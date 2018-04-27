#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Chip8inters.h"
#include "Chip8Opcodes.h"

void delay(int timer);
void chip8Monitor(Chip8 *c);
int main(int argc, char const *argv[]) {
	Chip8 Game;
	chip_init(&Game, "../c8games/MAZE");
	while(1){
		//chip8Monitor(&Game);
		OpcodeExec(&Game);
	}
	return 0;
}
void chip8Monitor(Chip8 *c){
	printf("[SP] %04X \t [PC] %04X \t [I] %04X \t [Opcode] %02X%02X\n", c->SP, c-> pc, c->I, c->memory[c->pc],c->memory[c->pc + 1]);
	for(int i =0; i< 16; i++){
		printf("\t[%01X]: %04X\t", i, *(c->V +i));
		printf("[%01X]: %04X\n", i, *(c->Stack + i));
	}
	printf("\n");
	getchar();
	system("cls");
}
void delay(int timer){
	clock_t start_time = clock();
	while(clock() < start_time + timer) ;
}
