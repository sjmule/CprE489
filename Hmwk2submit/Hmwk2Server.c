#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct sockaddr_in ServAddr, ClientAddr;

int main(int args, char** argv)
{
	char buff[1600];
	int n, fd, r;
	int c = 1;
	socklen_t ClientAddrLen;

	//Construct the server address
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_port = htons(33333);
	ServAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	//Create and bind the socket to receive packets on	
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	bind(fd, (struct sockaddr*)&ServAddr, sizeof(ServAddr));
	
	for(;;)
	{
		//Receive packets
		n = recvfrom(fd, buff, sizeof(buff), 0, (struct sockaddr*)&ClientAddr, &ClientAddrLen);
		r++;
		//Send an acknowledgement when we receive 10 packets
		if(r == 10)
		{
			r = 0;
			char* message = " packets received";
			char ack[256];
			sprintf(ack, "%d", r*c);
			c++;
			strcat(ack, message);
			printf("%s\n", ack);
			sendto(fd, ack, 256, 0, (struct sockaddr*)&ClientAddr, ClientAddrLen);
		}
	}
	return 0;
}
