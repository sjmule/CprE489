/**
 * A function which stuffs a message to be sent on the network
 * Author: Brian Moran
 */

#include "header.h"

char* stuff(char * stuffme){
	char * stuffed = NULL;
	char * stuffedDone = malloc(sizeof(char)*127);
	char * text = malloc(127 * sizeof(char));
	char DLE = 'm';//change for tesing but should be dle = 16 
	int h = 0;//for testing purposes
	int currentLoc = 0;
	int stuffmeLoc = 0;
	int cpySizeInt;

	stuffedDone = "";
	
	//takes in the text stuffs it then cuts it down to 72 characters
	while(stuffme[stuffmeLoc] != '\0' || currentLoc == 80){//change to a end delimiter
		text[currentLoc] = stuffme[stuffmeLoc];
		
		if(stuffme[stuffmeLoc]==DLE){
			currentLoc++;
			text[currentLoc] = DLE;
		}
		stuffmeLoc++;
		currentLoc++;
	}

	text[currentLoc] = '\0';
	
	if(currentLoc >= 80){
		cpySizeInt = 80;
	}
	else{
		cpySizeInt = strlen(text);
	}
	
	stuffed = text;

	return stuffed;
}

char * trim(char *text){
  int i = 0;
  while(1){
  	if(text[i] == '\n'){
  		text[i]='\0';
  		return text;
  	}
  	i++;
  }
}
