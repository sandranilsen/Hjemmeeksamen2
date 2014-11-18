struct packet
{
	//int id;
	int length;
	

};

struct packet* wrap(char* buf);
void unwrap();