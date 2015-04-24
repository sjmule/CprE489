EXES = main
OBJS = main.o Server.o Client.o stuff.o destuff.o
DEPS = header.h
CFLAGS = -w -g

main: $(OBJS)
	gcc -o main $^

%.o: %.c $(DEPS)
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(EXES)
	rm -rf *.o