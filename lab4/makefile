EXES = ftpClient ftpServer

all: $(EXES)

ftpClient: ftpClient.c
	gcc -o ftpClient ftpClient.c -g -w

ftpServer: ftpServer.c
	gcc -o ftpServer ftpServer.c -g -w

clean:
	rm -rf $(EXES)