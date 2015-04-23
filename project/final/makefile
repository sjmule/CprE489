fEXES = main
OBJS = main.o Server.o Client.o
DEPS = header.h
CFLAGS = -w
LIBRARIES = -lpthread

main: $(OBJS)
	gcc -o main $^ $(LIBRARIES)

%.o: %.c $(DEPS)
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(EXES)
	rm -rf *.o