#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

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

	otherlength = sizeof(otheraddr);
	fd = accept(s, &otheraddr, &otherlength);

	printf("Connected\n");

	return(fd);
}

int Client(int port)
{
	int s;
	int n;
	int code;
	FILE *fp;
	char *otherhostname="localhost", ch, thishostname[256];

	struct hostent *otherhost;
	struct sockaddr_in otheraddr;

	pid_t pid;

	code = gethostname(thishostname, sizeof(thishostname));

	bzero(&otheraddr, sizeof(otheraddr));

	otheraddr.sin_family = AF_INET;
	otheraddr.sin_port = htons(port);
	
	s = socket(AF_INET, SOCK_STREAM, 0);

	otherhost = gethostbyname(otherhostname);
	bcopy(otherhost->h_addr_list[0], &otheraddr.sin_addr, otherhost->h_length);

	n = connect(s, &otheraddr, sizeof(otheraddr));

	printf("Connected\n");

	if ( n < 0)
		return(n);
	else
		return(s);
}

int main(int argc, char** argv)
{
	char *my_node_id = argv[1];
	int client_fd, server_fd, n;
	pid_t pid;
	char *buffer = malloc(80 * sizeof(char));
	size_t *t = malloc(sizeof(size_t));
	*t = (size_t)1024;

	client_fd = Client(atoi(argv[2]));

	server_fd = Server(atoi(argv[3]));

	if ((pid = fork()) > 0) 	/* This is the parent     */
	{
		for(;;)
		{
			while((n = getline(&buffer, t, stdin)) < 0);
			write(server_fd, buffer, sizeof(buffer));
		}
  	} 
  	else if (pid == 0) 			/* This is the child      */  
    {
    	for(;;)
    	{
    		read(client_fd, buffer, 80);
    		if(strncmp(buffer, my_node_id, 1))
    		{
				printf("%s\n", buffer);
			}
    	}
    }
  	else
    	printf("fork failed\n");


	return 0;
}