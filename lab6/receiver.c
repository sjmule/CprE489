#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#include "AddCongestion.h"

#define DEBUG 1

struct sockaddr_in SenderAddr, SenderAddr2;

int AddCongestion (double p);

int main(int argc, char** argv)
{
	int fd, s, SenderAddr2Len, do_i_take;
	int n = 0;
	int ack_num = 0;
	double probability;
	socklen_t SenderAddrLen;
	char* buff[8];
	char* ack_pack = malloc(3 * sizeof(char));
	
	if(argc == 1)
	{
		probability = 0.001;
	}
	else
	{
		probability = atof(argv[1]);
	}
	
	//Configure struct for the sender
	SenderAddr.sin_family = AF_INET;
	SenderAddr.sin_port = htons(54841);
	SenderAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	SenderAddrLen = sizeof(SenderAddr);

	//Bind the sender struct to a port to listen
	fd = socket(AF_INET, SOCK_STREAM, 0);
	bind(fd, (struct sockaddr*)&SenderAddr, SenderAddrLen);
	
	//Listen on the new port
	if(DEBUG) printf("Listening\n");
	listen(fd, 2);
	s = accept(fd, (struct sockaddr*)&SenderAddr2, &SenderAddr2Len);
	if(DEBUG) printf("Accepted\n");

	int i = 0;
	for(;;)
	{
		n = read(s, buff, 8);
		if(DEBUG) printf("%s\n", buff);
		if(AddCongestion(probability))
		{
			if(DEBUG) printf("nope\n");
		}
		else
		{
			sleep(1);
			sprintf(ack_pack, "%d\0", ack_num);
			write(s, ack_pack, sizeof(ack_pack));
			ack_num++;
		}

	}

	close(fd);
	close(s);

	return 0;
}