#include <netinet/in.h> 
#include <sys/socket.h>
#include <netdb.h> 
#include <stdio.h>
#include <string.h>

/*

oppretter klient og kobler til server. 
INPUT: brukerinput

*/

void createclient(char* in){

    printf("INPUT: %s\n", in);
   /* deklarasjon av litt datastruktur */
     struct sockaddr_in serveraddr;
     int sock;
     char buf[12]; 

   /* Opprett socket */
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    /* Null ut serveradresse-struct'en */
    memset((void *) &serveraddr, 0, sizeof(serveraddr));

    /* Sett domenet til Internett */
    serveraddr.sin_family = AF_INET;

    /* Sett inn internettadressen til localhost */
    serveraddr.sin_addr.s_addr = inet_addr("129.240.71.79");

    /* Sett portnummer */
    serveraddr.sin_port = htons(2009);

    /* Koble opp */
    connect(sock, (struct sockaddr*)&serveraddr, sizeof serveraddr); 

    /* Send data */
    //her må det sjekke på hva slags input som er sendt med og deretter sende med 
    //rett input til systemkall

  //  write(sock, "Hei verden!", 11);
    write(sock, in, sizeof(in));

    /* les data fra forbindelsen */
    read(sock, buf, 11);

    /* legg til et termineringstegn, og skriv ut til skjerm */
    buf[11] = '\0';
    printf("%s \n",buf);

    /* Steng socketen */
    close(sock);
}
