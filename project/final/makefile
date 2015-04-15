EXES = main
OBJS = main.o Server.o Client.o
DEPS = header.h
LIBRARIES = -lpthread

main: $(OBJS)
	gcc -o main $^ $(LIBRARIES)

%.o: %.c $(DEPS)
	gcc -o $@ -c $<

clean:
	rm -rf $(EXES)
	rm -rf *.o