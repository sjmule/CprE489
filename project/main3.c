#include "header.h"

int main(int argc, char** argv)
{
	int fd, n;
	char *buffer = malloc(80 * sizeof(char));
	char *my_node = argv[3];
	//size_t *t = NULL;
	size_t *t = malloc(sizeof(size_t));
	*t = (size_t)1024;
	
	printf("%s\n", my_node);

	if(strncmp(argv[1], "client", 6) == 0)
	{
		fd = Client(atoi(argv[2]));
		for(;;)
		{
			while((n = getline(&buffer, t, stdin)) < 0);
			write(fd, buffer, sizeof(buffer));
		}
	}

	if(strncmp(argv[1], "server", 6) == 0)
	{
		fd = Server(atoi(argv[2]));
		for(;;)
		{
			read(fd, buffer, 80);
			printf("%s\n", buffer);
		}
	}

	close(fd);

	return 0;
}