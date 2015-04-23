#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>


char* stuff(char*);
char* destuff(char*);

void main(){
	char buffer[80];
	char * textBuffer = NULL;
	char * textBuffer2 = NULL;
   
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

        printf("When ready enter message of length 80 characters to send to node %c:",i);

        er = getline(&text, &size, stdin);
        //printf("er=%d\n",er);
        //printf("%s\n",text);

	sprintf(buffer,"%c%c%c%c%c%c%s%c%c", SYN,SYN,DLE,STX,destAddr,sourceAddr, text,DLE, ETX);
	printf("%s\n",buffer);

	textBuffer = stuff(text);
	textBuffer2 = destuff(textBuffer);
}

char* stuff(char * stuffme){
	char * stuffed = NULL;
	char * stuffedDone = malloc(sizeof(char)*80);
	char text[150];
	char DLE = 'm';//change for tesing but should be dle = 16 
	int h = 0;//for testing purposes
	int currentLoc = 0;
	int stuffmeLoc = 0;
	int cpySizeInt;
	
	//takes in the text stuffs it then cuts it down to 72 characters
	//printf("start of while loop h)%d\n",h);h++;
	while(stuffme[stuffmeLoc] != '\0' || currentLoc == 80){//chaneg to a end delimiter
		//printf("appending single chars h)%d\n",h);h++;
		text[currentLoc] = stuffme[stuffmeLoc];
		
		if(stuffme[stuffmeLoc]==DLE){
			currentLoc++;
			text[currentLoc] = DLE;
		}
		stuffmeLoc++;
		currentLoc++;
	}
	/*if(currentLoc != 80){
		text[currentLoc+1] = '\0';
	}
	else{text[80] = '\0';}*/
	
	//printf("%d\n",currentLoc);
	
	if(currentLoc >= 80){
		cpySizeInt = 80;
		//printf("greater than 80\n");
	}
	else{
		cpySizeInt = strlen(text);
		//printf("not greater than 80\n");
	}
	//printf("%d\n",cpySizeInt);
	
	stuffed = text;
	strncat(stuffedDone,stuffed,cpySizeInt);
	
	//printf("              not stuffed: %s\n",stuffme);
	//printf("                  stuffed: %s\n",text);
	printf("stuffed and 80 characters: %s\n",stuffedDone);
	
	return stuffed;
	
}

char* destuff(char * destuffme){
	char * stuffed = NULL;
	char text[150];
	char DLE = 'm';//change for tesing but should be dle = 16
	int h = 0;//for testing purposes
	int currentLoc = 0;
	int destuffmeLoc = 0;
	int cpySizeInt;
	
	//takes in the text stuffs it then cuts it down to 72 characters
	//printf("start of while loop h)%d\n",h);h++;
	while(destuffme[destuffmeLoc] != '\0' || currentLoc == 80){//chaneg to a end delimiter
		//printf("appending single chars h)%d\n",h);h++;
		text[currentLoc] = destuffme[destuffmeLoc];
		
		if(destuffme[destuffmeLoc]==DLE){
			destuffmeLoc++;
		}
		destuffmeLoc++;
		currentLoc++;
	}
	/*if(currentLoc != 80){
		text[currentLoc+1] = '\0';
	}
	else{text[80] = '\0';}*/
	
	//printf("%d\n",currentLoc);
	
	if(currentLoc >= 80){
		cpySizeInt = 80;
		//printf("greater than 80\n");
	}
	else{
		cpySizeInt = strlen(text);
		//printf("not greater than 80\n");
	}
	//printf("%d\n",cpySizeInt);
	
	stuffed = text;
	//printf("              not stuffed: %s\n",stuffme);
	printf("destuffed: %s\n",text);
	
	return stuffed;
	
}

 
