CC=gcc
CFLAGS=-I.
DEPS = chip8inters.h
OBJ = main.o chip8inters.o
ARGS = ./c8games/15PUZZLE

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

CHIP8266: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
run:
	CHIP8266 $(ARGS)
