#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct sockaddr_in ServAddrCommand, ClientAddrCommand, ServAddrData, ClientAddrData;

int main(int args, char** argv)
{
	int s, n, commandSock, dataSock, ClientAddrCommandLen, ClientAddrDataLen;
	socklen_t ServAddrCommandLen;
	socklen_t ServAddrDataLen;
	char *command = malloc(80 * sizeof(char));
	size_t commandLine = 80;
	
	//Configure struct for command port
	ServAddrCommand.sin_family = AF_INET;
	ServAddrCommand.sin_port = htons(54811);
	ServAddrCommand.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServAddrCommandLen = sizeof(ServAddrCommand);

	//Configure struct for data port
	ServAddrData.sin_family = AF_INET;
	ServAddrData.sin_port = htons(54812);
	ServAddrData.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServAddrDataLen = sizeof(ServAddrData);
	
	//Bind the command port
	commandSock = socket(AF_INET, SOCK_STREAM, 0);
	bind(commandSock, (struct sockaddr*)&ServAddrCommand, ServAddrCommandLen);
	
	//Listen on the command port
	listen(commandSock, 2);
	s = accept(commandSock, (struct sockaddr*)&ClientAddrCommand, &ClientAddrCommandLen);
	printf("Connection established\n");

	//Connect on the data port
	dataSock = socket(AF_INET, SOCK_STREAM, 0);
	connect(dataSock, (struct sockaddr*)&ServAddrData, ServAddrDataLen);
	printf("Connection established\n");
	
	for(;;)
	{
		n = read(s, command, commandLine);
		printf("%s\n", command);
		if(strncmp(command, "quit", 4)==0)
		{
			free(command);
			printf("Exiting\n");
			break;
		}
		if(strncmp(command, "LIST", 4) == 0)
		{
			system("ls > dir.txt");
			FILE *dir;
			dir = fopen("dir.txt", "r");
			char *str = malloc(1024 * sizeof(char));
			size_t *t = NULL;
			getline(&str, t, dir);
			while(!feof(dir))
			{
				write(s, str, sizeof(str));
			}
			fclose(dir);
			free(str);
		}
	}

	return 0;
}
