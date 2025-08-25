#include <os.h>
#include "image_data.hpp"
#include "level.hpp"
#include "level_data.hpp"
#include <SDL/SDL_config.h>
#include <SDL/SDL.h>
#include <math.h>

SDL_Surface* screen;

#define FRAMERATE 30	// Frames per second
#define TICKRATE 1000/FRAMERATE  // Number of ticks that need to pass to go to the next frame

// Initialize SDL and screen
void init() {
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	screen = SDL_SetVideoMode(320, 240, has_colors ? 16 : 8, SDL_SWSURFACE);
	if (screen == NULL) {
		printf("Couldn't initialize display: %s\n", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	SDL_ShowCursor(SDL_DISABLE);
}

// Quits the program, unloading what's needed
void quit(nSDL_Font* font) {
	nSDL_FreeFont(font);

	SDL_Quit();
}

int main() {
	init();

	nSDL_Font* font;
	font = nSDL_LoadFont(NSDL_FONT_FANTASY, 255, 255, 255);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	SDL_bool should_close = SDL_FALSE;

	SDL_Surface* ground_sprite = nSDL_LoadImage(image_ground);
	if (ground_sprite == NULL) {
		return EXIT_FAILURE;
	}
	SDL_Surface* wall_sprite = nSDL_LoadImage(image_wall);
	if (wall_sprite == NULL) {
		return EXIT_FAILURE;
	}

	Level currLevel(level1size.x, level1size.y, level1map, level1playerPos, level1boxes, level1storages, ground_sprite, wall_sprite);


	// Deltatime / framerate vars
	Uint32 last_time = SDL_GetTicks();
	Uint32 current_time = SDL_GetTicks();
	Uint32 delta_time = 1;

	while (!should_close) {
		// Update
		int framerate = int(1.0f/(float(delta_time)*0.001));

		// Event handling
		// This equates to one input per frame
		SDL_Event event;
		int has_event = SDL_PollEvent(&event);
		if (has_event) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					should_close = SDL_TRUE;
				}
				// Put code here to handle key presses with SDLKey event.key.keysym.sym
				break;
			default:
				break;
			}
		}

		
		// Draw

		// Clear screen
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 184, 200, 222));
		
		currLevel.draw(screen);

		// UI
		nSDL_DrawString(screen, font, 10, 10, "FPS: %d \x1", framerate);
		nSDL_DrawString(screen, font, 10, 20, "Press esc to exit... \x1");
		
		
		SDL_Flip(screen);
		

		// Deltatime handling
		current_time = SDL_GetTicks();
		if (current_time >= last_time + TICKRATE) { // Frame already spent enough time rendering
			delta_time = current_time - last_time;
			last_time = current_time;
		} else {
			// Wait the remaining ticks
			SDL_Delay(TICKRATE - (current_time - last_time));
			current_time = SDL_GetTicks();

			delta_time = current_time - last_time;
			last_time = current_time;
		}
	}

	quit(font);

	return EXIT_SUCCESS;
}
