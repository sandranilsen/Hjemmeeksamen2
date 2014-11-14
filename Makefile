all: client server

client: client.c hjemmeeksamen2.c managewrapping.c
	gcc -o client client.c hjemmeeksamen2.c managewrapping.c

server: servermain.c server.c manage_syscall.c
	gcc -o server servermain.c server.c manage_syscall.c

clean:
	rm -f *~ client server

#vil lage et alternativ der jeg kan kjøre koden med valgrind