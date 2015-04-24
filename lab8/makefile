EXES = main
OBJS = lab8.o introduceerror.o
DEPS = introduceerror.h
CFLAGS = -w

main: $(OBJS)
	gcc -o main $^

%.o: %.c $(DEPS)
	gcc -o $@ -c $<

clean:
	rm -rf $(EXES)
	rm -rf *.o