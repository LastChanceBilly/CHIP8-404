#ifndef C8inters_H
#define C8C8inters_H
typedef struct Chip8{
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
#endif
