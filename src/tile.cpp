#include "tile.hpp"
#include "image_manager.hpp"
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
	ImageManager::drawTile(this->sprite, screen, 
		(this->gridPos.x * TILE_WIDTH) + offset.x,
		(this->gridPos.y * TILE_HEIGHT) + offset.y
	);
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


Player::Player(vec2 gridPos) : MovableTile(gridPos, ImageManager::getTexture(image_player)) {
	this->direction = DIR_DOWN;
}
Player::~Player() {}

void Player::draw(SDL_Surface* screen, vec2 offset) {
	ImageManager::drawTile(this->sprite, screen, 
		(this->gridPos.x * TILE_WIDTH) + offset.x,
		(this->gridPos.y * TILE_HEIGHT) + offset.y,
		this->direction
	);
}

void Player::moveLeft() {
	this->moveLeft(true);
}

void Player::moveRight() {
	this->moveRight(true);
}

void Player::moveUp() {
	this->moveUp(true);
}

void Player::moveDown() {
	this->moveDown(true);
}

void Player::moveLeft(bool change_direction) {
	if (change_direction) {
		this->direction = DIR_LEFT;
	}
	MovableTile::moveLeft();
}

void Player::moveRight(bool change_direction) {
	if (change_direction) {
		this->direction = DIR_RIGHT;
	}
	MovableTile::moveRight();
}

void Player::moveUp(bool change_direction) {
	if (change_direction) {
		this->direction = DIR_UP;
	}
	MovableTile::moveUp();
}

void Player::moveDown(bool change_direction) {
	if (change_direction) {
		this->direction = DIR_DOWN;
	}
	MovableTile::moveDown();
}


Box::Box(vec2 gridPos) : MovableTile(gridPos, ImageManager::getTexture(image_box)) {
	this->placed = false;
}
Box::~Box() {}

void Box::draw(SDL_Surface* screen, vec2 offset) {
	ImageManager::drawTile(this->sprite, screen, 
		(this->gridPos.x * TILE_WIDTH) + offset.x,
		(this->gridPos.y * TILE_HEIGHT) + offset.y,
		this->placed ? 1 : 0
	);
}


Storage::Storage(vec2 gridPos) : Tile(gridPos, ImageManager::getTexture(image_storage)) {}
Storage::~Storage() {}