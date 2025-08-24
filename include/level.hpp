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
    // Player player;
    // 
    std::vector<Tile> boxes;
    std::vector<Tile> storages;
public:
    Level(int w, int h, TileType* grid, vec2 playerPos, std::vector<vec2> boxes, std::vector<vec2> storages);
    ~Level();

    void draw(SDL_Surface* screen);
};


#endif