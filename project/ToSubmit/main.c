/**
 *  A simple Token Ring prgram
 *  Authors: Scott Mueller and Brian Moran
 */

#include "header.h"

char DLE = '16';//16;
char SYN = '22';//22;
char STX = '2';//2;
char ETX = '3';//3;
int DEBUG;

// Program version string
const char *argp_program_version = "Token Ring Client 1.0";
// Program bug address string
const char *argp_program_bug_address = "Scott Mueller <scotm1@iastate.edu> | Brian Moran <bmoran@iastate.edu>";
// Program documentation string
static char doc[] = "Simple token ring workstation client";

// List of options supported
static struct argp_option options[] = 
{
	{"verbose", 'v', 0, 0, "Produce verbose output"},
	{"quite", 'q', 0, 0, "Don't produce any output"},
	{"silent", 's', 0, OPTION_ALIAS, 0},
	{"node-id", 'i', "ID", 0, "Number to identify this workstation by, start indexing with 0"},
	{"server-port", 'h', "PORT", 0, "The port number to host the server on"},
	{"client-port", 'c', "PORT", 0, "The port number to connect to a server on"},
	{"number", 'n', "NUMBER", 0, "Optional, specify number of workstations, default 3"},
	{0}
};

// Arugment structure to store the results of command line parsing
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
	// the number of workstations in the ring
	int num_workstations;
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
error_t parse_opt(int key, char* arg, struct argp_state *state)
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
		case 'i':
			arguments->node_id = atoi(arg);
			break;
		case 'h':
			arguments->server_port = atoi(arg);
			break;
		case 'c':
			arguments->client_port = atoi(arg);
			break;
		case 'n':
			arguments->num_workstations = atoi(arg);
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

// The arg parser object
static struct argp argp = {&options, parse_opt, 0, doc};

// The structure of the socket data
struct data
{
	char dest;
	int source;
	char* text;
};

int main(int argc, char** argv)
{
	// Define defaults for the parser
	struct arguments arguments;
	arguments.verbose_mode = 1;
	arguments.server_port = 0;
	arguments.client_port = 0;
	arguments.node_id = -1;
	arguments.num_workstations = 3;
	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	DEBUG = arguments.verbose_mode;

	struct data data;

	fd_set rfds;

	int server_fd, client_fd, er, n, destAddr, rv, stdin_flags, fd_flags, retval, fdmax;
	int err = 0;
	int check = 0;
    char j;
	char* buffer = malloc(127 * sizeof(char));
	char* buffer2 = malloc(127 * sizeof(char));
	char* textBuffer = malloc(127 * sizeof(char));
	char* textBuffer2 = malloc(127 * sizeof(char));
	char* textBuffer3 = malloc(127 * sizeof(char));
	char* textBuffer4 = malloc(127 * sizeof(char));
	char* text = NULL;
	size_t* t = 0;
	size_t size = 0;

	// Verify the user has set a node id
	if(arguments.node_id == -1)
	{
		printf("Please specify a node id using \"-i #\"\n");
		exit(-1);
	}

	// Check if the user has defined port numbers, if not, use defaults
	if(arguments.server_port == 0)
	{
		check++;
		// Default server port numbers start at 50980 and increase based on the node id
		arguments.server_port = 50980 + arguments.node_id;
	}
	if(arguments.client_port == 0)
	{
		check++;
		// If we are not the last node in the ring, start defining client port numbers at 50981 then increase based on node id
		if(arguments.node_id != (arguments.num_workstations-1))
		{
			arguments.client_port = 50981 + arguments.node_id;
		}
		// If this is the last node in the ring, define the client port to be the base server port to close the ring
		else
		{
			arguments.client_port = 50980;
		}
	}

	// Print some information to the user if not running in silent mode
	if(arguments.verbose_mode > 0)
	{
		printf("Expected number of workstations in ring: %d, if this is incorrect, please restart and specify a number of workstations using \"-n #\"\n", arguments.num_workstations);
		printf("Node id: %d\n", arguments.node_id);
		printf("Running server on port: %d\n", arguments.server_port);
		printf("Connecting to client on port: %d\n", arguments.client_port);
		if(check == 2)
		{
			printf("If you would like to specify your own ports please set them with \"-h #####\" and \"-c #####\"\n");
		}
	}

	// If this is the last workstation in the ring, assume the server is started and connect to it, then start our server
	if(arguments.node_id == (arguments.num_workstations-1))
	{
		client_fd = Client(arguments.client_port);
		server_fd = Server(arguments.server_port);
	}
	// If this is not the last workstation in the ring, start our server, then wait for a connection before connecting to our client
	else
	{
		server_fd = Server(arguments.server_port);
		client_fd = Client(arguments.client_port);
	}

	for(;;)
	{
		// Watch stdin and our socket
		FD_ZERO(&rfds);
		FD_SET(STDIN_FILENO, &rfds);
		FD_SET(server_fd, &rfds);
		fdmax = server_fd;
		
		printf("When ready to enter a message please type in the destination node address\n");
		
		// Wait for one of our file descriptors to have data
		n = select(fdmax+1, &rfds, NULL, NULL, NULL);

		if((n == -1 ) && (errno == EINTR)) 
		   continue;
	  	if(n == -1)
	  	{	
	  		printf("Something broke\n");
	  		exit(-1);
	  	}

		if(FD_ISSET(STDIN_FILENO, &rfds))
		{
			// Standard input has data to be read
			// Get the destination node
			destAddr = fgetc(stdin);
			j = fgetc(stdin);
			printf("When ready enter message of length 80 characters to send to node %c:\n", destAddr);
			// Get the message text
			getline(&textBuffer, &size, stdin);
			// Ready the message text to be sent
			textBuffer2 = trim(textBuffer);
			textBuffer3 = stuff(textBuffer2);
			sprintf(textBuffer4,"%c&%c&%c&%c&%c&%d&%s&%c&%c&", SYN,SYN,DLE,STX,destAddr,arguments.node_id, textBuffer3,DLE, ETX);
			write(client_fd, textBuffer4, strlen(textBuffer4));
		}
		else if((n > 0 ) && (FD_ISSET(server_fd, &rfds)))
		{
			// Our socket has data to be read
			// Read the data
			n = read(server_fd, buffer, 90);
			strcpy(buffer2, buffer);
			// Decrypt the message
			data = deserialize(buffer);
			int a = data.dest - '0';
			// Check if the message is for us, print if it is
			if(a == arguments.node_id)
			{
				printf("Message from node %d:%s\n", a, data.text);
			}
			// If the message is not for us, send it to the next guy
			else
			{
				write(client_fd, buffer2, strlen(buffer2));
			}
		}

		memset(buffer, '\0', 127);
		memset(buffer2, '\0', 127);
		memset(textBuffer, '\0', sizeof(textBuffer));
		memset(textBuffer2, '\0', sizeof(textBuffer2));
		memset(&data, 0, sizeof(data));
	}

	close(client_fd);
	close(server_fd);
	free(buffer);

	return 0;
}