all: server client

client:client.o
	g++ -g client.o -o client

client.o:client.cpp
	g++ -g  -c client.cpp -o client.o
	
server:server.o
	g++ -g  server.o -o server

server.o:server.cpp
	g++  -g -c server.cpp -o server.o

clean:all
	rm all

