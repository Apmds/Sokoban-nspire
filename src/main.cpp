#include <SDL/SDL.h>
#include <SDL/SDL_config.h>
#include "image_manager.hpp"
#include "menu.hpp"

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
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
}

int main() {
	init();

	std::unique_ptr<Menu> menu = std::make_unique<MainMenu>();

	SDL_bool should_close = SDL_FALSE;

	// Deltatime / framerate vars
	Uint32 last_time = SDL_GetTicks();
	Uint32 current_time = SDL_GetTicks();
	Uint32 delta_time = current_time - last_time;

	while (!should_close) {
		// Event handling
		// This equates to one input per frame
		SDL_Event event;
		int has_event = SDL_PollEvent(&event);
		if (has_event) {
			switch (event.type) {
			case SDL_KEYDOWN: {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					should_close = SDL_TRUE;
				}

				// Handle input and possible switching
				std::unique_ptr<Menu> new_menu = menu->input(event.key.keysym.sym);
				if (new_menu != nullptr) {
					menu = std::move(new_menu);
				}
				break;
			}
			default:
				break;
			}
		}

		// Handle update and possible switching
		std::unique_ptr<Menu> new_menu = menu->update(delta_time);
		if (new_menu != nullptr) {
			menu = std::move(new_menu);
		}

		// Draw
		menu->draw(screen);

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

	ImageManager::unloadAllTextures();
	SDL_Quit();

	return EXIT_SUCCESS;
}
