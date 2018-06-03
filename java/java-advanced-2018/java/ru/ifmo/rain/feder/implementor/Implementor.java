package ru.ifmo.rain.feder.implementor;

import info.kgeorgiy.java.advanced.implementor.*;
import javafx.util.Pair;

import javax.tools.JavaCompiler;
import javax.tools.ToolProvider;
import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.lang.reflect.*;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.nio.file.attribute.FileAttribute;
import java.util.*;
import java.util.function.Predicate;
import java.util.jar.Attributes;
import java.util.jar.JarOutputStream;
import java.util.jar.Manifest;
import java.util.stream.Collectors;
import java.util.zip.ZipEntry;

/**
 * Implementation class for {@link JarImpler} interface.
 */
public class Implementor implements JarImpler {
    /**
     * {@link StringBuilder} class for saving code.
     */
    private StringBuilder code;

    /**
     * {@link Set} for saving class methods and constructors,
     * where first argument is header and second is body of function.
     */
    private Set<Pair<String, String>> bodyFunctions;

    /**
     * Current {@link Class}, which we are creating.
     */
    private Class curClass;

    /**
     * Default constructor.
     */
    public Implementor() {
    }
    /**
     * Getting class name in good format.
     * @param aClass {@link Class} for which we want get name.
     * @return Name return canononical name of class.
     */
    private static String getClassName(Class aClass) {
        return aClass.getCanonicalName();
    }

    /**
     * Getting class package in good format.
     * @param aClass {@link Class} for which we want get package.
     * @return Name returned by {@link Package#getName()} function for package got by {@link Class#getPackage()} function.
     */
    private static String getPackageName(Class aClass) {
        if (aClass.getPackage() == null)
            return "";
        return aClass.getPackage().getName();
    }

    /**
     * Getting implementation class name in good format.
     * @param aClass {@link Class} for which we want get name.
     * @return Name returned by {@link Class#getSimpleName()} and "Impl" suffix function.
     */
    private static String getImplClassName(Class aClass) {
        return aClass.getSimpleName() + "Impl";
    }

    /**
     * Get return type for executable class.
     * @param executable {@link Constructor} or {@link Method} object.
     * @return name of {@link Method} returning type by {@link Method#getReturnType()}
     * or empty {@link String} if it's constructor.
     */
    private static String getReturnType(Executable executable) {
        if (executable instanceof Method) {
            return getClassName(((Method) executable).getReturnType());
        }
        return "";
    }

    /**
     * Get arguments of executable object.
     * @param executable {@link Constructor} or {@link Method} object from we want arguments.
     * @param sb output string builder with (arg_type1 arg0[, arg_type2 arg1...]) suffix.
     */
    private static void getMethodArguments(Executable executable, StringBuilder sb) {
        int argInd = 0;
        sb.append("(");

        for (Class<?> arg : executable.getParameterTypes()) {
            sb.append(getClassName(arg)).append(" arg").append(argInd).append(", ");
            argInd++;
        }

        if (executable.getParameterTypes().length != 0) {
            sb.setLength(sb.length() - 2);
        }

        sb.append(")");
    }

    /**
     * Get name of executable object.
     * @param executable {@link Constructor} or {@link Method} object.
     * @param aClass class where executable object exists.
     * @return Name by {@link Executable#getName()} if it's {@link Method},
     * or {@link Implementor#getImplClassName(Class)} if it's {@link Constructor}.
     */
    private static String getFuncName(Executable executable, Class aClass) {
        if (executable instanceof Method)
            return executable.getName();
        return getImplClassName(aClass);
    }

    /**
     * Get body of executable object.
     * @param executable {@link Constructor} or {@link Method} object.
     * @return
     * "return X;", where X - false or 0 or null if executable is {@link Method} with non-void return type
     * "super(arg0[, arg1...]);" if it's {@link Constructor} which is recall of superclass constructor
     * Empty string otherwise.
     */
    private static String getMethodBody(Executable executable) {
        if (executable instanceof Method) {
            Class ret = ((Method) executable).getReturnType();

            if (ret.isPrimitive() && ret != void.class) {
                if (ret == boolean.class) {
                    return "return false;\n";
                } else {
                    return "return 0;\n";
                }
            } else if (ret != void.class) {
                return "return null;\n";
            }
        } else if (executable instanceof Constructor) {
            StringBuilder sb = new StringBuilder();

            sb.append("super(");
            for (int i = 0; i < executable.getParameterTypes().length; i++) {
                sb.append("arg").append(i).append(", ");
            }

            if (executable.getParameterTypes().length != 0) {
                sb.setLength(sb.length() - 2);
            }
            sb.append(");\n");
            return sb.toString();
        }
        return "";
    }

