#include "header.h"

struct data{
	int dest;
	int source;
	char * text;
};

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
	text[currentLoc] ='\0';
	if(currentLoc != 80){
		text[currentLoc+1] = '\0';
	}
	else{text[80] = '\0';}

	stuffed = text;

	//printf("              not stuffed: %s\n",stuffme);
	//printf("destuffed: %s\n",text);
	stuffed = trim(stuffed);
	printf("destuffed:%s\n",stuffed);
	
	return stuffed;
	
}

struct data deserialize(char * buffer){
	char * cpyBuff = buffer;
	//printf("cpy:%s\n",cpyBuff);
	char * DLE;
	char * SYN;
	char * STX;
	char * ETX;
	int destAddr;
	int sourceAddr;
	char * text;
	char * d;
	char * s;
	
	struct data stuff;
	
	SYN = strtok(cpyBuff,"&");
	SYN = strtok(NULL,"&");
	DLE = strtok(NULL,"&");
	STX = strtok(NULL,"&");
	d = strtok(NULL,"&");
	s = strtok(NULL,"&");
	text = strtok(NULL,"&");
	DLE = strtok(NULL,"&");
	ETX = strtok(NULL,"&");
	printf("deserialized text:%s\n",text);
	printf("convert s and d");
	sourceAddr = atoi(s);
	destAddr = atoi(d);
	printf("set to struct");
	stuff.dest = destAddr;
	stuff.source = sourceAddr;
	stuff.text = destuff(text);
	
	return stuff;
}
