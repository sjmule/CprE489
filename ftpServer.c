#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct sockaddr_in ServAddr, ClientAddr;

int main(int args, char** argv)
{
	int s, fd, ClientAddrLen;
	ClientAddrLen = sizeof(ClientAddr);

	ServAdd.sin_family = AF_INET;
	ServAdd.sin_port = 21;
	ServAdd.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	fd = socket(AF_INET, SOCK_STREAM, 0);
	bind(fd, (struct sockaddr*)&ServAddr, sizeof(ServAddr));
	listen(fd, 2);

	
	return 0;
}
