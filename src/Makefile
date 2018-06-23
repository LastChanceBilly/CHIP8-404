CC=gcc
CFLAGS=-I -lSDL2.
DEPS = Chip8inters.h Chip8Opcodes.h
OBJ = Chip8inters.c Chip8Opcodes.c CHIP8266.c
ARGS = ../c8games/MISSILE

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

CHIP8266: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

run:
	CHIP8266.exe $(ARGS)
