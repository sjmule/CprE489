#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//generate random number, if < packet loss, don't send packet
//source port 44444 destination port 33333
struct sockaddr_in SourceAddr, DestinationAddr;

int main(int args, char** argv)
{
	char buff[2048]; //Buffer to hold the packets in
	int n, fdS, fdD;
	socklen_t DestAddrLen; //The destination address length
	socklen_t SourceAddrLen; //The source address length
	int lossRate = atoi(argv[5]);  //Determine the loss rate
	int random;

	int sourcePort = atoi(argv[2]); //Determine the source port
	int destPort = atoi(argv[4]); //Determine the destination port
	
	printf("Source IP: %s, Source Port: %d, Destination IP: %s, Destination Port: %d, Loss Rate: %d\n", argv[1], sourcePort, argv[3], destPort, lossRate);
	//Construct the source address
	SourceAddr.sin_family = AF_INET;
	SourceAddr.sin_port = htons(sourcePort);
	SourceAddr.sin_addr.s_addr = inet_addr(argv[1]);
	
	//Construct the destination address
	DestinationAddr.sin_family = AF_INET;
	DestinationAddr.sin_port = htons(destPort);
	DestinationAddr.sin_addr.s_addr = inet_addr(argv[3]);

	//Get the size of both the addresses
	DestAddrLen = sizeof(DestinationAddr);
	SourceAddrLen = sizeof(SourceAddr);
	
	//Open the sockets for the source and destination, bind the source address
	fdS = socket(AF_INET, SOCK_DGRAM, 0);
	fdD = socket(AF_INET, SOCK_DGRAM, 0);
	bind(fdS, (struct sockaddr*)&SourceAddr, SourceAddrLen);

	for(;;)
	{
		//receive and store a packet from the source
		n = recvfrom(fdS, buff, sizeof(buff), 0, (struct sockaddr*) &SourceAddr, &SourceAddrLen);
		
		//generate a random value 0-100
		srand(time(NULL));
		random = rand() % 101;
		//check if the random value is less than the loss rate, if it is, don't send the packet, if it is not, send the packet
		if(random <= lossRate)
			continue;
		else
		{
			//send the packet to the destination
			sendto(fdD, buff, n, 0, (struct sockaddr*)&DestinationAddr, DestAddrLen);
		}
	}
	return 0;
}
