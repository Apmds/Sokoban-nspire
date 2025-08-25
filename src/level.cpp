#include "level.hpp"

Level::Level(int w, int h, TileType* grid, vec2 playerPos, std::vector<vec2> boxes, std::vector<vec2> storages, SDL_Surface* ground_sprite, SDL_Surface* wall_sprite) {
    this->width = w;
    this->height = h;
    this->grid = grid;
    
    // this.player = ;

    //this->boxes = ;
    //this->storages = ;
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
}
