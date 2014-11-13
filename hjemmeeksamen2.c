#include <stdio.h>
#include <string.h>
#include "client.h"

void command_loop();

int main(){

	command_loop();
	return 0;

}

/*

kommandoløkke løper helt til bruker taster 'q'.
Kaller på createclient() fra client.c

*/
void command_loop(){

	int isRunning = 1;
	char userInput[3];
	char* command;

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
					createclient(command);

				}else if(userInput[0] == '2'){
					command = "pwd";
					createclient(command);

				}else if(userInput[0] == '3'){
					//cd

				}else if(userInput[0] == '4'){
					//file information

				}else if(userInput[0] == '5'){
					//cat

				}else if(userInput[0] == 'q'){
					command = "q";
					createclient(command);
					isRunning = 0;

				}

			}

		}
		
	}
}