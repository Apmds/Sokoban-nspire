#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SDL/SDL.h>
#include "tile.hpp"
#include <vector>
#include <deque>

typedef struct level_state level_state;

class Level {
private:
    int width;
    int height;
    int player_steps;
    TileType* grid;
    Player player;
    std::vector<Box> boxes;
    std::vector<Storage> storages;
    std::deque<level_state> states;
    SDL_Surface* ground_sprite;
    SDL_Surface* wall_sprite;
    bool is_completed;
    
    bool isTileColliding(Tile tile);
    Box* getCollidingBox(Tile tile);
    void updateBox(Box* box);
    void updateBox(Box& box);
    void registerState(level_state state);
public:
    Level(int w, int h, TileType* grid, vec2 playerPos, std::vector<vec2> boxes, std::vector<vec2> storages);
    ~Level();

    void draw(SDL_Surface* screen);

    Player& getPlayer();
    void movePlayerUp();
    void movePlayerDown();
    void movePlayerLeft();
    void movePlayerRight();

    bool isCompleted();
    int getSteps();
    void rewind();
};


#endif