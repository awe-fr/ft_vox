#include <View/ViewMap.hpp>

extern std::mutex stop;

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

void ViewMap::updateUp(BlockMap *block_map)
{
    // for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    //     delete this->_map[RENDER_DISTANCE * 2][i];
    stop.lock();
    for (size_t i = RENDER_DISTANCE * 2; i > 0; i--)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[i][j] = this->_map[i - 1][j];
    }
    stop.unlock();
    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        this->_map[0][i] = new ViewChunk(block_map->getChunk(i, 0));
}

void ViewMap::updateDown(BlockMap *block_map)
{
    // for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    //     delete this->_map[0][i];
    stop.lock();
    for (size_t i = 0; i < RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[i][j] = this->_map[i + 1][j];
    }
    stop.unlock();
    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        this->_map[RENDER_DISTANCE * 2][i] = new ViewChunk(block_map->getChunk(i, RENDER_DISTANCE * 2));
}

void ViewMap::updateLeft(BlockMap *block_map)
{
    // for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    //     delete this->_map[i][RENDER_DISTANCE * 2];
    stop.lock();
    for (size_t i = RENDER_DISTANCE * 2; i > 0; i--)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[j][i] = this->_map[j][i - 1];
    }
    stop.unlock();
    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        this->_map[i][0] = new ViewChunk(block_map->getChunk(0, i));
}

void ViewMap::updateRight(BlockMap *block_map)
{
    // for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    //     delete this->_map[i][0];
    stop.lock();
    for (size_t i = 0; i < RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[j][i] = this->_map[j][i + 1];
    }
    stop.unlock();
    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        this->_map[i][RENDER_DISTANCE * 2] = new ViewChunk(block_map->getChunk(RENDER_DISTANCE * 2, i));
}