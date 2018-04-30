#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Chip8inters.h"
#include "Chip8Opcodes.h"

void delay(int timer);
void chip8Monitor(Chip8 *c);
int main(int argc, const char *argv[]) {
	Chip8 Game;
	Chip8* c = &Game;
	chip_init(&Game, argv[1]);
	while(1){
		//chip8Monitor(c);
		for(int i = 0; i < timerDelay; i++){
			//chip8Monitor(&Game);
			OpcodeExec(c);
		}
		if(c->delay_timer > 0) c->delay_timer--;
		if(c->sound_timer > 0) c->sound_timer--;
	}
	return 0;
}
void chip8Monitor(Chip8 *c){
	printf("[SP] %04X \t [PC] %04X \t [I] %04X \t [Opcode] %02X%02X\n", c->SP, c-> pc, c->I, c->memory[c->pc],c->memory[c->pc + 1]);
	printf("[DT]: %02X [ST]: %02X\n", c->delay_timer, c->sound_timer);
	for(int i =0; i< 16; i++){
		printf("\t[%01X]: %04X\t", i, *(c->V +i));
		printf("[%01X]: %04X\n", i, *(c->Stack + i));
	}
	printf("\n");
	//getchar();
	system("cls");
}
void delay(int timer){
	clock_t start_time = clock();
	while(clock() < start_time + timer) ;
}
