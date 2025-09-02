#ifndef IMAGE_LOADER_HPP
#define IMAGE_LOADER_HPP

#include <SDL/SDL.h>

#define TILE_WIDTH 16
#define TILE_HEIGHT TILE_WIDTH

namespace ImageManager {
    SDL_Surface* getTexture(Uint16* tex_data);
    void unloadTexture(Uint16* tex_data);

    void unloadAllTextures();

    void drawTexture(SDL_Surface* tex, SDL_Surface* screen, int x, int y);
    void drawTexture(SDL_Surface* tex, SDL_Surface* screen, int x, int y, int tex_id);
}

#endif