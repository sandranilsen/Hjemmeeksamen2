#include <netinet/in.h> 
#include <sys/socket.h>
#include <netdb.h> 
#include <stdio.h>
#include <string.h>

main()
{

    //kan flytte dette inn i egen metode, for så å ha ordreløkka her.
    //kanskje litt selvmotsigende mtp filnavnet?
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
    serveraddr.sin_addr.s_addr = inet_addr("129.240.71.85");

    /* Sett portnummer */
    serveraddr.sin_port = htons(2009);

    /* Koble opp */
    connect(sock, (struct sockaddr*)&serveraddr, sizeof serveraddr); 

    /* Send data */
    write(sock, "Hei verden!", 11);

    /* les data fra forbindelsen */
    read(sock, buf, 11);

    /* legg til et termineringstegn, og skriv ut til skjerm */
    buf[11] = '\0';
    printf("%s \n",buf);

    /* Steng socketen */
    close(sock);

}