#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headerinfo.h"

/*
funksjon for å legge inn headerinformasjon
*/
void makeheaderinfo(char* msg, struct packet* p){

	p->length = strlen(msg);

}