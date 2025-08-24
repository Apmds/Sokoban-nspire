#include "level.hpp"

Level::Level(int w, int h, TileType* grid, vec2 playerPos, std::vector<vec2> boxes, std::vector<vec2> storages) {
    this->width = w;
    this->height = h;
    this->grid = grid;
    
    // this.player = ;

    //this->boxes = ;
    //this->storages = ;
}

Level::~Level() {
}
