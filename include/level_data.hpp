#ifndef LEVEL_DATA_HPP
#define LEVEL_DATA_HPP

#include "level.hpp"
#include "tile.hpp"

static vec2 level1size = {8, 9};
static TileType level1map[] = {
    GROUND, GROUND, WALL  , WALL  , WALL  , WALL  , WALL  , GROUND,
    WALL  , WALL  , WALL  , GROUND, GROUND, GROUND, WALL  , GROUND,
    WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , GROUND,
    WALL  , WALL  , WALL  , GROUND, GROUND, GROUND, WALL  , GROUND,
    WALL  , GROUND, WALL  , WALL  , GROUND, GROUND, WALL  , GROUND,
    WALL  , GROUND, WALL  , GROUND, GROUND, GROUND, WALL  , WALL  ,
    WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  ,
    WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  ,
    WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  ,
};
static std::vector<vec2> level1boxes = {
    {3, 2},
    {4, 3},
    {4, 4},
    {4, 6},
    {3, 6},
    {5, 6},
    {1, 6},
};
static std::vector<vec2> level1storages = {
    {1, 2},
    {5, 3},
    {1, 4},
    {4, 5},
    {4, 7},
    {3, 6},
    {6, 6},
};
static vec2 level1playerPos = {2, 2};


static vec2 level2size = {14, 10};
static TileType level2map[] = {
    WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , GROUND, GROUND,
    WALL  , GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , WALL  , WALL  ,
    WALL  , GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  ,
    WALL  , GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, WALL  , WALL  , WALL  , WALL  , GROUND, GROUND, WALL  ,
    WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , WALL  , GROUND, GROUND, WALL  ,
    WALL  , GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, WALL  , GROUND, GROUND, GROUND, GROUND, WALL  , WALL  ,
    WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , GROUND, WALL  , WALL  , GROUND, GROUND, GROUND, GROUND, WALL  ,
    GROUND, GROUND, WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  ,
    GROUND, GROUND, WALL  , GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, WALL  ,
    GROUND, GROUND, WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  ,
};
static std::vector<vec2> level2boxes = {
    {6, 3},
    {7, 2},
    {10, 2},
    {10, 5},
    {9, 6},
    {9, 7},
    {11, 6},
    {11, 7},
    {7, 7},
    {4, 7},
};
static std::vector<vec2> level2storages = {
    {1, 1},
    {1, 2},
    {1, 3},
    {1, 4},
    {1, 5},
    
    {2, 1},
    {2, 2},
    {2, 3},
    {2, 4},
    {2, 5},
};
static vec2 level2playerPos = {7, 4};

#endif