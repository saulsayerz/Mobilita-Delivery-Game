CC = gcc
CFLAGS = -c -Wall
ADT_DIR= DaftarADT
ADT_PRIMITIF_DIR= ADTPrimitif
LINKER= -lm
DEPEND_FILE= $(filter-out ../$(ADT_DIR)/mapdriver.c, $(wildcard ../$(ADT_DIR)/*.c))
QUEUE_FILE= $(wildcard ../$(ADT_DIR)/$(ADT_PRIMITIF_DIR)/Queue.c)
POINT_FILE= $(wildcard ../$(ADT_DIR)/$(ADT_PRIMITIF_DIR)/Point.c)
OBJ_FILE= *.o

todo.o:  main.c $(DEPEND_FILE)
	$(CC) $(CFLAGS) main.c $(DEPEND_FILE) $(QUEUE_FILE) $(POINT_FILE)

todo:
	$(CC) $(OBJ_FILE) -o main $(LINKER)

unused:
	-rm *driver.o

test: main
	./main

.PHONY: clean all

clean:
	-rm *.o