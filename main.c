#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chip8inters.h"


int main(int argc, char *argv[]) {
	FILE *rom_file = fopen(argv[1], "rb");
	if(rom_file == NULL){
		printf("Can't open file %s", argv[1]);
	}
	fseek(rom_file, 0L, SEEK_END);
	int rom_size = ftell(rom_file);
	fseek(rom_file, 0L, SEEK_SET);
	unsigned char *buffer = malloc(rom_size);
	fread(buffer, rom_size, 1, rom_file);
	int pc = 0;
	while(pc < rom_size){
		//printf(" %04x \t %02x %02x\n", pc, buffer[pc], buffer[pc + 1]);
		//pc += 2;
		pc += dAssembler(buffer, pc);
	}
	free(buffer);
	return 0;
}
