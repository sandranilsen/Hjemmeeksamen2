#include <netinet/in.h> 
#include <sys/socket.h>
#include <netdb.h> 
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

#include "manage_syscall.h"
#include "managewrapping.h"
#include "messages.h"

/*

Oppretter klient og venter på at klienten skal koble seg til

*/

void createserver(){

	struct sockaddr_in serveraddr, clientaddr; 
    int clientaddrlen;
    int request_sock, sock;
    FILE* f;
   	char res[1000];

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

	while(isrunning){

    	/* aktiver lytting på socketen */
   	 	listen(request_sock, SOMAXCONN);

    	/* motta en forbindelse */
    	sock = accept(request_sock,(struct sockaddr *)&clientaddr, &clientaddrlen);

        /*leser data fra forbindelsen*/
        //HUSK Å ENDRE STØRRELSEN PÅ BUFF OG STØRRELSEN SOM SENDES MED

        char* buff = malloc(sizeof(char) * 10);
        readmessage(sock, 10, buff);
  
        printf("BUF: %s\n", buff);
           
		/*dersom q sendes med skal den evige løkken avsluttes og serveren lukkes*/
        /*
		if(buff[0] == 'q'){
			isrunning = 0;
			write(sock, " ", 2);

		}else{

            //HUSK Å ENDRE DENNE VERDIEN
            char* res = malloc(sizeof(char) * 100);

			f = popen(buff, "r");
	
            //HUSK Å ENDRE LENGDEN SOM SENDES MED SENDMESSAGE()
            while(fgets(res, sizeof(res), f)!=NULL){
                printf("%s\n", res);
                sendmessage(sock, 100, res);
            }
    
            
            isrunning = 1;
			
    	}*/
	}

    /* Steng socketene */
    pclose(f);
    close(sock);
    close(request_sock);

}