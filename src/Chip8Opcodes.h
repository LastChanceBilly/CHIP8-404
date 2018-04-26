#ifndef Chip8Opcodes_H
#define Chip8Opcodes_H

int OpcodeExec(Chip8 *c, int pc);
void chip_init(Chip8* c, char game_name[100]);
void JP(Chip8 * c, unsigned short address);
void CALL(Chip8 * c, unsigned short address);
void SE(Chip8 * c, unsigned char reg,unsigned char val);
void SNE(Chip8 * c, unsigned char reg,unsigned char val);
void SRE(Chip8 * c, unsigned char regX,unsigned char regY);
void LD(Chip8 * c, unsigned char reg,unsigned char val);
void ADD(Chip8 * c, unsigned char reg,unsigned char val);
void LRD(Chip8 * c, unsigned char regX, unsigned char regY);
void OR(Chip8 * c, unsigned char regX, unsigned char regY);
void AND(Chip8 * c, unsigned char regX, unsigned char regY);
void XOR(Chip8 * c, unsigned char regX, unsigned char regY);
void ADDF(Chip8 * c, unsigned char regX, unsigned char regY);
void SUB(Chip8 * c, unsigned char regX, unsigned char regY);
void SHR(Chip8 * c, unsigned char reg);
void SUBN(Chip8 * c, unsigned char regX, unsigned char regY);
void SHL(Chip8 * c, unsigned char reg);
#endif
