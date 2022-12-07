main: main.o file.o
	cc main.o file.o -o main
	make clean

main.o: ./src/main.c
	cc -c ./src/main.c

file.o: ./src/file.c ./src/file.h
	cc -c ./src/file.c

clean:
	rm *.o