CC = g++
flags = -Wall 

ser: Server.cpp
	$(CC) $(flags) -std=c++0x server.cpp -lpthread -o server

cli: cliente.o
	$(CC) $(flags) -o cliente cliente.o

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