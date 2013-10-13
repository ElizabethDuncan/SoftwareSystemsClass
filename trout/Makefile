util.o: util.c util.h
	gcc -Wall -c util.c 

trout.o: trout.c trout.h
	gcc -Wall -c trout.c

main.o: main.c
	gcc -Wall -c main.c 

trout: util.o trout.o main.o
	gcc -Wall main.o util.o trout.o -o trout 
