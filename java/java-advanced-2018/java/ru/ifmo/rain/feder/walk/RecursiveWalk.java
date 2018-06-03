package ru.ifmo.rain.feder.walk;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;

public class RecursiveWalk {
    /*** Main ***/
    public static void main(String[] in) {
        if (in == null || in.length != 2 || in[0] == null || in[1] == null) {
            System.out.println("ERROR: Invalid arguments (need 2 non-null file name)");
        } else {
            countHashes(in[0], in[1]);
        }
    }

    /*** Hash module ***/
    private static final int FNV_PRIME_NUMBER = 0x01000193;
    private static final int FNV_START_NUMBER = 0x811c9dc5;

    private static final int FNV_BUF_SIZE = 1024;

    public static int countFnvHashForFile(Path path) {
        int curHash = FNV_START_NUMBER;

        try (FileInputStream inputStream = new FileInputStream(path.toString())) {
            int numRead;
            byte[] buf = new byte[FNV_BUF_SIZE];
            while ((numRead = inputStream.read(buf)) != -1) {
                for (int i = 0; i < numRead; i++) {
                    curHash *= FNV_PRIME_NUMBER;
                    curHash ^= buf[i] & 0xff;
                }
            }
        } catch (IOException e) {
            curHash = 0;
        }
        return curHash;
    }

    /*** Work with input file **/
    private static void countHashes(String inName, String outName) {
        /* Create input file handler */
        try (BufferedReader reader =
                     new BufferedReader(
                             new InputStreamReader(
                                     new FileInputStream(inName),
                                     StandardCharsets.UTF_8)
                     )) {
            /* Create output handler */
            try (BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(
                    new FileOutputStream(outName),
                    StandardCharsets.UTF_8))) {

                /* Start walking */
                try {
                    String directory;
                    MyFileVisitor visitor = new MyFileVisitor(writer);
                    while ((directory = reader.readLine()) != null) {
                        try {
                            Path path = Paths.get(directory);
                            Files.walkFileTree(path, visitor);
                        } catch (InvalidPathException e) {
                            writer.write(String.format("%08x %s", 0, directory));
                            writer.newLine();
                        }
                    }
                } catch (IOException e) {
                    System.out.println("ERROR: Error while count hashes: " + e.getMessage());
                }
            } catch (FileNotFoundException e) {
                System.out.println("ERROR: Output file not found" + e.getMessage());
            } catch (SecurityException e) {
                System.out.println("ERROR: Security exception while opening output file." + e.getMessage());
            } catch (IOException e) {
                System.out.println("ERROR: IOException when close output files: " + e.getMessage());
            }
        } catch (FileNotFoundException e) {
            System.out.println("ERROR: Input file not found" + e.getMessage());
        } catch (SecurityException e) {
            System.out.println("ERROR: Security exception while opening input file." + e.getMessage());
        } catch (IOException e) {
            System.out.println("ERROR: IOException when close input files: " + e.getMessage());
        }
    }
}
