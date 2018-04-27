#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chip8inters.h"
#include "Chip8Opcodes.h"

void OpcodeExec(Chip8 *c){
	unsigned char *code = &c->memory[c->pc];
	unsigned char uphalf = (code[0] >> 4);
	//printf("%04X %02X %02X\t", c->pc, code[0], code[1]);
	unsigned short addr;
	unsigned char regX, regY;
	unsigned char num;
	switch(uphalf){
		/*case 0x00:
			//Clear screen
			if(code[1] == 0xe0){
			}
			else if(code[1] == 0xee){
			}
			else{
			}
			break;*/
		case 0x01:
			addr = ((code[0] & 0x0f) << 8) | code[1];
			JP(c, addr);
			break;
		case 0x02:
			addr = ((code[0] & 0x0f) << 8) | code[1];
			CALL(c, addr);
			break;
		case 0x03:
			regX = (code[0] & 0x0f);
			num = code[1];
			SE(c, regX, num);
			break;
		case 0x04:
			regX = (code[0] & 0x0f);
			num = code[1];
			SNE(c, regX, num);
			break;
		case 0x05:
			regX = (code[0] & 0x0f);
			regY = code[1] & 0xf0;
			SRE(c, regX, regY);
			break;
		case 0x06:
			regX = (code[0] & 0x0f);
			num = code[1] & 0xf0;
			LD(c, regX, num);
			break;
		case 0x07:
			regX = (code[0] & 0x0f);
			num = code[1];
			ADD(c, regX, num);
			break;
		case 0x08:
			regX = code[0] & 0x0f;
			regY = (code[1] & 0xf0) >> 4;
			switch(code[1] & 0x0f){
				case(0x00):
					LRD(c, regX, regY);
					break;
				case(0x01):
					OR(c, regX, regY);
					break;
				case(0x02):
					AND(c, regX, regY);
					break;
				case(0x03):
					XOR(c, regX, regY);
					break;
				case(0x04):
					ADDF(c, regX, regY);
					break;
				case(0x05):
					SUB(c, regX, regY);
					break;
				case(0x06):
					SHR(c, regX);
					break;
				case(0x07):
					SUBN(c, regX, regY);
					break;
				case(0x0e):
					SHL(c, regX);
					break;
				default:
					;
					//printf("Error, opcode %02X%02X\n", code[0] , code[1]);
			}
			break;
		case 0x09:
			regX = code[0] & 0x0f;
			regY = (code[1] & 0xf0) >> 4;
			SNER(c, regX, regY);
			break;
		case 0x0a:
			addr = ((code[0] & 0x0f) << 8) | code[1];
			LD_I(c, addr);
			break;
		case 0x0b:
			addr = ((code[0] & 0x0f) << 8) | code[1];
			JPR(c, addr);
			break;
		case 0x0c:
			regX = (code[0] & 0x0f);
			num = code[1];
			RND(c, regX, num);
			break;
		case 0x0d:
			regX = code[0] & 0x0f;
			regY = (code[1] & 0xf0) >> 4;
			num = code[1] & 0x0f;
			DRW(c, regX, regY,num);
			break;
		case 0x0e:
			regX = code[0] & 0x0f;
			switch(code[1]){
				case 0x9e:
					SKP(c, regX);
					break;
				case 0xa1:
					SKNP(c, regX);
					break;
				default:
					;
					//printf("Error, opcode %02X%02X\n", code[0] , code[1]);
			}
			break;
		case 0x0f:
			regX = code[0] & 0x0f;
			switch(code[1]){
				case 0x07:
					LDDT(c, regX);
					break;
				case 0x0a:
					SKHP(c, regX);
					break;
				case 0x15:
					DTLD(c, regX);
					break;
				case 0x18:
					LDST(c, regX);
					break;
				case 0x1e:
					IADD(c, regX);
					break;
				case 0x29:
					ILD(c, regX);
					break;
				case 0x33:
					BCD(c, regX);
					break;
				case 0x55:
					VLD(c, regX);
					break;
				case 0x65:
					LDV(c, regX);
					break;
				default:
					;
					//printf("Error, opcode %02X%02X\n", code[0] , code[1]);
			}
			break;
		default:
			;
			//printf("Error, opcode %02X%02X\n", code[0] , code[1]);
	}
	c->pc+=2;
}
//1NNN
void JP(Chip8 * c, unsigned short address){
	//printf("%04X\n", address);
  c->pc = address;
}
//2NNN
void CALL(Chip8 * c, unsigned short address){
  c->Stack[c->SP] = c->pc;
  c->pc = address;
  c->SP++;
}
//3XKK
void SE(Chip8 * c, unsigned char reg, unsigned char val){
  if(c->V[reg] == val){
    c->pc += 2;
  }
}
//4XKK
void SNE(Chip8 * c, unsigned char reg, unsigned char val){
  if(c->V[reg] != val){
    c->pc += 2;
  }
}
//5XY0
void SRE(Chip8 * c, unsigned char regX, unsigned char regY){
  if(c->V[regX] == c->V[regY]){
    c->pc += 2;
  }
}
//6XKK
void LD(Chip8 * c, unsigned char reg, unsigned char val){
  c->V[reg] = val;
}
//7XKK
void ADD(Chip8 * c, unsigned char reg, unsigned char val){
  c->V[reg] += val;
}
//8XY0
void LRD(Chip8 * c, unsigned char regX, unsigned char regY){
  c->V[regX] = c->V[regY];
}
//8XY1
void OR(Chip8 * c, unsigned char regX, unsigned char regY){
  c->V[regX] = c->V[regX] | c->V[regY];
}
//8XY2
void AND(Chip8 * c, unsigned char regX, unsigned char regY){
  c->V[regX] = c->V[regX] & c->V[regY];
}
//8XY2
void XOR(Chip8 * c, unsigned char regX, unsigned char regY){
  c->V[regX] = c->V[regX] ^ c->V[regY];
}
//8XY4
void ADDF(Chip8 * c, unsigned char regX, unsigned char regY){
  unsigned short result = c->V[regX] + c->V[regY];
  c->V[0x0f] = (result & 0x0100) >> 8;
  c->V[regX] = result & 0x00ff;
}
//8XY5
void SUB(Chip8 * c, unsigned char regX, unsigned char regY){
  if(c->V[regX] > c->V[regY]){
    c->V[0x0f] = 0x01;
  }
  else{
    c->V[0x0f] = 0x00;
  }
  c->V[regX] -= c->V[regY];
}
//8XY6
void SHR(Chip8 * c, unsigned char reg){
  c->V[0x0f] = c->V[reg] & 1;
  c->V[reg] = c->V[reg] >> 1;
}
//8XY7
void SUBN(Chip8 * c, unsigned char regX, unsigned char regY){
  if(c->V[regX] < c->V[regY]){
    c->V[0x0f] = 0x01;
  }
  else{
    c->V[0x0f] = 0x00;
  }
  c->V[regX] = c->V[regY] - c->V[regX];
}
//8XYE
void SHL(Chip8 * c, unsigned char reg){
  c->V[0x0f] = c->V[reg] >>7;
  c->V[reg] = c->V[reg] << 1;
}
//9XY0
void SNER(Chip8 * c, unsigned char regX, unsigned char regY){
	if(c->V[regX] != c->V[regY]){
    c->pc += 2;
  }
}
//ANNN
void LD_I(Chip8 * c, unsigned short val){
	c->I = val;
}
//BNNN
void JPR(Chip8 * c, unsigned short address){
  c->pc = c->V[0] + address;
}
//CXKK
void RND(Chip8 * c, unsigned char reg, unsigned char val){
	unsigned char random = rand() % 256;
	c->V[reg] = random & val;
//	printf("%02X\n", random);
}
//DXYN
void DRW(Chip8 * c, unsigned char regX, unsigned char regY, unsigned char n){
	for(int rows = 0; rows < n; rows++){
		unsigned char sprite = c->memory[c->I + rows];
		for(int pixel = 0; pixel < 8; pixel++){
			if((sprite & (0x80 >> pixel)) !=0){
				if(c->video[regX + (regY * 64)] == 1){
					 c->V[0x0f] = 1;
					 c->video[regX + (regY * 64)] ^= 1;
				 }
			}
		}
	}
}
//EX9E
void SKP(Chip8 * c, unsigned char reg){
	if(c->keys[c->V[reg]] != 0){
		c->pc += 2;
	}
}
//EXA1
void SKNP(Chip8 * c, unsigned char reg){
	if(c->keys[c->V[reg]] == 0){
		c->pc += 2;
	}
}
//FX07
void LDDT(Chip8 * c, unsigned char reg){
	c->V[reg] = c->delay_timer;
}
//FX0A
void SKHP(Chip8 * c, unsigned char reg){
	for(unsigned char i = 0; i < 16 ; i++){
		if(c->keys[i] != 0){
			c->V[reg] = i;
		}
		else{
			c->pc -= 2;
		}
	}
}
//FX15
void DTLD(Chip8 * c, unsigned char reg){
	c->delay_timer = c->V[reg];
}
//FX18
void LDST(Chip8 * c, unsigned char reg){
	c->sound_timer = c->V[reg];
}
//FX1E
void IADD(Chip8 * c, unsigned char reg){
	c->I = c->I + c->V[reg];
}
//FX29
void ILD(Chip8 * c, unsigned char reg){
	c->I = c->V[reg] * 5;
}
//FX33
void BCD(Chip8 * c, unsigned char reg){
	c->memory[c->I] = c->V[reg] / 100;
	c->memory[c->I] = (c->V[reg] / 10) % 10;
	c->memory[c->I] = c->V[reg] % 10;
}
//FX55
void VLD(Chip8 * c, unsigned char reg){
	for(unsigned char i = 0; i < reg; i++){
		c->memory[c->I+i] = c->V[reg];
	}
}
//FX65
void LDV(Chip8 * c, unsigned char reg){
	for(unsigned char i = 0; i < reg; i++){
		c->V[reg] = c->memory[c->I+i];
	}
}
