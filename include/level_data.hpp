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


static vec2 level3size = {17, 10};
static TileType level3map[] = {
    GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , GROUND,
    GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , GROUND,
    GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, GROUND, WALL  , GROUND, GROUND, WALL  , WALL  , GROUND,
    GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, GROUND,
    GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , WALL  , GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, GROUND,
    WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , GROUND, GROUND, GROUND, WALL  , GROUND, WALL  , WALL  , WALL  ,
    WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  ,
    WALL  , WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  ,
    WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  ,
    WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND,
};
static std::vector<vec2> level3boxes = {
    {10, 2},
    {10, 3},
    {10, 4},
    {10, 5},
    {10, 6},
    {9, 7},

    {12, 2},
    {13, 3},
    {12, 4},
    {13, 6},
    {12, 7},
};
static std::vector<vec2> level3storages = {
    {1, 6},
    {2, 6},
    {3, 6},
    {4, 6},
    
    {2, 7},
    {3, 7},
    {4, 7},
    
    {1, 8},
    {2, 8},
    {3, 8},
    {4, 8},
};
static vec2 level3playerPos = {14, 1};


static vec2 level4size = {17, 13};
static TileType level4map[] = {
    GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , WALL  , WALL  , WALL  , WALL  , GROUND, GROUND, GROUND, GROUND,
    GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, GROUND, GROUND, WALL  , WALL  , WALL  , WALL  , WALL  ,
    GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, WALL  , GROUND, WALL  , WALL  , GROUND, GROUND, WALL  ,
    GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  ,
    WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , GROUND, WALL  , WALL  , WALL  , GROUND, GROUND, GROUND, WALL  ,
    WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , WALL  , WALL  ,
    WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , WALL  , GROUND,
    WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , GROUND,
    WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , WALL  , GROUND,
    GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , GROUND,
    GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , WALL  , WALL  , GROUND, WALL  , WALL  , GROUND, WALL  , GROUND,
    GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, GROUND, GROUND, GROUND, WALL  , GROUND,
    GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , GROUND,
};
static std::vector<vec2> level4boxes = {
    {11, 2},
    {14, 3},
    {13, 5},
    {10, 5},
    {9, 6},
    {9, 7},
    {11, 6},
    {12, 6},
    {12, 7},
    {11, 8},
    {10, 9},
    {12, 9},
};
static std::vector<vec2> level4storages = {
    {1, 5},
    {2, 5},
    {3, 5},
    {4, 5},

    {1, 6},
    {2, 6},
    {3, 6},
    {4, 6},

    {1, 7},
    {2, 7},
    {3, 7},
    {4, 7},
};
static vec2 level4playerPos = {14, 7};


static vec2 level5size = {12, 11};
static TileType level5map[] = {
    WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , GROUND, GROUND, WALL  , WALL  , WALL  , GROUND,
    WALL  , GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, WALL  , WALL  , GROUND, WALL  , WALL  ,
    WALL  , GROUND, GROUND, GROUND, GROUND, WALL  , WALL  , WALL  , GROUND, GROUND, GROUND, WALL  ,
    WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  ,
    WALL  , GROUND, GROUND, GROUND, GROUND, WALL  , GROUND, WALL  , GROUND, GROUND, GROUND, WALL  ,
    WALL  , GROUND, GROUND, WALL  , WALL  , WALL  , GROUND, WALL  , GROUND, GROUND, GROUND, WALL  ,
    WALL  , WALL  , WALL  , WALL  , GROUND, GROUND, GROUND, WALL  , GROUND, GROUND, GROUND, WALL  ,
    GROUND, GROUND, GROUND, WALL  , GROUND, GROUND, GROUND, WALL  , GROUND, GROUND, GROUND, WALL  ,
    GROUND, GROUND, GROUND, WALL  , GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL  ,
    GROUND, GROUND, GROUND, WALL  , GROUND, GROUND, WALL  , WALL  , GROUND, GROUND, GROUND, WALL  ,
    GROUND, GROUND, GROUND, WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  , WALL  ,
};
static std::vector<vec2> level5boxes = {
    {8, 3},
    {9, 3},
    {9, 4},
    {9, 5},
    {8, 6},
    {9, 7},
    {8, 8},
    
    {5, 8},
    {6, 7},
    {5, 6},
};
static std::vector<vec2> level5storages = {
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
static vec2 level5playerPos = {9, 1};

#endif