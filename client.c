#include <netinet/in.h> 
#include <sys/socket.h>
#include <netdb.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "messages.h"
#include "headerinfo.h"

/*
oppretter klient og kobler til server. 
INPUT: brukerinput
*/

void createclient(char* in){

   /* deklarasjon av litt datastruktur */
    struct sockaddr_in serveraddr;
    int sock;
 
   /* Oppretter socket, nuller ut serveradresse-struct'en, setter domenet til Internett */
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset((void *) &serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    /* Sett inn internettadressen til localhost, sette portnummer og koble opp mot server */
    serveraddr.sin_addr.s_addr = inet_addr("129.240.71.70");
    serveraddr.sin_port = htons(2009);
    connect(sock, (struct sockaddr*)&serveraddr, sizeof serveraddr); 

    /*oppretter og oppdaterer headerinformasjon og sender til server*/
    struct packet* toserver = malloc(sizeof(struct packet));
    makeheaderinfo(in, toserver);
    char* streamtoserver = (char*)toserver;
    sendmessage(sock, sizeof(streamtoserver), streamtoserver);

    /* Send data fra brukerinput/nyttelast*/
    sendmessage(sock, toserver->length, in);

    /*leser inn headerinformasjon fra server*/
    struct packet* fromserver = malloc(sizeof(struct packet));
    char* streamfromserver = (char*)fromserver;
    readmessage(sock, sizeof(streamfromserver), streamfromserver);

    /*leser inn beskjed/pakke fra serveren og legger dette i et buffer lik lengden som er oppgitt i headerinformasjonen*/
    char* buff = malloc(sizeof(char) * fromserver->length);
    readmessage(sock, fromserver->length, buff);
    printf("%s\n", buff);

    memset(buff, 0, sizeof(buff));

    /*frigjore minne*/
    free(toserver);
    free(fromserver);
    free(buff);

    /* Steng socketen */
    close(sock);
}
