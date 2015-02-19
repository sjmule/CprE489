#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define DEBUG 1

struct sockaddr_in ServAddr, ClientAddr;

int main(int args, char** argv)
{
	int fd;
	int i = 0;
	char packet[1472];
	
	//Ping the server to determine round trip time
	char *pinging = "ping -w 2 ";
	char *pingingEnd = " |tail -1| awk '{print $4}' | cut -d '/' -f 2 > tmp.txt";
	char str[256];
	strcpy(str, pinging);
	strcat(str, argv[1]);
	strcat(str, pingingEnd);
	system(str);
	
	printf("I pinged\n");
	
	//Get the results of the ping
	char avgS[7];
	double avg = 0;
	int t = NULL;
	FILE* tmp = fopen("tmp.txt", "r");
	getline(&avgS, &t, tmp);
	printf("%s\n", avgS);
	avg = atof(avgS);
	printf("%d\n", avg);
	
	//Construct the server address
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_port = htons(54811);
	ServAddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	//Construct the destination address
	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_port = htons(54811);
	ClientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	
	char junk[1469];
	int j = 0;
	for(j; j<1469; j++)
	{
		junk[j] = 'a';
	}
	
	for(;;)
	{
		sprintf(packet, "%d ", i);
		strcat(packet, junk);
		sendto(fd, packet, 1472, 0, &ServAddr, sizeof(ServAddr));
		i++;
	}
	
	return 0;
}