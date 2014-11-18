
/*disse metodene tar for seg sending og mottak av meldinger/pakker*/

void readmessage(int sock, int length, char* buff);
void sendmessage(int sock, int length, char* buff);