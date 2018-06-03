package ru.ifmo.rain.feder.walk;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.FileVisitResult;
import java.nio.file.Path;
import java.nio.file.SimpleFileVisitor;
import java.nio.file.attribute.BasicFileAttributes;

public class MyFileVisitor extends SimpleFileVisitor<Path> {
    private BufferedWriter writer;

    MyFileVisitor(BufferedWriter wr) {
        super();
        writer = wr;
    }

    private FileVisitResult writeToFile(String result) {
        try {
            writer.write(result);
            writer.newLine();
            return FileVisitResult.CONTINUE;
        } catch (IOException e) {
            System.out.println("ERROR: Error while writing in walking" + e.getMessage());
            return FileVisitResult.TERMINATE;
        }
    }

    @Override
    public FileVisitResult visitFile(Path path, BasicFileAttributes basicFileAttributes) {
        return writeToFile(String.format("%08x %s", RecursiveWalk.countFnvHashForFile(path), path.toString()));
    }

    @Override
    public FileVisitResult visitFileFailed(Path path, IOException e) {
        return writeToFile(String.format("%08x %s", 0, path.toString()));
    }
}