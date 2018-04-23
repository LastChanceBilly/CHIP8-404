#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chip8inters.h"

int dAssembler(unsigned char *buffer, int pc){
	int count= 2;
	unsigned char *code = &buffer[pc];
	unsigned char uphalf = (code[0] >> 4);
	printf("%04X %02X %02X\t", pc, code[0], code[1]);
	unsigned short addr;
	unsigned char regX, regY;
	unsigned char num;
	switch(uphalf){
		case 0x00:
			//Clear screen
			if(code[1] == 0xe0){
				printf("CLS\n");
			}
			else if(code[1] == 0xee){
				printf("RETURN\n");
			}
			else{
				printf("\n");
			}
			break;
		case 0x01:
			//GOTO
			addr = ((code[0] & 0x0f) << 8) | code[1];
			printf("GOTO $%04X\n", addr);
			break;
		case 0x02:
			//CALL
			addr = ((code[0] & 0x0f) << 8) | code[1];
			printf("CALL $%04X\n", addr);
			break;
		case 0x03:
			//COND, EQL
			regX = (code[0] & 0x0f);
			num = code[1];
			printf("IF reg%01X EQL $#%02X, JMP $%04X\n", regX, num, pc+4);
			break;
		case 0x04:
			//COND DIFF
			regX = (code[0] & 0x0f);
			num = code[1];
			printf("IF reg%01X NO-EQL $#%02X, JMP $%04X\n", regX, num, pc+4);
			break;
		case 0x05:
			//COND (W/ REGISTERS)
			regX = (code[0] & 0x0f);
			regY = code[1] & 0xf0;
			printf("IF reg%01X EQL reg%02X, JMP $%04X\n", regX, regY, pc+4);
			break;
		case 0x06:
			//ADD VALUE TO REG
			regX = (code[0] & 0x0f);
			num = code[1] & 0xf0;
			printf("reg%01X EQL $#%02X\n", regX, num);
			break;
		case 0x07:
			//ADD NUM TO REG VALUE
			regX = (code[0] & 0x0f);
			num = code[1] & 0xf0;
			printf("reg%01X ADD $#%02X\n", regX, num);
			break;
		case 0x08:
			regX = code[0] & 0x0f;
			regY = (code[1] & 0xf0) >> 4;
			switch(code[1] & 0x0f){
				case(0x00):
					//X = Y
					printf("reg%01X EQL reg%01X\n", regX, regY);
					break;
				case(0x01):
					//X = X | Y
					printf("reg%01X EQL reg%01X OR reg%01X\n",regX, regX, regY);
					break;
				case(0x02):
					//X = X & Y
					printf("reg%01X EQL reg%01X AND reg%01X\n", regX, regX, regY);
					break;
				case(0x03):
					//X = X ^ Y
					printf("reg%01X EQL reg%01X XOR reg%01X\n", regX, regX, regY);
					break;
				case(0x04):
					//X += Y
					printf("reg%01X ADD reg%01X\n", regX, regY);
					break;
				case(0x05):
					//X -= Y
					printf("reg%01X RMV reg%01X\n", regX, regY);
					break;
				case(0x06):
					//X = Y = Y >> 1
					//reg F is set to the least significant bit (i.e 01010101)
					//                                           VF =      /|\
					printf("reg%01X EQL SHR reg%01X (regF EQL %01X & 0x01)\n", regX, regY, regY);
					break;
				case(0x07):
					//X = Y - X
					printf("reg%01X SUBB reg%01X\n", regX, regY);
					break;
				case(0x0e):
					//X = Y = Y << 1
					//reg F is set to the most significant bit (i.e 01010101)
					//                                       VF = /|\
					printf("reg%01X EQL SHR reg%01X (regF EQL %01X & 0x01)\n", regX, regY, regY);
					break;
				default:
					printf("\n");
			}
			break;
		case 0x09:
			regX = code[0] & 0x0f;
			regY = (code[1] & 0xf0) >> 4;
			printf("IF reg%01X EQL reg%01X, JUMP $%04X\n", regX, regY, pc+4);
		default:
			printf("\n");
	}
	return count;
}

void chip8initialize(chip8 *chip){
	
}
