#include "introduceerror.h"

void generateCRC(char* data, int CRCfield)
{
	
}

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		printf("Please input bit error rate as command line argument.\n");
		exit(-1);
	}

	char* buffer = malloc(1024 * sizeof(char));
	size_t size = 0;

	printf("Feed me keyboard input\n");
	getline(&buffer, &size, stdin);


	printf("%s\n", buffer);

	return 0;
}