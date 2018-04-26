#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chip8inters.h"


int main(int argc, char const *argv[]) {
	Chip8 Game;
	chip_init(&Game, "./c8games/PONG2");
	unsigned char a = 40;
	unsigned char b = 70;
	printf("%04X", a - b);
	return 0;
}
