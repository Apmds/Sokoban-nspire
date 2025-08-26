#include "tile.hpp"
#include "imageLoader.hpp"
#include "image_data.hpp"

Tile::Tile(vec2 gridPos, SDL_Surface* sprite) {
    this->gridPos = gridPos;
    this->sprite = sprite;
}

Tile::~Tile() {}

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


MovableTile::MovableTile(vec2 gridPos, SDL_Surface* sprite) : Tile(gridPos, sprite) {}
MovableTile::~MovableTile() {}

void MovableTile::moveTo(vec2 pos) {
	this->gridPos = pos;
}

void MovableTile::moveLeft() {
	this->gridPos.x--;
}

void MovableTile::moveRight() {
	this->gridPos.x++;
}

void MovableTile::moveUp() {
	this->gridPos.y--;
}

void MovableTile::moveDown() {
	this->gridPos.y++;	
}


Player::Player(vec2 gridPos) : MovableTile(gridPos, ImageLoader::getTexture(image_player)) {}
Player::~Player() {}