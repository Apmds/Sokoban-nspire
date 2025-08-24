#include "tile.hpp"

Tile::Tile(vec2 gridPos, SDL_Surface* sprite) {
    this->gridPos = gridPos;
    this->sprite = sprite;
}

Tile::~Tile() {
}

void Tile::draw(SDL_Surface* screen) {
    SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = TILE_WIDTH;
	src.h = TILE_HEIGHT;

	SDL_Rect pos;
	pos.x = this->gridPos.x * TILE_WIDTH;
	pos.y = this->gridPos.y * TILE_HEIGHT;

	SDL_BlitSurface(this->sprite, &src, screen, &pos);
}
