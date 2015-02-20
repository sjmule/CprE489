#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define DEBUG 1

struct sockaddr_in ServAddr, ClientAddr;

int main(int args, char** argv)
{
	int fd, n;
	int acks = 0;
	int i = 0;
	int N = 100;
	double throughput[100];
	char packet[1472];
	char ackBuff[256];
	socklen_t ServAddrLen;
	
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
	char* avgS;
	double avg = 0;
	int* t = NULL;
	FILE* tmp;
	tmp = fopen("tmp.txt", "r");
	if(tmp == 0)
	{
		perror("Failed to open file");
		exit(-1);
	}
	getline(&avgS, &t, tmp);
	avg = atof(avgS);

	
	//Construct the server address
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_port = htons(33333);
	ServAddr.sin_addr.s_addr = inet_addr(argv[1]);

	ServAddrLen = sizeof(ServAddr);	
	
	fd = socket(AF_INET, SOCK_DGRAM, 0);
	
	char junk[1469];
	int j = 0;
	for(j; j<1469; j++)
	{
		junk[j] = 'a';
	}
	
	int k = 0;
	for(;;)
	{
		int ack = 0;
		struct timeval tv;
		time_t starttime;
		time_t endtime;
		double start;
		double end;
		double through = 0;
		double top = 0;
		double bottom = 0;
		gettimeofday(&tv, NULL);
		starttime = tv.tv_usec;
		start = (double) starttime;
		for(i=0; i<N; i++){
			sprintf(packet, "%d ", i);
			strcat(packet, junk);
			sendto(fd, packet, sizeof(packet), 0, (struct sockaddr*)&ServAddr, &ServAddrLen);
			i++;
		}
		
		if (( n = recvfrom(fd, ackBuff, sizeof(ackBuff), 0, (struct sockaddr*)&ServAddr, ServAddrLen)) != -1 ) {
			ack++;
		}
		gettimeofday(&tv, NULL);
		endtime = tv.tv_usec;
		end = (double) endtime;
		top = (ack*8*1518);
		bottom = (end - start - avg);
		through = top/bottom;
		throughput[k] = through;
		k++;
		N = N*2;
		//calculate throughput change between previous rounds, how to do this was not made very clear, break when change <=.05
		//throughput is an array of size 100, I'm sure if I knew how to calculate change between rounds exceeding the size of this array
		//would not be a problem, but since I don't, don't run this program forever so it doesn't seg fault
	}
	
	return 0;
}
