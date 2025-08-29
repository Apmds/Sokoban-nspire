#ifndef TILE_HPP
#define TILE_HPP

#include <SDL/SDL.h>

#define TILE_WIDTH 16
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

// Base class
class Tile {
protected:
    vec2 gridPos;
    SDL_Surface* sprite;
    int id;
public:
    Tile(vec2 gridPos, SDL_Surface* sprite);
    ~Tile();

    void draw(SDL_Surface* screen, vec2 offset);
    void draw(SDL_Surface* screen);

    vec2 getPosition();
    int getId();
};

class MovableTile : public Tile {
public:
    MovableTile(vec2 gridPos, SDL_Surface* sprite);
    ~MovableTile();
    
    void moveTo(vec2 pos);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
};

class Player : public MovableTile {
public:
    Player(vec2 gridPos);
    ~Player();
};

class Box : public MovableTile {
public:
    Box(vec2 gridPos);
    ~Box();
};

class Storage : public MovableTile {
public:
    Storage(vec2 gridPos);
    ~Storage();
};

#endif