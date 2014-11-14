struct packet
{
	//int id;
	int length;
	char* data;

};

struct packet* wrap(char* buf);
void unwrap();