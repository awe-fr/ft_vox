#include <View/ViewMap.hpp>

ViewMap::ViewMap(BlockMap *block_map)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[i][j] = new ViewChunk(block_map->getChunk(j, i));
    }
}

ViewMap::~ViewMap(void)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            delete this->_map[i][j];
    }
}

ViewChunk *ViewMap::getChunk(size_t x, size_t y)
{
    return this->_map[y][x];
}