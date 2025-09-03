#include "image_manager.hpp"
#include <unordered_map>

static std::unordered_map<Uint16*, SDL_Surface*> map;

SDL_Surface* ImageManager::getTexture(Uint16* tex_data) {
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

void ImageManager::unloadTexture(Uint16* tex_data) {
    if (map.find(tex_data) == map.end()) {
        return;
    }

    SDL_FreeSurface(map[tex_data]);
    map.erase(tex_data);
}

void ImageManager::unloadAllTextures() {
    for (auto kv : map) {
        SDL_FreeSurface(kv.second);
    }
    map.clear();
}

void ImageManager::drawTile(SDL_Surface* tex, SDL_Surface* screen, int x, int y) {
    drawTile(tex, screen, x, y, 0);
}

void ImageManager::drawTile(SDL_Surface* tex, SDL_Surface* screen, int x, int y, int tile_id) {
    SDL_Rect src;
	src.x = tile_id * TILE_WIDTH;
	src.y = 0;
	src.w = TILE_WIDTH;
	src.h = TILE_HEIGHT;

	SDL_Rect pos;
	pos.x = x;
	pos.y = y;

	SDL_BlitSurface(tex, &src, screen, &pos);
}

void ImageManager::drawTexture(SDL_Surface* tex, SDL_Surface* screen, int x, int y) {
    SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = tex->w;
	src.h = tex->h;

	SDL_Rect pos;
	pos.x = x;
	pos.y = y;

	SDL_BlitSurface(tex, &src, screen, &pos);
}
