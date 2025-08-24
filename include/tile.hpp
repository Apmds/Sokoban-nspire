#ifndef TILE_HPP
#define TILE_HPP

#include <SDL/SDL.h>

#define TILE_WIDTH 32
#define TILE_HEIGHT TILE_WIDTH

enum TileType {
    PLAYER = 0,
    BOX,
    GROUND,
    WALL,
    STORAGE,
};


typedef struct vec2 {
    int x;
    int y;
} vec2;

class Tile {
private:
    vec2 gridPos;
    SDL_Surface* sprite;
public:
    Tile(vec2 gridPos, SDL_Surface* sprite);
    ~Tile();

    void draw(SDL_Surface* screen);
};


#endif