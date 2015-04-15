#include "header.h"

int Server(int port)
{
	struct sockaddr_in myaddr, otheraddr;
	struct hostent *myname;

	int s, fd, otherlength;
	FILE *fdopen(), *fp;
	char *hostname = "localhost", ch;
	int hostnamelength;

	pid_t pid;

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) printf("No go server\n");
	myname = gethostbyname(hostname);

	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family  = AF_INET;
	myaddr.sin_port = htons(port); //54841
	bcopy(myname->h_addr_list[0], &myaddr.sin_addr, myname->h_length);
	bind(s, &myaddr, sizeof(myaddr));

	listen(s, 1);
	if(DEBUG) printf("Server listening on port: %d\n", port);

	otherlength = sizeof(otheraddr);
	fd = accept(s, &otheraddr, &otherlength);

	printf("Connected\n");

	return(fd);
}