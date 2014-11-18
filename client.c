#include <netinet/in.h> 
#include <sys/socket.h>
#include <netdb.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "managewrapping.h"
#include "messages.h"

/*

oppretter klient og kobler til server. 
INPUT: brukerinput

*/

void createclient(char* in){

   /* deklarasjon av litt datastruktur */
     struct sockaddr_in serveraddr;
     int sock;
     char buf[1000];
     memset(buf, 0, sizeof(buf));
 
   /* Opprett socket */
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    /* Null ut serveradresse-struct'en */
    memset((void *) &serveraddr, 0, sizeof(serveraddr));

    /* Sett domenet til Internett */
    serveraddr.sin_family = AF_INET;

    /* Sett inn internettadressen til localhost, sette portnummer og koble opp mot server */
    serveraddr.sin_addr.s_addr = inet_addr("129.240.71.70");
    serveraddr.sin_port = htons(2009);
    connect(sock, (struct sockaddr*)&serveraddr, sizeof serveraddr); 

    /*headerinformasjon*/
    struct packet* toserver = malloc(sizeof(struct packet));
    
    /* Send data fra brukerinput*/

    sendmessage(sock, 10, in);
    printf("IN: %s\n", in);

  

    /* les data fra forbindelsen */
    //int l = read(sock, buf, sizeof(buf));

    /* legg til et termineringstegn, og skriv ut til skjerm */
   // buf[12] = '\0';
    printf("%s \n",buf);
    //memset(buf, 0, sizeof(buf));

    free(toserver);
    /* Steng socketen */
    close(sock);
}
