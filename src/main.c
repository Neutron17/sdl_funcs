#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <math.h>

#define PI 3.14159

int main(int argc, const char *argv[]) {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "ERROR: Couldn't init sdl, '%s'\n", SDL_GetError());
		return -1;
	}
	int width = 1024, height = 720;
	SDL_Window *window = SDL_CreateWindow("Title", 0, 0, width, height, SDL_WINDOW_RESIZABLE);
	if(!window) {
		fprintf(stderr, "ERROR: Couldn't create window, '%s'\n", SDL_GetError());
		return -2;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer) {
		fprintf(stderr, "ERROR: Couldn't create renderer, '%s'\n", SDL_GetError());
		return -3;
	}

	SDL_Event e;
	bool quit = false;
	float amplitude = 50.0;
	while(!quit) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		SDL_WaitEvent(&e);
		switch (e.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_WINDOWEVENT:
				switch (e.window.event) {
					case SDL_WINDOWEVENT_RESIZED:
						SDL_GetWindowSize(window, &width, &height);
						break;
					default:
						break;
				}
				break;
			default: {}
		}
		int x = 0;
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		const float startX = -PI * 2.5;
		const float stretch = 0.01;
		for(float i = startX; i < PI * 2.0; i += stretch, x++) {
			//if(x % 3 == 0)
			//	continue;
			if(x >= width)
				break;
			float y = amplitude * -cosf(i);
			y += height / 2.0;
			SDL_RenderDrawPointF(renderer, x, y);
			// Vertical line where x is around 0
			if(i < stretch && i > -stretch) {
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
				SDL_RenderDrawLineF(renderer, x, height/2.0-amplitude, x, height/2.0+amplitude);
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			}
		}


		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		// X0 line
		SDL_RenderDrawLine(renderer, 0, height/2.0, width, height/2.0);
		// bottom line
		SDL_RenderDrawLine(renderer, 0, height/2.0+amplitude, width, height/2.0+amplitude);
		// top line
		SDL_RenderDrawLine(renderer, 0, height/2.0-amplitude, width, height/2.0-amplitude);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
