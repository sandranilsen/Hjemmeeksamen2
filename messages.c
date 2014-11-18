
#include <stdio.h>
/*
funksjon som sørger for at hele meldingen/pakken mottas og mottas riktig
*/

void readmessage(int sock, int length, char* buff){

	printf("Kommer inn i readmessage\n");
	int tot_read = 0;
	int tot_left = length;
	int i = 0;

	while(tot_read < length){
		i = read(sock, buff + tot_read, tot_left);

		if(i < 0){

			perror("feil ved innlesning");

		}

		tot_read = tot_read + i;
		tot_left = tot_left - i;

	}


}

/*
funksjon som sørger for at hele meldingen/pakken sendes og sendes riktig
*/

void sendmessage(int sock, int length, char* buff){

	int tot_sent = 0;
	int tot_left = length;
	int i = 0;

	while(tot_sent < length){

		i= write(sock, buff + tot_sent, tot_left);
		if(i < 0){
			perror("feil ved skriving");
		}

		tot_sent = tot_sent + i;
		tot_left = tot_left - i;

	}


}