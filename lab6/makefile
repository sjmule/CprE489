EXES = receiver sender
OBJS_RECEIVER = receiver.o AddCongestion.o
OBJS_SENDER = sender.o

DEPS = AddCongestion.h

all: $(EXES)

receiver: $(OBJS_RECEIVER)
	gcc -o $@ $^

sender: sender.c
	gcc -o 

%.o: %.c $(DEPS)
	gcc -o $@ $<

clean:
	rm -rf $(EXES)
	rm -rf *.o