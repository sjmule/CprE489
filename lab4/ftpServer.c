#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct sockaddr_in ServAddrCommand, ClientAddrCommand, ServAddrPort1, ServAddrPort2;

int main(int args, char** argv)
{
	int s, n, commandSock, port1Sock, port2Sock, ClientAddrCommandLen;
	socklen_t ServAddrCommandLen;
	socklen_t ServAddrPort1Len;
	socklen_t ServAddrPort2Len;
	char *command = malloc(80 * sizeof(char));
	size_t commandLine = 80;
	
	//Configure struct for command port
	ServAddrCommand.sin_family = AF_INET;
	ServAddrCommand.sin_port = htons(54839);
	ServAddrCommand.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServAddrCommandLen = sizeof(ServAddrCommand);
	
	//Bind the command port
	commandSock = socket(AF_INET, SOCK_STREAM, 0);
	bind(commandSock, (struct sockaddr*)&ServAddrCommand, ServAddrCommandLen);
	
	//Listen on the command port
	listen(commandSock, 2);
	s = accept(commandSock, (struct sockaddr*)&ClientAddrCommand, &ClientAddrCommandLen);
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
			char *new_port1;
			new_port1 = strtok(command, " ");
			new_port1 = strtok(NULL, " ");
			command = "";
			
			//Create new sockaddr struct to use on new port
			ServAddrPort1.sin_family = AF_INET;
			ServAddrPort1.sin_port = htons(atoi(new_port1));
			ServAddrPort1.sin_addr.s_addr = inet_addr("127.0.0.1");
			ServAddrPort1Len = sizeof(ServAddrPort1);

			//Create new socket and connect on new port
			port1Sock = socket(AF_INET, SOCK_STREAM, 0);
			connect(port1Sock, (struct sockaddr*)&ServAddrPort1, ServAddrPort1Len);

			//List the directory
			printf("Listing directory\n");
			system("ls > dir.txt");
			FILE *dir;
			dir = fopen("dir.txt", "r");
			if(dir == 0)
			{
				perror("Cannot open second file");
				exit(-1);
			}
			
			//Send the directory
			char *str = malloc(2048 * sizeof(char));
			int nread = 0;
			nread = fread(str,1,2048,dir);
			printf("%s", str);
			write(port1Sock, str, nread);
			fclose(dir);
			free(str);
			close(port1Sock);
		}
		if(strncmp(command, "RET", 3) == 0)
		{
			char *file_name;
			char *new_port2;
			file_name = strtok(command, " ");
			file_name = strtok(NULL, " ");
			new_port2 = strtok(NULL, " ");
			command = "";
			
			//Create new sockaddr struct to use on new port
			ServAddrPort2.sin_family = AF_INET;
			ServAddrPort2.sin_port = htons(atoi(new_port2));
			ServAddrPort2.sin_addr.s_addr = inet_addr("127.0.0.1");
			ServAddrPort2Len = sizeof(ServAddrPort2);

			//Create new socket and connect on new port
			port2Sock = socket(AF_INET, SOCK_STREAM, 0);
			connect(port2Sock, (struct sockaddr*)&ServAddrPort2, ServAddrPort2Len);

			//Open file to read and send
			FILE *file;
			file = fopen(file_name, "r");
			if(file == 0)
			{
				perror("Cannot open second file");
				exit(-1);
			}

			//send the file
			char *line = malloc(2048 * sizeof(char));
			int nread = 0;
			nread = fread(line,1,2048,file);
			while(nread > 0)
			{
				write(port2Sock, line, nread);
				nread = fread(line,1,2048,file);
			}
			fclose(file);
			free(line);
			free(file_name);
			free(new_port2);
			close(port2Sock);
		}
	}
	close(s);
	close(commandSock);
	return 0;
}
