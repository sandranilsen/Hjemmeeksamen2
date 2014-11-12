#include <stdio.h>
#include <string.h>
#include "client.h"

void command_loop();

main(){

	command_loop();

}

/*
kommandoløkke løper helt til bruker taster 'q'.
*/
void command_loop(){

	int isRunning = 1;
	char userInput[40];

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

			}else if(userInput[0] == 'q'){

				isRunning = 0;

			}else{

				command_loop();
			}

		}
		
	}
}