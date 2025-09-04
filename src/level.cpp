#include "level.hpp"
#include "image_data.hpp"
#include "image_manager.hpp"

Level::Level(int w, int h, TileType* grid, vec2 playerPos, std::vector<vec2> boxes, std::vector<vec2> storages) : player(playerPos) {
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

    for (Box& box : this->boxes) {
        for (Storage storage : this->storages) {
            if (storage.getPosition().x == box.getPosition().x && storage.getPosition().y == box.getPosition().y) {
                box.placed = true;
                break;
            }
        }
    }

    this->ground_sprite = ImageManager::getTexture(image_ground);
    this->wall_sprite = ImageManager::getTexture(image_wall);
}

Level::~Level() {
}

void Level::draw(SDL_Surface* screen) {
    // Draw the grid centered
    vec2 level_offset = {(320 - (this->width*TILE_WIDTH)) / 2, (240 - (this->height*TILE_HEIGHT)) / 2};
    for (int i = 0; i < this->width*this->height; i++) {
        
        SDL_Surface* tex;
        switch (this->grid[i]) {
            case GROUND:
                tex = this->ground_sprite;
                break;
            case WALL:
                tex = this->wall_sprite;
                break;
            
            default:    // Ignore invalid static tiles
                continue;
        }
        ImageManager::drawTile(tex, screen, ((i % this->width) * TILE_WIDTH) + level_offset.x, ((i / this->width) * TILE_HEIGHT) + level_offset.y);
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
        this->player.moveDown(false);
    }

    // If player is colliding with a box, then move and check collision on it
    Box* collidingBox = this->getCollidingBox(this->player);
    if (collidingBox == nullptr) {
        return;
    }

    collidingBox->moveUp();
    if (this->isTileColliding(*collidingBox) || this->getCollidingBox(*collidingBox) != nullptr) {
        collidingBox->moveDown();
        this->player.moveDown(false);
        return;
    }
    this->updateBox(collidingBox);
}

void Level::movePlayerDown() {
    this->player.moveDown();

    if (this->isTileColliding(this->player)) {
        this->player.moveUp(false);
    }

    // If player is colliding with a box, then move and check collision on it
    Box* collidingBox = this->getCollidingBox(this->player);
    if (collidingBox == nullptr) {
        return;
    }

    collidingBox->moveDown();
    if (this->isTileColliding(*collidingBox) || this->getCollidingBox(*collidingBox) != nullptr) {
        collidingBox->moveUp();
        this->player.moveUp(false);
        return;
    }
    this->updateBox(collidingBox);
}

void Level::movePlayerLeft() {
    this->player.moveLeft();

    if (this->isTileColliding(this->player)) {
        this->player.moveRight(false);
    }
    

    // If player is colliding with a box, then move and check collision on it
    Box* collidingBox = this->getCollidingBox(this->player);
    if (collidingBox == nullptr) {
        return;
    }

    collidingBox->moveLeft();
    if (this->isTileColliding(*collidingBox) || this->getCollidingBox(*collidingBox) != nullptr) {
        collidingBox->moveRight();
        this->player.moveRight(false);
        return;
    }
    this->updateBox(collidingBox);
}

void Level::movePlayerRight() {
    this->player.moveRight();
    
    if (this->isTileColliding(this->player)) {
        this->player.moveLeft(false);
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
        this->player.moveLeft(false);
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
