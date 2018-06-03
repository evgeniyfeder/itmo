.PHONY: all clean run

all: main

run: all
	./main

main: main.o libs/libstatic.a libs/libdloadable.so libs/libdlinking.so
	g++ -o main -L./libs -Wl,-rpath,./libs main.o -ldlinking -ldl libs/libstatic.a
	rm -rf *.o

main.o: main.cpp
	g++ -c -o $@ $<

libs/libstatic.a: static/static.o
	ar rvs $@ $^
	rm $^
	cp static/static.h ./include

static/static.o : static/static.cpp
	g++ -c -o $@ $<

libs/libdloadable.so: dynamic_loadable/dynamic_loadable.o
	g++ -shared $^ -o $@
	rm $^
	cp dynamic_loadable/dynamic_loadable.h include

dynamic_loadable/dynamic_loadable.o : dynamic_loadable/dynamic_loadable.cpp
	g++ -c -fPIC -o $@ $<

libs/libdlinking.so: dynamic_linking/dynamic_linking.o
	g++ -shared $^ -o $@
	rm $^
	cp dynamic_linking/dynamic_linking.h include

dynamic_linking/dynamic_linking.o : dynamic_linking/dynamic_linking.cpp
	g++ -c -fPIC -o $@ $<