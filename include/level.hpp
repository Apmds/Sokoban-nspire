#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SDL/SDL.h>
#include "tile.hpp"
#include <vector>

class Level {
private:
    int width;
    int height;
    TileType* grid;
    Player player;
    std::vector<Box> boxes;
    std::vector<Storage> storages;
    SDL_Surface* ground_sprite;
    SDL_Surface* wall_sprite;
    bool is_completed;
    
    bool isTileColliding(Tile tile);
    Box* getCollidingBox(Tile tile);
    void updateBox(Box* box);
public:
    Level(int w, int h, TileType* grid, vec2 playerPos, std::vector<vec2> boxes, std::vector<vec2> storages, SDL_Surface* ground_sprite, SDL_Surface* wall_sprite);
    ~Level();

    void draw(SDL_Surface* screen);

    Player& getPlayer();
    void movePlayerUp();
    void movePlayerDown();
    void movePlayerLeft();
    void movePlayerRight();

    bool isCompleted();
};


#endif