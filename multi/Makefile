all: server.o thread.o packet.o
	gcc server.o thread.o packet.o -lpthread -o server

server.o:
	gcc -lpthread server.c -o server.o
packet.o:
	gcc packet.c -o packet.o
thread.o:
	gcc thread.c -o thread.o
