all: workstation1

########################################

workstation: workstation1.o 
	gcc -o workstation1 workstation1.c 
	
########################################

workstation.o: workstation1.c 
	gcc -c workstation1.c

########################################

clean : 
	touch workstation1.o;
	rm workstation1.o
