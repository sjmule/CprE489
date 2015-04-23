#ifndef HEAD_H
#define HEAD_H

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
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <argp.h>
#include <poll.h>

extern char DLE;
extern char SYN;
extern char STX;
extern char ETX;

int Server(int), Client(int);
char* stuff(char*), destuff(char*);

#endif
