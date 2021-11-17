CC = gcc
std99= -std=c99
CFLAGS = -c -Wall
LINKER= -lm
DEPEND_FILE= $(wildcard **/*.c)

OBJ_FILE= *.o

compileobj:  main.c $(DEPEND_FILE)
	$(CC) $(std99) $(CFLAGS) main.c $(DEPEND_FILE)

rmunused:
	rm *driver.o

build:
	$(CC) $(std99) $(OBJ_FILE) -o main $(LINKER)

.PHONY: clean all

clean:
	rm *.o

test: main
	./main
