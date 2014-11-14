#include <netinet/in.h> 
#include <sys/socket.h>
#include <netdb.h> 
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

#include "manage_syscall.h"

/*

Oppretter klient og venter på at klienten skal koble seg til

*/

void createserver(){

	struct sockaddr_in serveraddr, clientaddr; 
    int clientaddrlen;
    int request_sock, sock;
    char buf[100]; 

   	char res[1000];
   // char* res = malloc(sizeof(char) * 1000);
    int isrunning = 1;

    /* Opprett request-socket  */
    request_sock = socket(AF_INET, SOCK_STREAM, 
                                    IPPROTO_TCP);
    /* Opprett adressestruct */
    memset((void *) &serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET; 
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(2009);

    /* bind adressen til socketen */
    bind(request_sock, (struct sockaddr *)&serveraddr, sizeof serveraddr);
    //printf("You are connected to the server\n");

	while(isrunning){

    	/* aktiver lytting på socketen */
   	 	listen(request_sock, SOMAXCONN);

    	/* motta en forbindelse */
    	sock = accept(request_sock,(struct sockaddr *)&clientaddr, &clientaddrlen);

    	/* les data fra forbindelsen, og skriv dem ut */
    	read(sock, buf,100);
    	buf[100] = '\0';

		/*dersom q sendes med skal den evige løkken avsluttes og serveren lukkes*/
		if(buf[0] == 'q'){
			isrunning = 0;
			write(sock, " ", 100);

		}else{

 	  		FILE* f;

			f = popen(buf, "r");
			fgets(res, sizeof(res), f);
            write(sock, res, sizeof(res));
            isrunning = 1;
			
    	}
	}

    /* Steng socketene */
    close(sock);
    close(request_sock);

}