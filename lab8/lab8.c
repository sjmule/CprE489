#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include "introduceerror.h"

#define POLY 0x8408
#define N strlen(g)

char* trimAndAddNulls(char*);
void crcCheck(char*);
unsigned short crc16(char*, unsigned short);

unsigned int g = 0x1021;

void main(int argc, char** argv){
	unsigned char buffer[1024];
	unsigned char bufferCRC[1032];
	int er;
	size_t size =0;
	int currentLoc = 0;
	char *text = malloc(sizeof(char)*1024);
	int i = 0;
	int byte = 0;
	unsigned char data;
	
	if(argc==1){
		printf("ERROR!");
		exit(-1);
	}
	double p =atof(argv[1]);
	
	printf("p: %f\n", p);

	printf("When ready enter message of max size 1024 characters:\n");
	er = getline(&text, &size, stdin);
	
	text = trimAndAddNulls(text);
	
	printf("CRC: 0x%x\n", g);
	
	if(er>1024){er = 1024;}
	
	//takes in the text stuffs it then cuts it down
	for(i;i<er;i++){//chaneg to a end delimiter
		//printf("appending single chars h)%d\n",h);h++;
		buffer[i] = text[i];
	}
	if(er==1024){
		buffer[1022]='\0';
		buffer[1023]='\0';
	}
	else{
		i++;
		buffer[i]='\0';
	}
	printf("Buffer:%s\n",buffer);
	
	memcpy(bufferCRC,buffer,strlen(buffer));
	bufferCRC[strlen(buffer)] = 0x10;
	bufferCRC[strlen(buffer)+1] = 0x21;
	
	printf("Codeword:   %s\n", bufferCRC);
	//char * pointer = malloc(sizeof(char)*1024);
	//pointer = buffer;
	//printf("pointer:%s\n",pointer);
	
	//crcCheck(pointer);
	
   	//printf("new R:%x\n",pointer);
   	
   	IntroduceError(bufferCRC,p);

	printf("Corrupted:   %s\n", bufferCRC);

   	char* pointer2 = malloc(1027 * sizeof(char));
   	memcpy(pointer2, bufferCRC, strlen(bufferCRC));
   	unsigned short remander = crc16(pointer2, strlen(pointer2));

   	printf("Corrupted:   %s\n", bufferCRC);

   	printf("CRC check R: %s\n", pointer2);

   	printf("Remainder: %d\n", remander);

   	if(remander != 0)
   	{
   		printf("Errors detected\n");
   	}
   	else
   	{
   		printf("No errors\n");
   	}
   	
}

char* trimAndAddNulls(char *text){
  int i = 0;
  while(1){
  	if(text[i] == '\n'){
  		text[i]='\0';

  		return text;
  	}
  	i++;
  }
}

unsigned short crc16(char *data_p, unsigned short length)
{
      unsigned char i;
      unsigned int data;
      unsigned int crc = 0x1021;

      if (length == 0)
            return (~crc);

      do
      {
            for (i=0, data=(unsigned int)0xff & *data_p++;
                 i < 8; 
                 i++, data >>= 1)
            {
                  if ((crc & 0x0001) ^ (data & 0x0001))
                        crc = (crc >> 1) ^ POLY;
                  else  crc >>= 1;
            }
      } while (--length);

      crc = ~crc;
      data = crc;
      crc = (crc << 8) | (data >> 8 & 0xff);

      return (crc);
}

