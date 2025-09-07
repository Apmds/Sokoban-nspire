#ifndef TILE_HPP
#define TILE_HPP

#include <SDL/SDL.h>


enum TileType {
    GROUND,
    WALL,
};

enum PlayerDirection {
    DIR_DOWN = 0,
    DIR_UP,
    DIR_LEFT,
    DIR_RIGHT,
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
private:
    PlayerDirection direction;
public:
    Player(vec2 gridPos);
    ~Player();

    void draw(SDL_Surface* screen, vec2 offset);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void moveLeft(bool change_direction);
    void moveRight(bool change_direction);
    void moveUp(bool change_direction);
    void moveDown(bool change_direction);

    void setDirection(PlayerDirection val);
    PlayerDirection getDirection();
};

class Box : public MovableTile {
public:
    Box(vec2 gridPos);
    ~Box();

    void draw(SDL_Surface* screen, vec2 offset);

    bool placed;
};

class Storage : public Tile {
public:
    Storage(vec2 gridPos);
    ~Storage();
};

#endif