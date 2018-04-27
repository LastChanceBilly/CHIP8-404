#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chip8inters.h"
#include "Chip8Opcodes.h"

//Initialize chip
void chip_init(Chip8* c, char game_name[100]){
	FILE * game_file = fopen(game_name, "rb");
	if(game_file == NULL){
		printf("No such file: %s", game_name);
	}
	c->memory = calloc(MemSize, 1);
	memset(c->memory, 0, MemSize);
	fread(c->memory +0x200, 1, MemSize-0x200, game_file);
  c->video = calloc(videoW * videoH, 1);
  c->SP = c->delay_timer = c->sound_timer = c->I =0;
	c->pc = 0x200;
  memset(c->video, 0, sizeof(c->video));
  memset(c->Stack, 0, sizeof(c->Stack));
  memset(c->V, 0, sizeof(c->V));
	memset(c->keys, 0, sizeof(c->keys));
}
