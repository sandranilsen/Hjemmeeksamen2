CC=gcc
CFLAGS = -I.

all: client server

client: client.c hjemmeeksamen2.c messages.c headerinfo.c
	$(CC) -o client client.c hjemmeeksamen2.c messages.c headerinfo.c -I.

server: servermain.c server.c messages.c headerinfo.c
	$(CC) -o server servermain.c server.c messages.c headerinfo.c -I.

#val: 

.PHONY: clean

clean:
	rm -f *~ client server


#vil lage et alternativ der jeg kan kjøre koden med valgrind