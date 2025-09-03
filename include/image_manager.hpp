#ifndef IMAGE_LOADER_HPP
#define IMAGE_LOADER_HPP

#include <SDL/SDL.h>

#define TILE_WIDTH 16
#define TILE_HEIGHT TILE_WIDTH

namespace ImageManager {
    SDL_Surface* getTexture(Uint16* tex_data);      // Returns a newly loaded or previously cached texture based on the byte data
    void unloadTexture(Uint16* tex_data);           // Unloads a previously loaded texture

    void unloadAllTextures();       // Calls ImageManager::unloadTexture() on all loaded textures

    void drawTile(SDL_Surface* tex, SDL_Surface* screen, int x, int y);                 // Draws the first tile of a tile texture to the screen
    void drawTile(SDL_Surface* tex, SDL_Surface* screen, int x, int y, int tile_id);    // Draws a tile of a tile texture to the screen
    void drawTexture(SDL_Surface* tex, SDL_Surface* screen, int x, int y);              // Draws a texture to the screen
}

#endif