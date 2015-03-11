#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct sockaddr_in ServAddrCommand, ServAddrData, ServAddrDataTwo;

int main(int args, char** argv)
{
	int dataSock, commandSock, n, s, ServAddrDataTwoLen;
	socklen_t ServAddrCommandLen;
	socklen_t ServAddrDataLen;
	char *listResults = malloc(2048 * sizeof(char));

	//Configure struct for command port
	ServAddrCommand.sin_family = AF_INET;
	ServAddrCommand.sin_port = htons(54819);
	ServAddrCommand.sin_addr.s_addr = inet_addr(argv[1]);
	ServAddrCommandLen = sizeof(ServAddrCommand);
	
	//Configure struct for data port
	ServAddrData.sin_family = AF_INET;
	ServAddrData.sin_port = htons(54820);
	ServAddrData.sin_addr.s_addr = inet_addr(argv[1]);
	ServAddrDataLen = sizeof(ServAddrData);
	
	//Bind data port to receive on later
	dataSock = socket(AF_INET, SOCK_STREAM, 0);
	bind(dataSock, (struct sockaddr*)&ServAddrData, ServAddrDataLen);

	//Connect to the server on the command port
	commandSock = socket(AF_INET, SOCK_STREAM, 0);
	connect(commandSock, (struct sockaddr*)&ServAddrCommand, ServAddrCommandLen);
	printf("Connection established\n");

	//Listen on data port
	listen(dataSock, 2);
	s = accept(dataSock, (struct sockaddr*)&ServAddrDataTwo, &ServAddrDataTwoLen);
	printf("Connection established\n");
	
	write(commandSock, "RET dir.txt", 11);

	printf("command sent\n");
	n = read(s, listResults, 2048);
	//printf("%s", listResults);

	FILE *file;
	file = fopen("dir1.txt", "w");
	while(n>0)
	{
		fprintf(file, "%s", listResults);
	}

	write(commandSock, "quit", 4);

	free(listResults);

	close(s);
	close(dataSock);
	close(commandSock);

	return 0;
}
