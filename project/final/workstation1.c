#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>


char* stuff(char*);

void main(){
	char buffer[80];
	char * textBuffer = NULL;
   
    char DLE = 16;
    char SYN = 22;
    char STX = 2;
    char ETX = 3;
    char destAddr;
    char sourceAddr;
    char *text = NULL;
    char i;   
    size_t size =0;
    int er;
   
    //while(1){
        printf("When ready to enter a message please type in the destination node address (a,b,or c)\n");

        i = fgetc(stdin);
        fgetc(stdin);

        printf("When ready enter message of length 72 characters to send to node %c:",i);

        er = getline(&text, &size, stdin);
        printf("er=%d\n",er);
        printf("%s\n",text);

	//sprintf(buffer,"%c%c%c%c%c%c%s%c%c", SYN,SYN,DLE,STX,destAddr,sourceAddr, text,DLE, ETX);
	//printf("%s\n",buffer);

	//textBuffer = stuff(text);
	
}

char* stuff(char * stuffme){
	char * stuffed = NULL;
	char text[150];
	char i;
	int h = 0;//for testing purposes
	int k=0;
	int currentLoc = 0;
	int stuffmeLoc = 0;
	size_t cpySize;
	int cpySizeInt;
	//takes in the text stuffs it then cuts it down to 72 characters
	//printf("start of while loop h)%d\n",h);h++;
	while(stuffme[stuffmeLoc] != '\0'){//chaneg to a end delimiter
		//printf("appending single chars h)%d\n",h);h++;
		text[currentLoc] = stuffme[stuffmeLoc];
		
		if(stuffme[stuffmeLoc]=='d'){
			if(stuffme[stuffmeLoc+1]=='l'){
				if(stuffme[stuffmeLoc+2]=='e'){
				//printf(" found dle appending h)%d\n",h);h++;
					currentLoc++;
					text[currentLoc] = 'l';
					currentLoc++;
					text[currentLoc] = 'e';
					currentLoc++;
					text[currentLoc] = 'd';
					currentLoc++;
					text[currentLoc] = 'l';
					currentLoc++;
					text[currentLoc] = 'e';
					stuffmeLoc++;
					stuffmeLoc++;
				}
			}
		}
		stuffmeLoc++;
		currentLoc++;
	}
	printf("%d\n",currentLoc);
	if(currentLoc >= 72){
		cpySize = sizeof(72*i);
		cpySizeInt = 72;
	}
	else{
		cpySize =strlen(text);
		cpySizeInt = strlen(text);
	}
	printf("%d\n",cpySizeInt);
	//printf("copying 72 chars h)%d\n",h);h++;
	//strncpy(stuffed,&text,cpySize);
	for(k;k<cpySizeInt;k++){
		stuffed[k]=text[k];
	}
	//printf("print all data h)%d\n",h);h++;
	printf("               not stuffed: %s\n",stuffme);
	//printf("printed stuffme h)%d\n",h);h++;
	printf("                   stuffed: %s\n",text);
	//printf("printed text h)%d\n",h);h++;
	printf("stuffed and 72 characters: %s\n",stuffed);
	//printf("print text 72 h)%d\n",h);h++;
	
	return stuffed;
	
}

 
