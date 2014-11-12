all: client server

client: client.c hjemmeeksamen2.c
	gcc -o client client.c hjemmeeksamen2.c

server: server.c
	gcc -o server server.c

clean:
	rm -f *~ client server