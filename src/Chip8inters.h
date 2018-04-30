#ifndef Chip8inters_H
#define Chip8C8inters_H

#define MemSize 4096
#define StackSize 16
#define videoW 64
#define videoH 32
#define RegisterNum 16
#define timerDelay 10

typedef struct Chip8{
	//Chip's memory
	unsigned char *memory;
	//Chip's Stack
	unsigned short Stack[StackSize];
	//Chip's Stack pointer
	unsigned char SP;
	//Chip's program counter
	unsigned short pc;
	//Registers
	unsigned char V[RegisterNum];
	//Chip's Index register
	unsigned short I;
	//Chip's video memory
	unsigned char *video;
	//Chip's timers
	unsigned char delay_timer;
	unsigned char sound_timer;
	//Game keys
	unsigned char keys[16];
	//Instruction been executed (debug)
}Chip8;
void DebugDraw(Chip8 * d);
void chip_init(Chip8* c, char game_name[100]);
#endif
