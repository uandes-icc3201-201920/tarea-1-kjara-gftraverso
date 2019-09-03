CC = g++
flags = -Wall 

ser: server.o
	$(CC) $(flags) -o server server.o

cli: cliente.o
	$(CC) $(flags) -o cliente cliente.o

server.o: Server.cpp
	$(CC) $(flags) -o server.o -c server.cpp

cliente.o: Cliente.cpp
	$(CC) $(flags) -o cliente.o -c Cliente.cpp

server: ser
	./server

cliente: cli
	./cliente

clean:
	rm -f *.o
	rm -f server
	rm -f cliente