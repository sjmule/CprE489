#include "header.h"

// program version string
const char *argp_program_version = "Token Ring Client 1.0";
// program bug address string
const char *argp_program_bug_address = "Scott Mueller <scotm1@iastate.edu>";
// program documentation string
static char doc[] = "Simple token ring workstation client";

// list of options supported
static struct argp_option options[] = 
{
	{"verbose", 'v', 0, 0, "Produce verbose output"},
	{"quite", 'q', 0, 0, "Don't produce any output"},
	{"silent", 's', 0, OPTION_ALIAS, 0},
	{"node-id", 'n', "ID", 0, "Character to identify this workstation by: a, b, or c"},
	{"server-port", 'h', "Port", 0, "The port number to host the server on"},
	{"client-port", 'c', "Port", 0, "The port number to connect to a server on"},
	{0}
};

//arugment structure to store the results of command line parsing
struct arguments
{
	// are we in verbose mode?
	int verbose_mode;
	// the node id
	char node_id;
	// the server port address
	int server_port;
	// the client port address
	int client_port;
};

/*
 * @brief     Callback to parse a command line argument
 * @param     key
 *                 The short code key of this argument
 * @param     arg
 *                 The argument following the code
 * @param     state
 *                 The state of the arg parser state machine
 * @return    0 if succesfully handeled the key, ARGP_ERR_UNKONWN if the key was uknown
 */
error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;
	switch(key)
	{
		case 'v':
			arguments->verbose_mode = 2;
			break;
		case 'q':
		case 's':
			arguments->verbose_mode = 0;
			break;
		case 'n':
			arguments->node_id = arg[0];
			break;
		case 'h':
			arguments->server_port = atoi(arg);
			break;
		case 'c':
			arguments->client_port = atoi(arg);
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

// The arg parser object
static struct argp argp = {&options, parse_opt, 0, doc};

// The server socket needs to be global so the thread can listen on it
int server_fd;

// The thread for listening on our socket
void listener(void)
{

}

int main(int argc, char** argv)
{
	struct arguments arguments;
	arguments.verbose_mode = 1;
	arguments.server_port = 0;
	arguments.client_port = 0;
	arguments.node_id = '0';
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	int client_fd, n, er;
	int err = 0;
	char DLE = 16;
    char SYN = 22;
    char STX = 2;
    char ETX = 3;
    char node_id, destAddr, sourceAddr, i;
	char *buffer = malloc(80 * sizeof(char));
	size_t *t = 0;
	size_t size = 0;

	if(arguments.server_port == 0)
	{
		printf("Please enter a port to run the server on using \"-h #####\"\n");
		exit(-1);
	}
	if(arguments.client_port == 0)
	{
		printf("Please enter a port to run the client on using \"-c #####\"\n");
		exit(-1);
	}
	if(arguments.node_id == '0')
	{
		printf("Please specify a node id using \"-n \%c\" where \%c is either: a, b, or c\n");
		exit(-1);
	}

	if(arguments.verbose_mode > 0)
	{
		printf("Node id: %c\n", arguments.node_id);
		printf("Running server on port: %d\n", arguments.server_port);
		printf("Connecting to client on port: %d\n", arguments.client_port);
	}

	if(arguments.node_id == 'c')
	{
		client_fd = Client(arguments.client_port);
		server_fd = Server(arguments.server_port);
	}
	else
	{
		server_fd = Server(arguments.server_port);
		client_fd = Client(arguments.client_port);
	}

	if(arguments.verbose_mode == 2) printf("Attempting to create socket listener thread\n");
	pthread_t socket_listener;
	err = pthread_create(&socket_listener, NULL, (void*)listener, NULL);
	if(err != 0)
	{
		perror("pthread_create encountered an error");
		exit(-1);
	}
	if(arguments.verbose_mode == 2) printf("Attempting to join socket listener thread\n");
	err = pthread_join(socket_listener, NULL);
	if(err != 0)
	{
		perror("failed joining threads");
		exit(-1);
	}

	for(;;)
	{
		if(arguments.node_id == 'a')
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
		else if(arguments.node_id == 'b')
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