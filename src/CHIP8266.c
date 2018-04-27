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
	chip_init(&Game, "../c8games/PONG2");
	CALL(&Game, 0x0400);
	CALL(&Game, 0x0400);
	CALL(&Game, 0x0400);
	LD(&Game, 0x01, 0x01);
	ADD(&Game, 0x01, 0x23);
	while(1){
		chip8Monitor(&Game);
	}
	return 0;
}
void chip8Monitor(Chip8 *c){
	for(int i =0; i< 16; i++){
		printf("[%01X]: %04X\t", i, c->V[i]);
		printf("[%d]: %04X\n", i, c->Stack[i]);
	}
	delay(500);
	system("cls");
}
void delay(int timer){
	clock_t start_time = clock();
	while(clock() < start_time + timer) ;
}
