l9.PHONY: all

all: static_library.a

static_library.a: static.o
	ar rcs ../libs/$@ $^
	rm $^
	cp static.h ../include

static.o : static.cpp
	gcc -c -o $@ $<
