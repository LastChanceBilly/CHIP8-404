#ifndef Chip8inters_H
#define Chip8C8inters_H

#define MemSize 4096
#define StackSize 0x0f
#define ScreenSize 32 * 64
#define RegisterNum 16

typedef struct Chip8{
	//Chip's memory
	unsigned char *memory;
	//Chip's Stack
	unsigned short Stack[StackSize];
	//Chip's Stack pointer
	unsigned short SP;
	//Chip's program counter
	unsigned char pc;
	//Registers
	unsigned char V[RegisterNum];
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
void JP(Chip8 * c, unsigned short address);
void CALL(Chip8 * c, unsigned short address);
void SE(Chip8 * c, unsigned char reg,unsigned char val);
void SNE(Chip8 * c, unsigned char reg,unsigned char val);
void SRE(Chip8 * c, unsigned char regX,unsigned char regY);
void LD(Chip8 * c, unsigned char reg,unsigned char val);
void ADD(Chip8 * c, unsigned char reg,unsigned char val);

#endif
