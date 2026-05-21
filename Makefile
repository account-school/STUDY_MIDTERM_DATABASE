all: main

main: main.o database.o
	gcc main.o database.o -o main


main.o: main.c database.h
	gcc -c main.c database.h 


database.o: database.c database.h
	gcc -c database.c database.h


clean:
	rm *.o  main