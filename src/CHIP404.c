#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "Chip8inters.h"
#include "Chip8Opcodes.h"

//#define DEBUG
#define PLAY
#define INIT_FLAGS SDL_INIT_VIDEO

//SDL_Renderer flags
#define RENDERER_FLAGS SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC

void delay(int timer);
void chip8Monitor(Chip8 *c);
int main(int argc, const char *argv[]) {
	//Chip8 initialization
	SDL_Init(INIT_FLAGS);
	Chip8 Game;
	Chip8* c = &Game;
	chip_init(&Game, argv[1]);
#ifdef PLAY
	//SDL stuff
	if(SDL_Init(INIT_FLAGS) != 0){
		printf("SDL initialization error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	SDL_Window* main_window = SDL_CreateWindow("Main Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, 0);
	if(main_window == NULL){
		printf("SDL window creation error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	SDL_Renderer* main_renderer = SDL_CreateRenderer(main_window, -1, RENDERER_FLAGS);
	if(main_renderer == NULL){
		printf("SDL window creation error: %s\n", SDL_GetError());
		SDL_DestroyWindow(main_window);
		SDL_Quit();
		return 1;
	}
	SDL_Texture* main_texture = SDL_CreateTexture(main_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WINDOW_W, WINDOW_H);
	uint32_t* pixel_buffer = (uint32_t *)calloc(WINDOW_H * WINDOW_W, sizeof(uint32_t)); 
	SDL_RenderClear(main_renderer);
#endif
	//Main loop
	uint8_t killflag = 1;
	while(killflag){
#ifdef DEBUG
		chip8Monitor(c);
#endif
		for(int i = 0; i < timerDelay; i++){
			OpcodeExec(c);
		}
		if(c->delay_timer > 0) c->delay_timer--;
		if(c->sound_timer > 0) c->sound_timer--;
#ifdef PLAY
		for(int index =0; index < WINDOW_H * WINDOW_W; index++){
			pixel_buffer[index] = 0;
		}
		PixelDraw(c, pixel_buffer);
		SDL_UpdateTexture(main_texture, NULL, pixel_buffer, WINDOW_W * sizeof(uint32_t));
		SDL_RenderCopy(main_renderer, main_texture, NULL, NULL);
		SDL_RenderPresent(main_renderer);
		//Loop kill event
		SDL_Event main_event;
		if(SDL_PollEvent(&main_event)){
			if(main_event.type == SDL_QUIT) killflag =0;
			if(main_event.type == SDL_KEYDOWN){
				memset(c->keys, 0, sizeof(c->keys));
				switch(main_event.key.keysym.sym){
					case (SDLK_1):
						c->keys[1] = 0xff;
						break;
					case (SDLK_2):
						c->keys[2] = 0xff;
						break;
					case (SDLK_3):
						c->keys[3] = 0xff;
						break;
					case (SDLK_4):
						c->keys[4] = 0xff;
						break;
					case (SDLK_5):
						c->keys[5] = 0xff;
						break;
					case (SDLK_6):
						c->keys[6] = 0xff;
						break;
					case (SDLK_7):
						c->keys[7] = 0xff;
						break;
					case (SDLK_8):
						c->keys[8] = 0xff;
						break;
					case (SDLK_9):
						c->keys[9] = 0xff;
						break;
					case (SDLK_a):
						c->keys[10] = 0xff;
						break;
					case (SDLK_b):
						c->keys[11] = 0xff;
						break;
					case (SDLK_c):
						c->keys[12] = 0xff;
						break;
					case (SDLK_d):
						c->keys[13] = 0xff;
						break;
					case (SDLK_e):
						c->keys[14] = 0xff;
						break;
					case (SDLK_f):
						c->keys[15] = 0xff;
						break;
					case (SDLK_0):
						c->keys[0] = 0xff;
						break;
					case (SDLK_q):
						killflag =0;
						break;
					default:
						continue;
				}
			}
		}
		SDL_Delay(6);
#endif 
	}
	free(c->video);
	free(c->memory);
#ifdef PLAY
	free(pixel_buffer);
	SDL_DestroyRenderer(main_renderer);
	SDL_DestroyWindow(main_window);
	SDL_Quit();
#endif
	return 0;
}
void chip8Monitor(Chip8 *c){
	printf("[SP] %04X \t [PC] %04X \t [I] %04X \t [Opcode] %02X%02X\n", c->SP, c-> pc, c->I, c->memory[c->pc],c->memory[c->pc + 1]);
	printf("[DT]: %02X [ST]: %02X\n", c->delay_timer, c->sound_timer);
	for(int i =0; i< 16; i++){
		printf("\t[%01X]: %04X\t", i, *(c->V +i));
		printf("[%01X]: %04X\n", i, *(c->Stack + i));
	}
	printf("\n");
#ifdef DEBUG
	char label =getchar();
	if(label == 'q') exit(1);
#endif
	system("clear");
}
void delay(int timer){
	clock_t start_time = clock();
	while(clock() < start_time + timer) ;
}
