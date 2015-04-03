#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define DEBUG 1

struct sockaddr_in ReceiverAddr;

int main(int args, char** argv)
{
	int fd;
	int seq_num = 0;
	int ack = 0;
	char data[] = {'j', 'e', '2', '*', 't'};
	char* packet = malloc(8 * sizeof(char));
	char* ack_pack = malloc(3 * sizeof(char));
	socklen_t ReceiverAddrLen;

	//Configure struct for the receiver
	ReceiverAddr.sin_family = AF_INET;
	ReceiverAddr.sin_port = htons(54838);
	ReceiverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ReceiverAddrLen = sizeof(ReceiverAddr);

	//Connect to the receiver
	fd = socket(AF_INET, SOCK_STREAM, 0);
	connect(fd, (struct sockaddr*)&ReceiverAddr, ReceiverAddrLen);
	if(DEBUG) printf("Connected\n");

	for(;;)
	{
		int i = 0;
		for(i; i < 5; i++)
		{
			sprintf(packet, "%d%s\0", seq_num, data);
			if(DEBUG) printf("%s\n", packet);
			write(fd, packet, 8);
			seq_num++;
		}
		for(i = 0; i < 5; i++)
		{
			read(fd, ack_pack, 3);
			ack = atoi(ack_pack);
			if(DEBUG) printf("%d\n", ack);
		}
	}

	close(fd);
	free(packet);

	return 0;
}