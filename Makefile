all: client server

client: client.c hjemmeeksamen2.c
	gcc -o client client.c hjemmeeksamen2.c

server: servermain.c server.c manage_syscall.c
	gcc -o server servermain.c server.c manage_syscall.c

clean:
	rm -f *~ client server