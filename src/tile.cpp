#include "tile.hpp"
#include "imageLoader.hpp"
#include "image_data.hpp"

static int tileid = 0;

Tile::Tile(vec2 gridPos, SDL_Surface* sprite) {
    this->gridPos = gridPos;
    this->sprite = sprite;
	this->id = tileid++;
}

Tile::~Tile() {}

void Tile::draw(SDL_Surface* screen) {
	this->draw(screen, {0, 0});
}

void Tile::draw(SDL_Surface* screen, vec2 offset) {
    SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = TILE_WIDTH;
	src.h = TILE_HEIGHT;

	SDL_Rect pos;
	pos.x = (this->gridPos.x * TILE_WIDTH) + offset.x;
	pos.y = (this->gridPos.y * TILE_HEIGHT) + offset.y;

	SDL_BlitSurface(this->sprite, &src, screen, &pos);
}

vec2 Tile::getPosition() {
	return this->gridPos;
}

int Tile::getId() {
	return this->id;
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


Box::Box(vec2 gridPos) : MovableTile(gridPos, ImageLoader::getTexture(image_box)) {
	this->placed = false;
}
Box::~Box() {}


Storage::Storage(vec2 gridPos) : Tile(gridPos, ImageLoader::getTexture(image_storage)) {}
Storage::~Storage() {}