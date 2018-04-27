#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chip8inters.h"
#include "Chip8Opcodes.h"

int main(int argc, char const *argv[]) {
	Chip8 Game;
	chip_init(&Game, "../c8games/PONG2");
	return 0;
}
