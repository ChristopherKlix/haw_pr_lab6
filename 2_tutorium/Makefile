main: main.o file.o util.o cipher.o
	cc main.o file.o util.o cipher.o -o main
	make clean

main.o: ./src/main.c
	cc -c ./src/main.c

file.o: ./src/file.c ./src/file.h
	cc -c ./src/file.c

util.o: ./src/util.c ./src/util.h
	cc -c ./src/util.c

cipher.o: ./src/cipher.c ./src/cipher.h
	cc -c ./src/cipher.c

clean:
	rm *.o