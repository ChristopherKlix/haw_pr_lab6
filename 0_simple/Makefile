main: main.o cypher.o vector.o
	cc main.o cypher.o vector.o -o main
	make clean

main.o: ./src/main.c
	cc -c ./src/main.c

cypher.o: ./src/cypher.c ./src/cypher.h
	cc -c ./src/cypher.c

vector.o: ./src/vector.c ./src/vector.h
	cc -c ./src/vector.c

clean:
	rm *.o