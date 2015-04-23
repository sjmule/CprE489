#include "header.h"

char DLE = 'm';
char SYN = 22;
char STX = 2;
char ETX = 3;

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

int main(int argc, char** argv)
{
	struct arguments arguments;
	arguments.verbose_mode = 1;
	arguments.server_port = 0;
	arguments.client_port = 0;
	arguments.node_id = -1;
	arguments.num_workstations = 3;
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	int server_fd, client_fd, n, er, destAddr, rv;
	int err = 0;
	int check = 0;
    char i;
	char *buffer = NULL;
	char *textBuffer = NULL;
	char *textBuffer2 = NULL;
	char *text = NULL;
	size_t *t = 0;
	size_t size = 0;
	struct pollfd fds[2];

	if(arguments.node_id == -1)
	{
		printf("Please specify a node id using \"-i #\"\n");
		exit(-1);
	}

	if(arguments.server_port == 0)
	{
		check++;
		arguments.server_port = 50980 + arguments.node_id;
	}
	if(arguments.client_port == 0)
	{
		check++;
		if(arguments.node_id != (arguments.num_workstations-1))
		{
			arguments.client_port = 50981 + arguments.node_id;
		}
		else
		{
			arguments.client_port = 50980;
		}
	}

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

	if(arguments.node_id == (arguments.num_workstations-1))
	{
		client_fd = Client(arguments.client_port);
		server_fd = Server(arguments.server_port);
	}
	else
	{
		server_fd = Server(arguments.server_port);
		client_fd = Client(arguments.client_port);
	}

	fds[0].fd = stdin;
	fds[0].events = POLLIN | POLLPRI;

	fds[1].fd = server_fd;
	fds[1].events = POLLIN | POLLPRI;

	for(;;)
	{
		rv = poll(fds, 2, -1);
		if(arguments.node_id == 0)
		{
			printf("When ready to enter a message please type in the destination node address\n");

        	i = fgetc(stdin);
	        fgetc(stdin);
	        destAddr = atoi(i);

        	printf("When ready enter message of length 80 characters to send to node %c:", i);

        	er = getline(&text, &size, stdin);

        	textBuffer = stuff(text);

			sprintf(buffer,"%c%c%c%d%d%d%s%c%c", SYN, SYN, DLE, STX, destAddr, arguments.node_id, textBuffer, DLE, ETX);
			printf("%s\n",buffer);

        	write(client_fd, buffer, er);
			if(strncmp(text, "!!quit!!", 8) == 0)
			{
				break;
			}
		}
		else if((arguments.node_id > 0) && (arguments.node_id < (arguments.num_workstations-1)))
		{
			n = read(server_fd, buffer, 80);
			textBuffer2 = destuff(buffer);
			printf("%s\n", textBuffer2);
			write(client_fd, buffer, n);
			if(strncmp(buffer, "!!quit!!", 8) == 0)
			{
				break;
			}
			memset(buffer, '\0', 80);
		}
		else if(arguments.node_id == (arguments.num_workstations-1))
		{
			n = read(server_fd, buffer, 80);
			textBuffer2 = destuff(buffer);
			printf("%s\n", buffer);
			if(strncmp(buffer, "!!quit!!", 8) == 0)
			{
				break;
			}
			memset(buffer, '\0', 80);
		}
	}

	close(client_fd);
	close(server_fd);
	free(buffer);

	return 0;
}