#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "client.h"

void command_loop(char* machinename, char* portnb);

int main(int argc, char* argv[]){

	command_loop(argv[1], argv[2]);
	return 0;

}

/*
kommandoløkke løper helt til bruker taster 'q'.
Kaller på createclient() fra client.c
*/
void command_loop(char* machinename, char* portnb){

	int isRunning = 1;
	char userInput[15];
	char* command = malloc(sizeof(char) * 20);
	char* param = malloc(sizeof(char) * 20);

	while(isRunning){
		printf("cmd (? for help)> ");

		if(fgets(userInput, sizeof(userInput), stdin) != NULL){

			if(userInput[0] == '?'){
				printf("! Please press a key \n");
				printf("! [1] list content of current directory (ls) \n");
				printf("! [2] print name of current directory (pwd) \n");
				printf("! [3] change current directory (cd) \n");
				printf("! [4] get file information \n");
				printf("! [5] display file (cat) \n");
				printf("! [?] this menu \n");
				printf("! [q] quit \n");

			}else{

				if(userInput[0] == '1'){
					command = "ls";
					createclient(machinename, portnb, command);

				}else if(userInput[0] == '2'){
					command = "pwd";
					createclient(machinename, portnb, command);

				}else if(userInput[0] == '3'){
					//cd

				}else if(userInput[0] == '4'){
					//file information

				}else if(userInput[0] == '5'){

					/*legg inn i egen metode*/
					command = "cat";
					/*

					DETTE MÅ FIKSES
					strncpy(param, userInput + 1, strlen(userInput));

					char* tot = malloc(strlen(command) + strlen(param) + 1);
					strcat(tot, command);
					strcat(tot, param);
			
					createclient(machinename, portnb, tot);

					free(tot);*/

				}else if(userInput[0] == 'q'){
					command = "q";
					createclient(machinename, portnb, command);
					isRunning = 0;

				}
			}
		}	
	}
//husk å frigjøre param
	free(command);
}
