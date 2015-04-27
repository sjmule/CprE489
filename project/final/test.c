#include "header.h"

int main(int argc, char** argv)
{
	int server_fd, client_fd;
	char* buffer = malloc(80 * sizeof(char));

	client_fd = Client(66666);
	server_fd = Server(66667);

	getline();

	return 0;
}