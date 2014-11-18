all: client server

client: client.c hjemmeeksamen2.c messages.c
	gcc -o client client.c hjemmeeksamen2.c messages.c

server: servermain.c server.c manage_syscall.c messages.c
	gcc -o server servermain.c server.c manage_syscall.c messages.c

clean:
	rm -f *~ client server

#vil lage et alternativ der jeg kan kjøre koden med valgrind