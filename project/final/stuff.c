#include "header.h"

char* stuff(char * stuffme){
	char * stuffed = NULL;
	char * stuffedDone = malloc(sizeof(char)*80);
	char text[150];
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
