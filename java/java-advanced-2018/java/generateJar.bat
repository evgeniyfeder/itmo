javac -cp ../artifacts/ImplementorTest.jar ru/ifmo/rain/feder/implementor/*.java

SET pack_kg=info/kgeorgiy/java/advanced/implementor/


jar xf ../artifacts/ImplementorTest.jar %pack_kg%Impler.class %pack_kg%JarImpler.class %pack_kg%ImplerException.class
jar cfm Implementor.jar manifest.txt ru/ifmo/rain/feder/implementor/*.class %pack_kg%*.class

java -jar Implementor.jar -jar java.util.Set out.jar