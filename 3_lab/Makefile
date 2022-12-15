main: main.o task1.o task2.o task3.o
	cc main.o task1.o task2.o task3.o -o main
	make clean

main.o: ./src/main.c
	cc -c ./src/main.c

task1.o: ./src/task1.c ./src/task1.h
	cc -c ./src/task1.c

task2.o: ./src/task2.c ./src/task2.h
	cc -c ./src/task2.c

task3.o: ./src/task3.c ./src/task3.h
	cc -c ./src/task3.c

clean:
	rm *.o