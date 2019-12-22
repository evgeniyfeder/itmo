package ru.evgeniyfeder.sd.refactoring.html;

import java.io.PrintWriter;

public class HTMLPrinter implements AutoCloseable {
    public final PrintWriter writer;

    public HTMLPrinter(PrintWriter writer) {
        this.writer = writer;
        this.writer.println("<html><body>");
    }

    public void println(String str) {
        this.writer.println(str + "</br>");
    }

    public void print(int str) {
        writer.println(str);
    }

    public void putWithH1(String str) {
        writer.println("<h1>" + str + "</h1>");
    }

    @Override
    public void close() {
        this.writer.println("</body></html>");
    }
}
