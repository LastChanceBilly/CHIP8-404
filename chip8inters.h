#ifdef CHIP8INTERS_H
#define CHIP8INTERS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MemSize 4096
#define StackSize 16
#define ScreenSize 32 * 64

typedef struct chip8{
	//Chip's memory
	unsigned char *memory;
	//Chip's Stack
	unsigned short v[StackSize];
	//Chip's Stack pointer
	unsigned short SP;
	//Chip's program counter
	unsigned char pc;
	//Chip's Index register
	unsigned char I;
	//Chip's video memory
	unsigned char video[ScreenSize];
	//Chip's timers
	unsigned char delay_timer;
	unsigned char sound_timer;
}Chip8;
int dAssembler(unsigned char *buffer, int pc);
#endif