    /**
     * Add package and class head text to {@link Implementor#code}.
     */
    private void addFileHeader() {
        if (!getPackageName(curClass).equals(""))
            code.append("package ").append(getPackageName(curClass)).append(";\n");
        code.append("public class ").append(getImplClassName(curClass)).append(" ")
                .append(curClass.isInterface() ? "implements " : "extends ").append(curClass.getSimpleName()).append(" {\n");
    }

    /**
     * Add all inner functions to {@link Implementor#code}.
     */
    private void printAll() {
        for (Pair<String, String> method : bodyFunctions) {
            code.append(method.getKey()).append(" {\n").
                    append(method.getValue()).append("\n" +
                    "}\n");
        }
    }

    /**
     * Add executable objects to global {@link Set}.
     * @param executables array of executable objects.
     * @param checker predicate to control which executable objects we want to implement.
     * @return number of true-checked objects.
     */
    private int addArrayOfExecutable(Executable[] executables,
                                     Predicate<Integer> checker) {
        int numReaded = 0;

        for (Executable executable : executables) {
            int mod = executable.getModifiers();

            if (checker.test(mod)) {
                continue;
            }
            mod = executable.getModifiers() & (Modifier.classModifiers() ^ Modifier.ABSTRACT);

            StringBuilder sb = new StringBuilder();
            sb.append(Modifier.toString(mod)).append(" ")
                    .append(getReturnType(executable)).append(" ")
                    .append(getFuncName(executable, curClass));


            getMethodArguments(executable, sb);

            if (executable.getExceptionTypes().length != 0) {
                sb.append(" throws ");

                for (Class exception : executable.getExceptionTypes()) {
                    sb.append(getClassName(exception)).append(", ");
                }

                sb.setLength(sb.length() - 2);
            }

            bodyFunctions.add(new Pair<>(sb.toString(), getMethodBody(executable)));
            numReaded++;
        }
        return numReaded;
    }

    /**
     * Add all methods, which we need to class, to global {@link Set}.
     */
    private void addAllMethods() {
        addArrayOfExecutable(curClass.getMethods(), (x) -> !Modifier.isAbstract(x));
        while (curClass != null) {
            addArrayOfExecutable(curClass.getDeclaredMethods(), (x) -> !Modifier.isAbstract(x));
            curClass = curClass.getSuperclass();
        }
    }

    /**
     * Add all methods and constructors, which we need to class, to global {@link Set}.
     * @throws ImplerException
     * If we don't have not-private constructors.
     */
    private void addClassBody() throws ImplerException {
        if (!curClass.isInterface()) {
            if (addArrayOfExecutable(curClass.getDeclaredConstructors(), Modifier::isPrivate) == 0) {
                throw new ImplerException("There is no not-private constructor");
            }
        }
        addAllMethods();
    }

    /**
     * Check input parametres for correctness.
     * @param aClass input class.
     * @param path  input path.
     * @throws ImplerException
     * if arguments is null or we can't implement this objects.
     */
    private void checkClass(Class aClass, Path path) throws ImplerException {
        if (aClass == null) {
            throw new ImplerException("Required not-null aClass class");
        } else if (path == null) {
            throw new ImplerException("Required not-null path class");
        } else if (aClass.isPrimitive() || aClass.isArray() || aClass == Enum.class || Modifier.isFinal(aClass.getModifiers())) {
            throw new ImplerException("Incorrect class");
        }
    }

    /**
     * Create directory for files.
     * @param path path for creating.
     * @throws ImplerException
     * if {@link IOException} or {@link SecurityException}
     * occurs in {@link Files#createDirectories(Path, FileAttribute[])} or {@link Path#getParent()} function.
     */
    private void createDirectory(Path path) throws ImplerException {
        if (path.getParent() != null) {
            try {
                Files.createDirectories(path.getParent());
            } catch (IOException | SecurityException e) {
                throw new ImplerException("Unable to create directories for output file", e);
            }
        }
    }


    /**
     * Get full path to implementing class
     * @param aClass input class.
     * @param path input path.
     * @param suffix suffix for path.
     * @return new path with full path to class.
     */
    private Path getPathToCreatedFile(Class aClass, Path path, String suffix) {
        return path.resolve(getPackageName(aClass).replace('.', File.separatorChar))
                .resolve(getImplClassName(aClass) + suffix);
    }

    /**
     * Generate string with implementation of class
     * @param aClass class for implementing
     * @return string with implementation of class
     * @throws ImplerException
     * see {@link Implementor#addClassBody()} function
     */
    private String generateClass(Class aClass) throws ImplerException {
        code = new StringBuilder();
        bodyFunctions = new HashSet<>();
        curClass = aClass;

        addFileHeader();
        addClassBody();
        printAll();
        code.append("}\n");

        return code.toString();
    }

    /**
     * Convert to unicode string
     * @param in input string
     * @return converted string
     */
    private String toUnicode(String in) {
        StringBuilder b = new StringBuilder();

        for (char c : in.toCharArray()) {
            if (c >= 128)
                b.append("\\u").append(String.format("%04X", (int) c));
            else
                b.append(c);
        }

        return b.toString();
    }


