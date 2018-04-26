#ifndef Chip8inters_H
#define Chip8C8inters_H

#define MemSize 4096
#define StackSize 16
#define ScreenSize 32 * 64

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
	unsigned char *video;
	//Chip's timers
	unsigned char delay_timer;
	unsigned char sound_timer;
}Chip8;
extern int dAssembler(Chip8 *c, int pc);
extern void chip_init(Chip8* c, char game_name[100]);
void Jmp(Chip8 * c, unsigned short address);
void SubR(Chip8 * c, unsigned short address);
#endif
