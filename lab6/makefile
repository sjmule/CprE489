OBJS = receiver.o sender.o AddCongestion.o

DEPS = AddCongestion.h

receiver: receiver.c
	gcc -o receiver receiver.c -g -w

sender: sender.c
	gcc -o sender sender.c -g -w

%.o: %.c $(DEPS)
	gcc -o $@ $<

clean:
	rm -rf $(EXES)