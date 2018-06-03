CC=g++
CFLAGS=-c -std=c++14 -Wunreachable-code -Wall -Wextra
LDFLAGS=
SOURCES=main.cpp callable_function.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hw3

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
