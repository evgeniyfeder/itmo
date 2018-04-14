"use strict";

lecture("Final notes");

chapter("Error handling");

section("Standard errors");

try {
    1();
} catch (e) {
    println("Got exception");
    println("    toString(): " + e.toString());
    println("    name:       " + e.name);
    println("    message:    " + e.message);
} finally {
    println("Finally!");
}
println();

try {
    throw new Error("Custom error message");
} catch (e) {
    println("Got exception: " + e + " (" + typeof(e) + ")");
}
println();


section("Everything is throwable");

try {
    throw 1;
} catch (e) {
    println("Got exception: " + e + " (" + typeof(e) + ")");
}
println();

try {
    throw {name: "my error"};
} catch (e) {
    println("Got exception: " + e.name + " (" + typeof(e) + ")");
}
println();

try {
    throw undefined;
} catch (e) {
    println("Got exception: " + e);
}
println();


section("Custom errors");

function CustomError(message) {
    this.name = "CustomError";
    this.message = message;
}
CustomError.prototype = Error.prototype;

try {
    throw new CustomError("Custom error message");
} catch (e) {
    println("Got exception: " + e);
}
println();

