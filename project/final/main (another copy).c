#include "header.h"
char DLE = 'm';//16;
char SYN = 's';//22;
char STX = 'b';//2;
char ETX = 'e';//3;
int DEBUG;

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
	{"node-id", 'i', "ID", 0, "Number to identify this workstation by, start indexing with 0"},
	{"server-port", 'h', "PORT", 0, "The port number to host the server on"},
	{"client-port", 'c', "PORT", 0, "The port number to connect to a server on"},
	{"number", 'n', "NUMBER", 0, "Optional, specify number of workstations, default 3"},
	{0}
};

//arugment structure to store the results of command line parsing
struct arguments
{
	// are we in verbose mode?
	int verbose_mode;
	// the node id
	int node_id;
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

struct data
{
	int dest;
	int source;
	char* text;
};

int main(int argc, char** argv)
{
	// Define defaults for the parser
	struct arguments arguments;
	struct data data;
	arguments.verbose_mode = 1;
	arguments.server_port = 0;
	arguments.client_port = 0;
	arguments.node_id = -1;
	arguments.num_workstations = 3;
	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	DEBUG = arguments.verbose_mode;

	int server_fd, client_fd, er, destAddr, rv, stdin_flags, fd_flags;
	int err = 0;
	int check = 0;
    char i;
	char* buffer = malloc(90 * sizeof(char));
	char* textBuffer = NULL;
	char* textBuffer2 = NULL;
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

	stdin_flags = fcntl(stdin, F_GETFL);
	stdin_flags |= O_NONBLOCK;
	fcntl(stdin, F_SETFL, stdin_flags);

	fd_flags = fcntl(server_fd, F_GETFL);
	fd_flags |= O_NONBLOCK;
	fcntl(server_fd, F_SETFL, fd_flags);

	for(;;)
	{
		int st = 0;
		int fs = 0;
		int n = 0;
		int h = 0;//for testing

		printf("When ready to enter a message please type in the destination node address\n");
		printf("h%d\n",h);h++;
		while(1)
		{
			printf("h%d\n",h);h++;
			if((n = read(stdin, buffer, 80)) < 1)
			{
				st = 1;
				break;
			}
			if((n = read(server_fd, buffer, 90)) < 1)
			{
				fs = 1;
				break;
			}
		}

		if(st = 1)
		{
			destAddr = atoi(buffer);
			stdin_flags = fcntl(stdin, F_GETFL);
			stdin_flags |= ~O_NONBLOCK;
			fcntl(stdin, F_SETFL, stdin_flags);
			printf("When ready enter message of length 80 characters to send to node %d:",destAddr);
			read(stdin, textBuffer, 80);
			textBuffer = stuff(textBuffer);
			sprintf(textBuffer2,"%c&%c&%c&%c&%d&%d&%s&%c&%c&", SYN,SYN,DLE,STX,destAddr,arguments.node_id, textBuffer,DLE, ETX);
			printf("%s\n", textBuffer2);
			write(client_fd, textBuffer2, sizeof(textBuffer2));
			stdin_flags = fcntl(stdin, F_GETFL);
			stdin_flags |= O_NONBLOCK;
			fcntl(stdin, F_SETFL, stdin_flags);
		}
		if(fs = 1)
		{
			data = deserialize(buffer);
			if(data.dest == arguments.node_id)
			{
				printf("Message from node %d:\n%s\n", data.dest, data.text);
			}
			else
			{
				write(client_fd, buffer, n);
			}
		}

		memset(buffer, '\0', 90);
		memset(textBuffer, '\0', sizeof(textBuffer));
		memset(textBuffer2, '\0', sizeof(textBuffer2));
		memset(data.text, '\0', sizeof(data.text));
		data.dest = NULL;
		data.source = NULL;
	}

	close(client_fd);
	close(server_fd);
	free(buffer);

	return 0;
}