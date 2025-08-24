#ifndef LEVEL_DATA_HPP
#define LEVEL_DATA_HPP

#include "level.hpp"
#include "tile.hpp"

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
    {6, 5},
};
Level level1(8, 9, level1map, (vec2) {2, 2}, level1boxes, level1storages);


#endif