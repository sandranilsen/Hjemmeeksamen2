#include <stdio.h>

char* getcmdres(char buf[]){

	FILE* f;
	char *res;

	f = popen(buf, "r");
	fgets(res, sizeof(res), f);
	return res;
}