.PHONY: client server

client : client.o
	g++ -o client client.o

server : server.o
	g++ -o server server.o

%.o : %.cpp
	g++ -Wall -c -o $@ $<
