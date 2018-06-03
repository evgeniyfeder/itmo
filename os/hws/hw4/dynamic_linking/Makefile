.PHONY: all

all: dlinking_library.so

%.so: dynamic_linking.o
	gcc -shared $^ -o ../libs/$@
	rm $^
	cp dynamic_linking.h ../include

%.o : %.cpp
	gcc -c -fPIC -o $@ $<
