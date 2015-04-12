EXES=main
OBJS = main3.o Server1.o Client1.o
DEPS = header.h

main: $(OBJS)
	gcc -o main3 $^

%.o: %.c $(DEPS)
	gcc -o $@ -c $<

clean:
	rm -rf $(EXES)
	rm -rf *.o