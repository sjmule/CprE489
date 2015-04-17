#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void main(){
	char buffer[80];
	
	char DLE = 16;
	char SYN = 22;
	char STX = 2;
	char ETX = 3;
	char destAddr;
	char sourceAddr;
	char *text = NULL;//malloc(100 * sizeof(char));
	char i;	
	size_t size =0;
	int er;
	//sprintf(buffer,"%c%c%c%c%c%c%s%c%c", SYN,SYN,DLE,STX,destAddr,sourceAddr, text,DLE, ETX);
	
	//while(1){
		printf("When ready to enter a message please type in the destination node address (a,b,or c)\n");
		//scanf(" %c",&i);
		i = fgetc(stdin);
		fgetc(stdin);
		//fflush(stdin);
		//fflush(stdout);
		//printf("%c\n",i);
		printf("When ready enter message of length 72 characters to send to node %c:",i);
		//fflush(stdin);
		//fflush(stdout);
		//printf("");
		//fgets(text,sizeof(text),stdin);
		er = getline(&text, &size, stdin);
		printf("er=%d\n",er);
		/*while((er = getline(&text, &size, stdin))<0)
		{
			//er = getline(&text,size, stdin);
			printf("%d\n",er);
			if(er < 0)
			{
				perror("It fucked up");
				exit(-1);
			}
		}*/
		/*if ( fgets (text, sizeof(text) , stdin) != NULL ) {
    			puts (text);
		}*/
		//printf("bytes: %d\n",er);
		printf("%s.\n",text);
	
	
	
	
	//}
	//sprintf(buffer,"%c%c%c%c%c%c%s%c%c", SYN,SYN,DLE,STX,destAddr,sourceAddr, text,DLE, ETX);
	//printf("%s\n",buffer);
	
}

/*char[] stuff(char[] stuffme){
	char[72] stuffed;
	
	
}*/

