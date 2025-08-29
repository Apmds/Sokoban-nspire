#include <os.h>
#include "level.hpp"
#include "level_data.hpp"
#include <SDL/SDL_config.h>
#include <SDL/SDL.h>
#include <math.h>
#include "imageLoader.hpp"
#include <stdexcept>

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

void handle_input(SDLKey sym, Level& level) {
	switch (sym) {
	case SDLK_UP:
	case SDLK_8:
		level.movePlayerUp();
		break;
	case SDLK_DOWN:
	case SDLK_2:
		level.movePlayerDown();
		break;

	case SDLK_LEFT:
	case SDLK_4:
		level.movePlayerLeft();
		break;

	case SDLK_RIGHT:
	case SDLK_6:
		level.movePlayerRight();
		break;

	default:
		break;
	}
}

Level load_level(int num) {
	switch (num) {
	case 1:
		return Level(level1size.x, level1size.y, level1map, level1playerPos, level1boxes, level1storages);
	case 2:
		return Level(level2size.x, level2size.y, level2map, level2playerPos, level2boxes, level2storages);
	default:
		throw std::invalid_argument("Unknown level number.");
	}
}

int main() {
	init();

	nSDL_Font* font;
	font = nSDL_LoadFont(NSDL_FONT_FANTASY, 255, 255, 255);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	SDL_bool should_close = SDL_FALSE;

	Level currLevel = load_level(1);	

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
				handle_input(event.key.keysym.sym, currLevel);
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
		
		if (currLevel.isCompleted()) {
			nSDL_DrawString(screen, font, 60, 120, "\x1 \x1 Yay, the level is completed! \x1 \x1");
			SDL_Flip(screen);
			SDL_Delay(1000);
			currLevel = load_level(2);
			continue;
		}
		
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

	nSDL_FreeFont(font);
	ImageLoader::unloadAllTextures();
	SDL_Quit();

	return EXIT_SUCCESS;
}
