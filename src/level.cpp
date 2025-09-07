#include "level.hpp"
#include "image_data.hpp"
#include "image_manager.hpp"

#define MAX_SAVED_STATES 20

struct level_state {
    vec2 playerMovement;
    PlayerDirection playerDir;
    bool movedBox;
};

Level::Level(int w, int h, TileType* grid, vec2 playerPos, std::vector<vec2> boxes, std::vector<vec2> storages) : player(playerPos) {
    this->width = w;
    this->height = h;
    this->grid = grid;
    this->is_completed = false;
    this->player_steps = 0;
    
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
    this->player_steps++;

    if (this->isTileColliding(this->player)) {
        this->player.moveDown(false);
        this->player_steps--;
        this->registerState({.playerMovement = {0, 0}, .playerDir = this->player.getDirection(), .movedBox = false});
        return;
    }

    // If player is colliding with a box, then move and check collision on it
    Box* collidingBox = this->getCollidingBox(this->player);
    if (collidingBox == nullptr) {
        this->registerState({.playerMovement = {0, -1}, .playerDir = this->player.getDirection(), .movedBox = false});
        return;
    }

    collidingBox->moveUp();
    if (this->isTileColliding(*collidingBox) || this->getCollidingBox(*collidingBox) != nullptr) {
        collidingBox->moveDown();
        this->player.moveDown(false);
        this->player_steps--;
        return;
    }
    this->updateBox(collidingBox);

    this->registerState({.playerMovement = {0, -1}, .playerDir = this->player.getDirection(), .movedBox = true});
}

void Level::movePlayerDown() {
    this->player.moveDown();
    this->player_steps++;

    if (this->isTileColliding(this->player)) {
        this->player.moveUp(false);
        this->player_steps--;
        this->registerState({.playerMovement = {0, 0}, .playerDir = this->player.getDirection(), .movedBox = false});
        return;
    }

    // If player is colliding with a box, then move and check collision on it
    Box* collidingBox = this->getCollidingBox(this->player);
    if (collidingBox == nullptr) {
        this->registerState({.playerMovement = {0, 1}, .playerDir = this->player.getDirection(), .movedBox = false});
        return;
    }

    collidingBox->moveDown();
    if (this->isTileColliding(*collidingBox) || this->getCollidingBox(*collidingBox) != nullptr) {
        collidingBox->moveUp();
        this->player.moveUp(false);
        this->player_steps--;
        return;
    }
    this->updateBox(collidingBox);

    this->registerState({.playerMovement = {0, 1}, .playerDir = this->player.getDirection(), .movedBox = true});
}

void Level::movePlayerLeft() {
    this->player.moveLeft();
    this->player_steps++;

    if (this->isTileColliding(this->player)) {
        this->player.moveRight(false);
        this->player_steps--;
        this->registerState({.playerMovement = {0, 0}, .playerDir = this->player.getDirection(), .movedBox = false});
        return;
    }
    

    // If player is colliding with a box, then move and check collision on it
    Box* collidingBox = this->getCollidingBox(this->player);
    if (collidingBox == nullptr) {
        this->registerState({.playerMovement = {-1, 0}, .playerDir = this->player.getDirection(), .movedBox = false});
        return;
    }

    collidingBox->moveLeft();
    if (this->isTileColliding(*collidingBox) || this->getCollidingBox(*collidingBox) != nullptr) {
        collidingBox->moveRight();
        this->player.moveRight(false);
        this->player_steps--;
        return;
    }
    this->updateBox(collidingBox);

    this->registerState({.playerMovement = {-1, 0}, .playerDir = this->player.getDirection(), .movedBox = true});
}

void Level::movePlayerRight() {
    this->player.moveRight();
    this->player_steps++;
    
    if (this->isTileColliding(this->player)) {
        this->player.moveLeft(false);
        this->player_steps--;
        this->registerState({.playerMovement = {0, 0}, .playerDir = this->player.getDirection(), .movedBox = false});
        return;
    }

    // If player is colliding with a box, then move and check collision on it
    Box* collidingBox = this->getCollidingBox(this->player);
    if (collidingBox == nullptr) {
        this->registerState({.playerMovement = {1, 0}, .playerDir = this->player.getDirection(), .movedBox = false});
        return;
    }

    
    collidingBox->moveRight();
    if (this->isTileColliding(*collidingBox) || this->getCollidingBox(*collidingBox) != nullptr) {
        collidingBox->moveLeft();
        this->player.moveLeft(false);
        this->player_steps--;
        return;
    }
    this->updateBox(collidingBox);

    this->registerState({.playerMovement = {1, 0}, .playerDir = this->player.getDirection(), .movedBox = true});
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

void Level::updateBox(Box& box) {
    box.placed = false;
    for (auto storage : storages) {
        if (storage.getPosition().x == box.getPosition().x && storage.getPosition().y == box.getPosition().y) {
            box.placed = true;
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

int Level::getSteps() {
    return this->player_steps;
}

void Level::registerState(level_state state) {
    this->states.push_back(state);
    if (this->states.size() > MAX_SAVED_STATES) {
        this->states.pop_front();
    }
}

void Level::rewind() {
    if (this->states.size() <= 0) {
        return;
    }
    level_state& state = this->states.back();
    
    
    this->player.setDirection(state.playerDir);
    
    if (state.movedBox) {
        for (Box& box : this->boxes) {
            vec2 playerPos = this->player.getPosition();
            vec2 boxPos = box.getPosition();
            switch (this->player.getDirection())
            {
            case DIR_UP:
                if (playerPos.x == boxPos.x && playerPos.y - 1 == boxPos.y) {
                    box.moveTo({box.getPosition().x, box.getPosition().y + 1});
                    this->updateBox(box);
                }
                break;
                
            case DIR_DOWN:
                if (playerPos.x == boxPos.x && playerPos.y + 1 == boxPos.y) {
                    box.moveTo({box.getPosition().x, box.getPosition().y - 1});
                    this->updateBox(box);
                }
                break;
            
            case DIR_LEFT:
                if (playerPos.x - 1 == boxPos.x && playerPos.y == boxPos.y) {
                    box.moveTo({box.getPosition().x + 1, box.getPosition().y});
                    this->updateBox(box);
                }
                break;

            case DIR_RIGHT:
                if (playerPos.x + 1 == boxPos.x && playerPos.y == boxPos.y) {
                    box.moveTo({box.getPosition().x - 1, box.getPosition().y});
                    this->updateBox(box);
                }
                break;
            default:
                break;
            }
        }
    }
    
    this->player.moveTo({this->player.getPosition().x - state.playerMovement.x, this->player.getPosition().y - state.playerMovement.y});
    if (state.playerMovement.x != 0 || state.playerMovement.y != 0) {
        this->player_steps--;
    }
    
    this->states.pop_back();
}