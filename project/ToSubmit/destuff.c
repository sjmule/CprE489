/**
 * A function which destuffs the message sent on the network.
 * Author: Brian Moran
 */

#include "header.h"

struct data{
	char dest;
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
	while(destuffme[destuffmeLoc] != '\0' || currentLoc == 80){//chaneg to a end delimiter
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

	stuffed = trim(stuffed);

	return stuffed;
	
}

struct data deserialize(char * buffer){
	char * cpyBuff = buffer;
	char DL;
	char SY;
	char ST;
	char ET;
	int destAddrs = 0;
	int sourceAddrs = 0;
	char * texts = "";
	char * d = NULL;
	char * s = NULL;
	
	struct data stuff;
	
	SY = strtok(cpyBuff,"&");
	SY = strtok(NULL,"&");
	DL = strtok(NULL,"&");
	ST = strtok(NULL,"&");
	d = strtok(NULL,"&");
	s = strtok(NULL,"&");
	texts = strtok(NULL,"&");
	DL = strtok(NULL,"&");
	ET = strtok(NULL,"&");

	sourceAddrs = s[0];

	stuff.dest = d[0];
	stuff.source = sourceAddrs;
	stuff.text = destuff(texts);
	
	return stuff;
}
