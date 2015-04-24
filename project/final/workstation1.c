#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

struct data{
	int dest;
	int source;
	char * text;
};

char* stuff(char*);
char* destuff(char*);
struct data deserialize(char *);
char * trim(char*);

void main(){
	char buffer[100];
	char buffer2[100];
	char * textBuffer = malloc(sizeof(char)*80);
	char * textBuffer2 = malloc(sizeof(char)*80);
	textBuffer2 = NULL;
	//textBuffer = NULL;
	
	memset(buffer,0,100);
	memset(buffer2,0,100);
   
    char DLE = 'm';//16;
    char SYN = 's';//22;
    char STX = 'b';//2;
    char ETX = 'e';//3;
    int destAddr = 1;
    int sourceAddr = 2;
    char *text = NULL;
    char i; 
    char j;  
    size_t size =0;
    int er;
    
    struct data results;
   
        printf("When ready to enter a message please type in the destination node address (a,b,or c)\n");

        i = fgetc(stdin);
        j = fgetc(stdin);

        printf("When ready enter message of length 80 characters to send to node %c:",i);

        er = getline(&text, &size, stdin);
        //printf("er=%d\n",er);
        text=trim(text);
        //printf("%s\n",text);

	//sprintf(buffer,"%c&%c&%c&%c&%d&%d&%s&%c&%c", SYN,SYN,DLE,STX,destAddr,sourceAddr, text,DLE, ETX);
	//printf("%s\n",buffer);

	textBuffer = stuff(text);
	printf("textbuffer:%s\n",textBuffer);
	sprintf(buffer2,"%c&%c&%c&%c&%d&%d&%s&%c&%c&", SYN,SYN,DLE,STX,destAddr,sourceAddr, textBuffer,DLE, ETX);

	printf("stuffed buffer2:%s\n",buffer2);

	textBuffer2 = destuff(textBuffer);
	//printf("textbuffer2:%s\n",textBuffer2);
	results = deserialize(buffer2);
	printf("deserialized buffer: dest:%d source: %d\ntext:%s\n",results.dest,results.source,results.text);
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
	
	if(currentLoc >= 80){
		cpySizeInt = 80;
		//printf("greater than 80\n");
	}
	else{
		cpySizeInt = strlen(text);
		//printf("not greater than 80\n");
	}
	//printf("cpysizeint: %d\n",cpySizeInt);//cpySizeInt
	
	stuffed = text;
	strncat(stuffedDone,stuffed,currentLoc);
	
	//printf("              not stuffed: %s\n",stuffme);
	//printf("                  stuffed: %s\n",text);
	//printf("stuffed and 80 characters at most: %s\n",stuffedDone);
	
	return stuffedDone;
	
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

 
