#include "level.hpp"

Level::Level(int w, int h, TileType* grid, vec2 playerPos, std::vector<vec2> boxes, std::vector<vec2> storages, SDL_Surface* ground_sprite, SDL_Surface* wall_sprite) : player(playerPos) {
    this->width = w;
    this->height = h;
    this->grid = grid;
    
    for (vec2 boxPos : boxes) {
        this->boxes.push_back(Box(boxPos));
    }
    for (vec2 storagePos : storages) {
        this->storages.push_back(Storage(storagePos));
    }

    this->ground_sprite = ground_sprite;
    this->wall_sprite = wall_sprite;
}

Level::~Level() {
}

void Level::draw(SDL_Surface* screen) {
    // Draw the grid centered
    vec2 level_offset = {(320 - (this->width*TILE_WIDTH)) / 2, (240 - (this->height*TILE_HEIGHT)) / 2};
    for (int i = 0; i < this->width*this->height; i++) {
        SDL_Rect src;
        src.x = 0;
        src.y = 0;
        src.w = TILE_WIDTH;
        src.h = TILE_HEIGHT;

        SDL_Rect pos;
        pos.x = ((i % this->width) * TILE_WIDTH) + level_offset.x;
        pos.y = ((i / this->width) * TILE_HEIGHT) + level_offset.y;

        switch (this->grid[i]) {
        case GROUND:
	        SDL_BlitSurface(this->ground_sprite, &src, screen, &pos);
            break;
        case WALL:
        	SDL_BlitSurface(this->wall_sprite, &src, screen, &pos);
            break;
        
        default:    // Ignore invalid static tiles
            break;
        }
        
    }
    
    // Draw the boxes and storages
    for (auto box : this->boxes) {
        box.draw(screen, level_offset);
    }
    for (auto storage : this->storages) {
        storage.draw(screen, level_offset);
    }
    
    // Draw the player
    this->player.draw(screen, level_offset);
}

Player& Level::getPlayer() {
    return this->player;
}


void Level::movePlayerUp() {
    this->player.moveUp();
    if (this->isPlayerColliding()) {
        this->player.moveDown();
    }
}

void Level::movePlayerDown() {
    this->player.moveDown();
    if (this->isPlayerColliding()) {
        this->player.moveUp();
    }
}

void Level::movePlayerLeft() {
    this->player.moveLeft();
    if (this->isPlayerColliding()) {
        this->player.moveRight();
    }
}

void Level::movePlayerRight() {
    this->player.moveRight();
    if (this->isPlayerColliding()) {
        this->player.moveLeft();
    }
}

bool Level::isPlayerColliding() {
    vec2 playerPos = this->player.getPosition();
    int playerGridPos = playerPos.x + (playerPos.y*this->width);

    // In level bounds and inside a wall
    if (playerGridPos < this->width * this->height && this->grid[playerGridPos] == WALL) {
        return true;
    }

    // Inside a box
    for (Box box : this->boxes) {
        vec2 boxPos = box.getPosition();
        if (playerPos.x == boxPos.x && playerPos.y == boxPos.y) {
            return true;
        }
    }

    return false;
}