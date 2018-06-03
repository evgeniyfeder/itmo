.PHONY: all

all: dloadable_library.so

dloadable_library.so: dynamic_loadable.o
	gcc -shared $^ -o ../libs/$@
	rm $^
	cp dynamic_loadable.h ../include

%.o : %.cpp
	gcc -c -fPIC -o $@ $<
