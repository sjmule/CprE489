#include "header.h"

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		printf("Please enter command line argument of node id\n");
		return 0;
	}
	int server_port, client_port, server_fd, client_fd, n;
	char node_id[2];
	strcpy(node_id, argv[1]);
	char *buffer = malloc(80 * sizeof(char));
	size_t *t = 0;

	if(DEBUG) printf("Node id: %c\n", node_id);
	printf("Please enter the port to run the server on:\n");
	while((n = getline(&buffer, &t, stdin)) < 0);
	server_port = atoi(buffer);
	if(DEBUG) printf("Server port: %d\n", server_port);

	printf("Please enter the port to connect as a client on:\n");
	while((n = getline(&buffer, &t, stdin)) < 0);
	client_port = atoi(buffer);
	if(DEBUG) printf("Client port: %d\n", client_port);

	if(strncmp(node_id, 'c', 1) == 0)
	{
		client_fd = Client(client_port);
		server_fd = Server(server_port);
	}
	else
	{
		server_fd = Server(server_port);
		client_fd = Client(client_port);
	}
	for(;;)
	{
		if(strncmp(node_id, 'a', 1) == 0)
		{
			while((n = getline(&buffer, &t, stdin)) < 0);
			write(client_fd, buffer, sizeof(buffer));
		}
		else if(strncmp(node_id, 'b', 1) == 0)
		{
			n = read(server_fd, buffer, 80);
			printf("%s\n", buffer);
			write(client_fd, buffer, sizeof(buffer));
		}
		else
		{
			n = read(server_fd, buffer, 80);
			printf("%s\n", buffer);
		}
	}

	return 0;
}