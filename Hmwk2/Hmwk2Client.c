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
	int fd;
	int i = 0;
	char packet[1024];
	char message[] = "Hello World";
	
	//Ping the server to determine round trip time
	char *pinging = "ping -w 2 ";
	char str[80];
	strcpy(str, pinging);
	strcat(str, argv[1]);
	system(str);
	
	//Construct the server address
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_port = htons(54811);
	ServAddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	//Construct the destination address
	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_port = htons(54811);
	ClientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	
	for(;;)
	{
		sprintf(packet, "%d ", i);
		strcat(packet, message);
		sendto(fd, packet, 1024, 0, &ServAddr, sizeof(ServAddr));
		i++;
	}
	
	return 0;
}