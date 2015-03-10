EXES = ftpClient ftpServer

all: $(EXES)

ftpClient: ftpClient.c
	gcc -o ftpClient.o ftpClient.c -g -w

ftpServer: ftpServer.c
	gcc -o ftpServer.o ftpServer.c -g -w

clean:
	rm -rf *.o
	rm -rf $(EXES)