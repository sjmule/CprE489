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
	char buff[1024];
	int n, fd, ClientAddrLen, r;
	
	//Construct the server address
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_port = htons(54811);
	ServAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	bind(fd, &ServAddr, sizeof(ServAddr));
	for(;;)
	{
		n = recvfrom(fd, buff, 1024, 0, &ClientAddr, &ClientAddrLen);
		printf("%d ", n);
		r++;
		if(r == 10)
		{
			r = 0;
			char* message = " packets received";
			char ack[256];
			sprintf(ack, "%d", r);
			strcat(ack, message);
			sendto(fd, ack, 256, 0, &ClientAddr, ClientAddrLen);
		}
	}
	return 0;
}