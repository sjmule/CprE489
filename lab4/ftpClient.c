#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct sockaddr_in ServAddrCommand, ServAddrPort1, ServAddrPort2;

int main(int args, char** argv)
{
	int d1, d2, d1Sock, d2Sock, n, commandSock, port1Sock, port2Sock;
	socklen_t ServAddrCommandLen;
	socklen_t ServAddrPort1Len;
	socklen_t ServAddrPort2Len;
	char *readResults = malloc(2048 * sizeof(char));
	char string1[50];
	char string2[50];

	//Configure struct for command port
	ServAddrCommand.sin_family = AF_INET;
	ServAddrCommand.sin_port = htons(54839);
	ServAddrCommand.sin_addr.s_addr = inet_addr(argv[1]);
	ServAddrCommandLen = sizeof(ServAddrCommand);

	//Connect to the server on the command port
	commandSock = socket(AF_INET, SOCK_STREAM, 0);
	connect(commandSock, (struct sockaddr*)&ServAddrCommand, ServAddrCommandLen);
	printf("Connection established\n");

	//Block here for user input
	fgets(string1, 50, stdin);
	strcpy(string2, string1);

	char *new_port1;
	new_port1 = strtok(string2, " ");
	new_port1 = strtok(NULL, " ");

	printf("%s\n", string1);

	//Configure struct for new_port1
	ServAddrPort1.sin_family = AF_INET;
	ServAddrPort1.sin_port = htons(atoi(new_port1));
	ServAddrPort1.sin_addr.s_addr = inet_addr(argv[1]);
	ServAddrPort1Len = sizeof(ServAddrPort1);
	
	//Bind mew_port1 to listen for list results
	d1Sock = socket(AF_INET, SOCK_STREAM, 0);
	bind(d1Sock, (struct sockaddr*)&ServAddrPort1, ServAddrPort1Len);

	write(commandSock, string1, 50);

	//Listen for list results
	listen(d1Sock, 2);
	d1 = accept(d1Sock, (struct sockaddr*)&ServAddrPort1, &ServAddrPort1Len);
	printf("Connection established\n");

	//Print list results
	n = read(d1, readResults, 2048);
	while(n>0)
	{
		printf("%s", readResults);
		n = read(d1, readResults, 2048);
	}

	//Block here for user input
	fgets(string1, 50, stdin);
	strcpy(string2, string1);

	char *new_port2;
	new_port2 = strtok(string2, " ");
	new_port2 = strtok(NULL, " ");

	//Configure struct for new_port1
	ServAddrPort2.sin_family = AF_INET;
	ServAddrPort2.sin_port = htons(atoi(new_port2));
	ServAddrPort2.sin_addr.s_addr = inet_addr(argv[1]);
	ServAddrPort2Len = sizeof(ServAddrPort2);
	
	//Bind mew_port1 to listen for list results
	d2Sock = socket(AF_INET, SOCK_STREAM, 0);
	bind(d2Sock, (struct sockaddr*)&ServAddrPort2, ServAddrPort2Len);

	write(commandSock, string1, 50);

	//Listen for list results
	listen(d2Sock, 2);
	d2 = accept(d2Sock, (struct sockaddr*)&ServAddrPort2, &ServAddrPort2Len);
	printf("Connection established\n");

	//Get the file name from the user input
	char *fileName;
	fileName = strtok(string1, " ");
	fileName = strtok(NULL, " ");

	//Open the file and write the data from the server to it
	FILE *file;
	file = fopen(fileName, "w");
	n = read(d2Sock, readResults, 2048);
	while(n>0)
	{
		fprintf(file, "%s", readResults);
		n = read(d2Sock, readResults, 2048);
	}

	write(commandSock, "quit", 4);

	free(readResults);

	close(d1Sock);
	close(d2Sock);
	close(commandSock);

	return 0;
}
