#include <stdio.h>

char* getcmdres(char buf[]){

	FILE* f;
	char *r;

	f = popen(buf, "r");
	fgets(r, sizeof(r), f);
	return r;
}