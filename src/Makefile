CC = gcc
CFLAGS = -c -Wall
LINKER= -lm
DEPEND_FILE= $(wildcard **/*.c)

OBJ_FILE= *.o

compileobj:  main.c $(DEPEND_FILE)
	$(CC) $(CFLAGS) main.c $(DEPEND_FILE)

rmunused:
	rm *driver.o

build:
	$(CC) $(OBJ_FILE) -o main $(LINKER)

.PHONY: clean all

clean:
	-rm *.o

test: main
	./main
