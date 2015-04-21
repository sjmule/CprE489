#include "header.h"

int server_fd, client_fd;

void listener(void)
{

}

int main(int argc, char** argv)
{
	int server_port, client_port, n, er;
	int err = 0;
	char DLE = 16;
    char SYN = 22;
    char STX = 2;
    char ETX = 3;
    char node_id, destAddr, sourceAddr, i;
	char *buffer = malloc(80 * sizeof(char));
	size_t *t = 0;
	size_t size = 0;
	node_id = argv[1][0];

	if(DEBUG) printf("Node id: %c\n", node_id);
	
	printf("Please enter the port to run the server on:\n");
	while((n = getline(&buffer, &t, stdin)) < 0);
	server_port = atoi(buffer);
	if(DEBUG) printf("Server port: %d\n", server_port);

	printf("Please enter the port to connect as a client on:\n");
	while((n = getline(&buffer, &t, stdin)) < 0);
	client_port = atoi(buffer);
	if(DEBUG) printf("Client port: %d\n", client_port);

	if(node_id == 'c')
	{
		client_fd = Client(client_port);
		server_fd = Server(server_port);
	}
	else
	{
		server_fd = Server(server_port);
		client_fd = Client(client_port);
	}

	if(DEBUG) printf("Attempting to create socket listener thread\n");
	pthread_t socket_listener;
	err = pthread_create(&socket_listener, NULL, (void*)listener, NULL);
	if(err != 0)
	{
		perror("pthread_create encountered an error");
		exit(-1);
	}
	if(DEBUG) printf("Attempting to join socket listener thread\n");
	err = pthread_join(socket_listener, NULL);
	if(err != 0)
	{
		perror("failed joining threads");
		exit(-1);
	}

	for(;;)
	{
		if(node_id == 'a')
		{
			printf("When ready to enter a message please type in the destination node address (a,b,or c)\n");

        	i = fgetc(stdin);
        	fgetc(stdin);

        	printf("When ready enter message of length 72 characters to send to node %c:\n",i);

        	er = getline(&buffer, &size, stdin);
        	printf("er=%d\n",er);
        	printf("%s\n",buffer);

        	write(client_fd, buffer, er);
			if(strncmp(buffer, "!!quit!!", 8) == 0)
			{
				break;
			}
		}
		else if(node_id == 'b')
		{
			n = read(server_fd, buffer, 80);
			printf("%s\n", buffer);
			write(client_fd, buffer, n);
			if(strncmp(buffer, "!!quit!!", 8) == 0)
			{
				break;
			}
			memset(buffer, '\0', 80);
		}
		else
		{
			n = read(server_fd, buffer, 80);
			printf("%s\n", buffer);
			if(strncmp(buffer, "!!quit!!", 8) == 0)
			{
				break;
			}
			memset(buffer, '\0', 80);
		}
	}

	free(buffer);
	close(server_fd);
	close(client_fd);

	return 0;
}