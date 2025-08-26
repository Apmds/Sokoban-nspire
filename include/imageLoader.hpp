#ifndef IMAGE_LOADER_HPP
#define IMAGE_LOADER_HPP

#include <SDL/SDL.h>

namespace ImageLoader {
    SDL_Surface* getTexture(Uint16* tex_data);
    void unloadTexture(Uint16* tex_data);

    void unloadAllTextures();
}

#endif