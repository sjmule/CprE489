#include "header.h"

int server_fd, client_fd;

void server_connect(void* args)
{
	int port = (int) args;
	server_fd = Server(port);
}

int main(int argc, char** argv)
{
	int client_fd, server_fd, client_port, server_port, n;
	char *node_name = malloc(20 * sizeof(char));
	char *buffer = malloc(80 * sizeof(char));
	int t = 80;
	int err;

	printf("Input node name:\n");
	while((n = getline(&node_name, &t, stdin)) < 0);

	printf("Input server port:\n");
	while((n = getline(&buffer, &t, stdin)) < 0);
	
	//thread for server here
	server_port = atoi(buffer);
	pthread_t server_thread;
	err = pthread_create(&server_thread, NULL, (void *)server_connect, (void *)server_port);
	if(err != 0)
	{
		perror("pthread_create encountered an error");
		exit(-1);
	}

	memset(buffer, 0, 80);

	printf("Input client port:\n");
	while((n = getline(&buffer, &t, stdin)) < 0);
	client_port = atoi(buffer);
	memset(buffer, 0, 80);

	printf("Is the server started?\n");
	while((n = getline(&buffer, &t, stdin)) < 0);

	client_port = Client(client_port);
	memset(buffer, 0, 80);

	if(strncmp(argv[1], "client", 6) == 0)
	{
		for(;;)
		{
			while((n = getline(&buffer, &t, stdin)) < 0);
			write(client_fd, buffer, sizeof(buffer));
		}
	}

	if(strncmp(argv[1], "server", 6) == 0)
	{
		for(;;)
		{
			read(server_fd, buffer, 80);
			printf("%s\n", buffer);
		}
	}

	return 0;
}