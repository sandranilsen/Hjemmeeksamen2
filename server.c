#include <netinet/in.h> 
#include <sys/socket.h>
#include <netdb.h> 
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

#include "messages.h"
#include "headerinfo.h"

/*
Oppretter klient og venter på at klienten skal koble seg til
*/

void createserver(char* portnb){

    int port = atoi(portnb);
	struct sockaddr_in serveraddr, clientaddr; 
    int clientaddrlen;
    int request_sock, sock;
    FILE* f;

    int isrunning = 1;

    /* Opprett request-socket  */
    request_sock = socket(AF_INET, SOCK_STREAM, 
                                    IPPROTO_TCP);
    /* Opprett adressestruct */
    memset((void *) &serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET; 
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(port);

    /* bind adressen til socketen */
    bind(request_sock, (struct sockaddr *)&serveraddr, sizeof serveraddr);

	while(isrunning){

    	/* aktiver lytting på socketen */
   	 	listen(request_sock, SOMAXCONN);

    	/* motta en forbindelse */
    	sock = accept(request_sock,(struct sockaddr *)&clientaddr, &clientaddrlen);

        /*leser inn headerinformasjonen fra client*/
        struct packet* fromclient = malloc(sizeof(struct packet));
        char* streamfromclient = (char*)fromclient;
        readmessage(sock, sizeof(streamfromclient), streamfromclient);
  
        /*leser inn beskjed/pakke fra klienten og legger dette i et buffer lik lengden som er oppgitt i headerinformasjonen*/
        char* buff = malloc(sizeof(char) * fromclient->length);
        readmessage(sock, fromclient->length, buff);
        printf("BUF: %s\n", buff);

           
		/*dersom q sendes med skal den evige løkken avsluttes og serveren lukkes*/
		if(strcmp(buff, "q") == 0){
			isrunning = 0;
            memset(buff, 0, sizeof(buff));
			//write(sock, " ", 2);

		}else if(strcmp(buff, "ls") == 0 || strcmp(buff, "pwd") == 0){

            //HUSK Å ENDRE DENNE VERDIEN
            char* res = malloc(sizeof(char) * 200);
			f = popen(buff, "r");
            fread(res, sizeof(char)*200, sizeof(res), f);

            /*nullstiller bufferet*/
           // memset(buff, 0, sizeof(buff));

            /*oppretter og oppdaterer headerinformasjon og sender til client*/
            struct packet* toclient = malloc(sizeof(struct packet));
            makeheaderinfo(res, toclient);
            char* streamtoclient = (char*)toclient;
            sendmessage(sock, sizeof(streamtoclient), streamtoclient);

            printf("RES: %s\n", res);
	
            sendmessage(sock, toclient->length, res);
 
            
            isrunning = 1;
            free(res);
            free(toclient);
			
    	}

        memset(buff, '\0' , sizeof(buff));
        free(buff);
        free(fromclient);
   
	}

    /* Steng socketene */
    pclose(f);
    close(sock);
    close(request_sock);

}