    /**
     * @throws ImplerException given class cannot be generated for one of such reasons:
     *  <ul>
     *  <li> Some arguments are <tt>null</tt> or can't implement</li>
     *  <li> Can't create files or directories. </li>
     *  <li> The problems with I/O occurred during implementation. </li>
     *  <li> Haven't not-private class constructor </li>
     *  </ul>
     */
    @Override
    public void implement(Class aClass, Path path) throws ImplerException {
        checkClass(aClass, path);
        path = getPathToCreatedFile(aClass, path, ".java");
        createDirectory(path);

        try (BufferedWriter outFile = Files.newBufferedWriter(path)) {
            outFile.write(toUnicode(generateClass(aClass)));
        } catch (IOException e) {
            System.out.println("Error with opening output file" + e);
        }
    }

    /**
     * Clean all including files and directories in input path
     * @param path input path
     * @throws IOException
     * if occurs error while walking
     */
    private void clean(Path path) throws IOException {
        if (Files.exists(path)) {
            Files.walkFileTree(path, new SimpleFileVisitor<Path>() {
                public FileVisitResult visitFile(Path var1, BasicFileAttributes var2) throws IOException {
                    Files.delete(var1);
                    return FileVisitResult.CONTINUE;
                }

                public FileVisitResult postVisitDirectory(Path var1, IOException var2) throws IOException {
                    Files.delete(var1);
                    return FileVisitResult.CONTINUE;
                }
            });
        }
    }

    /**
     * @throws ImplerException given class cannot be generated for one of such reasons:
     *  <ul>
     *  <li> Error during implementation. See {@link #implement(Class, Path)} </li>
     *  <li> Can't create files or directories. </li>
     *  <li> {@link JavaCompiler} failed </li>
     *  <li> The problems with I/O occurred during implementation. </li>
     *  </ul>
     */
    @Override
    public void implementJar(Class aClass, Path path) throws ImplerException {
        checkClass(aClass, path);
        createDirectory(path);

        Path tmpDir;
        try {
             tmpDir = Files.createTempDirectory(path.toAbsolutePath().getParent(), "tmp");
        } catch (IOException e) {
            throw new ImplerException("Can't create temporary directory", e);
        }


        Manifest manifest = new Manifest();
        Attributes attributes = manifest.getMainAttributes();
        attributes.put(Attributes.Name.MANIFEST_VERSION, "1.0");
        attributes.put(Attributes.Name.IMPLEMENTATION_VENDOR, "Evgeniy Feder");
        try (JarOutputStream writer = new JarOutputStream(Files.newOutputStream(path), manifest)) {
            implement(aClass, tmpDir);

            JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();

            String[] args = new String[5];
            args[0] = "-cp";
            args[1] = tmpDir.toString() + File.pathSeparator + System.getProperty("java.class.path");

            args[2] = "-encoding";
            args[3] = "Cp1251";
            args[4] = getPathToCreatedFile(aClass, tmpDir, ".java").toString();

            if (compiler.run(null, null, null, args) != 0) {
                throw new ImplerException("Can't compile generated file");
            }
            try {
                writer.putNextEntry(new ZipEntry(aClass.getName().replace('.', '/') + "Impl.class"));
                Files.copy(getPathToCreatedFile(aClass, tmpDir, ".class"), writer);
            } catch (IOException e) {
                throw new ImplerException("Unable to write to JAR file", e);
            }
        } catch (IOException e) {
            throw new ImplerException("Unable to create JAR file", e);
        } finally {
            try {
                clean(tmpDir);
            } catch (IOException e) {
                System.out.println("Error while deleting temp directory" + e);
            }
        }
    }

    /**
     * Start point to program.
     * @param args
     * ["-jar" "class_name" "jar_out"] if we want create jar from
     * ["class_name", "jar_out"] if we want create only java file
     * where class_name - name of input class
     * and jar_out - path to jar file.
     */
    public static void main(String[] args) {
        if (args == null || (args.length != 2 && args.length != 3)) {
            System.out.println("Two or three arguments expected");
            return;
        }
        if (Arrays.stream(args).filter(Objects::isNull)
                .collect(Collectors.toList()).size() != 0) {
            System.out.println("Not-null arguments expected");
        }

        JarImpler implementor = new Implementor();
        try {
            if (args.length == 2) {
                implementor.implement(Class.forName(args[0]), Paths.get(args[1]));
            } else {
                implementor.implementJar(Class.forName(args[1]), Paths.get(args[2]));
            }
        } catch (LinkageError | ClassNotFoundException e) {
            System.out.println("Incorrect class name: " + e.getMessage());
        } catch (InvalidPathException e) {
            System.out.println("Incorrect path to root: " + e.getMessage());
        } catch (ImplerException e) {
            System.out.println("Error while implementation: " + e.getMessage());
        }
    }
}
