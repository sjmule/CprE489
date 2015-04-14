EXES = main
OBJS = main4.o Server1.o Client1.o
DEPS = header.h
LIBRARIES = -lpthread

main: $(OBJS)
	gcc -o main4 $^ $(LIBRARIES)

%.o: %.c $(DEPS)
	gcc -o $@ -c $<

clean:
	rm -rf $(EXES)
	rm -rf *.o