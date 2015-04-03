EXES = receiver sender

all: $(EXES)

receiver: receiver.c
	gcc -o receiver receiver.c -g -w

sender: sender.c
	gcc -o sender sender.c -g -w

clean:
	rm -rf $(EXES)