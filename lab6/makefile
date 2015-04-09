EXES = receiver sender
OBJS_RECEIVER = receiver.o AddCongestion.o
OBJS_SENDER = sender.o
CFLAGS = -w

DEPS = AddCongestion.h

all: $(EXES)

receiver: $(OBJS_RECEIVER)
	gcc -o $@ $^ $(CFLAGS)

sender: sender.c
	gcc -o $@ $^ $(CFLAGS) -lrt

%.o: %.c $(DEPS)
	gcc -o $@ -c $<

clean:
	rm -rf $(EXES)
	rm -rf *.o