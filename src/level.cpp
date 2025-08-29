#include "level.hpp"

Level::Level(int w, int h, TileType* grid, vec2 playerPos, std::vector<vec2> boxes, std::vector<vec2> storages, SDL_Surface* ground_sprite, SDL_Surface* wall_sprite) : player(playerPos) {
    this->width = w;
    this->height = h;
    this->grid = grid;
    this->is_completed = false;
    
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
    for (auto storage : this->storages) {
        storage.draw(screen, level_offset);
    }
    for (auto box : this->boxes) {
        box.draw(screen, level_offset);
    }
    
    // Draw the player
    this->player.draw(screen, level_offset);
}

Player& Level::getPlayer() {
    return this->player;
}


void Level::movePlayerUp() {
    this->player.moveUp();

    if (this->isTileColliding(this->player)) {
        this->player.moveDown();
    }

    // If player is colliding with a box, then move and check collision on it
    Box* collidingBox = this->getCollidingBox(this->player);
    if (collidingBox == nullptr) {
        return;
    }

    collidingBox->moveUp();
    if (this->isTileColliding(*collidingBox) || this->getCollidingBox(*collidingBox) != nullptr) {
        collidingBox->moveDown();
        this->player.moveDown();
        return;
    }
    this->updateBox(collidingBox);
}

void Level::movePlayerDown() {
    this->player.moveDown();

    if (this->isTileColliding(this->player)) {
        this->player.moveUp();
    }

    // If player is colliding with a box, then move and check collision on it
    Box* collidingBox = this->getCollidingBox(this->player);
    if (collidingBox == nullptr) {
        return;
    }

    collidingBox->moveDown();
    if (this->isTileColliding(*collidingBox) || this->getCollidingBox(*collidingBox) != nullptr) {
        collidingBox->moveUp();
        this->player.moveUp();
        return;
    }
    this->updateBox(collidingBox);
}

void Level::movePlayerLeft() {
    this->player.moveLeft();

    if (this->isTileColliding(this->player)) {
        this->player.moveRight();
    }
    

    // If player is colliding with a box, then move and check collision on it
    Box* collidingBox = this->getCollidingBox(this->player);
    if (collidingBox == nullptr) {
        return;
    }

    collidingBox->moveLeft();
    if (this->isTileColliding(*collidingBox) || this->getCollidingBox(*collidingBox) != nullptr) {
        collidingBox->moveRight();
        this->player.moveRight();
        return;
    }
    this->updateBox(collidingBox);
}

void Level::movePlayerRight() {
    this->player.moveRight();
    
    if (this->isTileColliding(this->player)) {
        this->player.moveLeft();
        return;
    }

    // If player is colliding with a box, then move and check collision on it
    Box* collidingBox = this->getCollidingBox(this->player);
    if (collidingBox == nullptr) {
        return;
    }

    
    collidingBox->moveRight();
    if (this->isTileColliding(*collidingBox) || this->getCollidingBox(*collidingBox) != nullptr) {
        collidingBox->moveLeft();
        this->player.moveLeft();
        return;
    }
    this->updateBox(collidingBox);
}

bool Level::isTileColliding(Tile tile) {
    vec2 tilePos = tile.getPosition();
    int tileGridPos = tilePos.x + (tilePos.y*this->width);

    // In level bounds and inside a wall
    if (tileGridPos < this->width * this->height && tileGridPos > 0 && this->grid[tileGridPos] == WALL) {
        return true;
    }

    return false;
}

Box* Level::getCollidingBox(Tile tile) {
    for (auto& box : this->boxes) {
        if (tile.getId() != box.getId() && tile.getPosition().x == box.getPosition().x && tile.getPosition().y == box.getPosition().y) {
            return &box;
        }
    }

    return nullptr;
}

bool Level::isCompleted() {
    return this->is_completed;
}

void Level::updateBox(Box* box) {
    box->placed = false;
    for (auto storage : storages) {
        if (storage.getPosition().x == box->getPosition().x && storage.getPosition().y == box->getPosition().y) {
            box->placed = true;
            break;
        }
    }

    this->is_completed = true;
    for (auto box : boxes) {
        if (!box.placed) {
            this->is_completed = false;
            break;
        }
    }
}
