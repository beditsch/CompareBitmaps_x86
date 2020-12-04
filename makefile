CC = gcc
CFLAGS = -Wall -m64

all: main.o whereIsWally.o IO.o
	$(CC) $(CFLAGS) -o whereIsWally main.o whereIsWally.o IO.o -lglut -lGLU -lGL

whereIsWally.o: whereIsWally.s
	nasm -f elf64 -o whereIsWally.o whereIsWally.s

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

IO.o: IO.c
	$(CC) $(CFLAGS) -c -o IO.o IO.c

clean:
	rm -f *.o

