#include "imageLoader.hpp"
#include <unordered_map>

static std::unordered_map<Uint16*, SDL_Surface*> map;

SDL_Surface* ImageLoader::getTexture(Uint16* tex_data) {
    // Texture not loaded yet
    if (map.find(tex_data) == map.end()) {
        SDL_Surface* tex = nSDL_LoadImage(tex_data);
        if (tex == NULL) {
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(tex, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(tex->format, 0, 0, 0));
        map[tex_data] = tex;

        return tex;
    }

    return map[tex_data];
}

void ImageLoader::unloadTexture(Uint16* tex_data) {
    if (map.find(tex_data) == map.end()) {
        return;
    }

    SDL_FreeSurface(map[tex_data]);
    map.erase(tex_data);
}

void ImageLoader::unloadAllTextures() {
    for (auto kv : map) {
        SDL_FreeSurface(kv.second);
    }
    map.clear();
}