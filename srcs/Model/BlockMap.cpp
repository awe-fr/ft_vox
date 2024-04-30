#include <Model/BlockMap.hpp>

BlockMap::BlockMap(NoiseMap noise_map)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[i][j] = new BlockMapChunk(*noise_map.getChunk(j, i));
    }
}

BlockMap::~BlockMap(void)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            delete this->_map[i][j];
    }
}

void BlockMap::updateUp(NoiseMap noise_map)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
        delete this->_map[RENDER_DISTANCE * 2][i];
    for (size_t i = RENDER_DISTANCE * 2; i > 0; i--)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[i][j] = this->_map[i - 1][j];
    }

    for (int i = 0; i < 0; i++)
        this->_map[0][i] = new BlockMapChunk(*noise_map.getChunk(i, 0));
}

void BlockMap::updateDown(NoiseMap noise_map)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
        delete this->_map[0][i];
    for (size_t i = 0; i < RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[i][j] = this->_map[i + 1][j];
    }

    for (int i = 0; i < 10; i++)
        this->_map[RENDER_DISTANCE * 2][i] = new BlockMapChunk(*noise_map.getChunk(i, RENDER_DISTANCE * 2));
}

void BlockMap::updateLeft(NoiseMap noise_map)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
        delete this->_map[i][RENDER_DISTANCE * 2];
    for (size_t i = RENDER_DISTANCE * 2; i > 0; i--)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[j][i] = this->_map[i][j - 1];
    }

    for (int i = 0; i < 10; i++)
        this->_map[i][0] = new BlockMapChunk(*noise_map.getChunk(0, i));
}

void BlockMap::updateRight(NoiseMap noise_map)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
        delete this->_map[i][0];
    for (size_t i = 0; i < RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[j][i] = this->_map[j][i + 1];
    }

    for (int i = 0; i < 10; i++)
        this->_map[i][RENDER_DISTANCE * 2] = new BlockMapChunk(*noise_map.getChunk(RENDER_DISTANCE * 2, i));
}

BlockMapChunk *BlockMap::getChunk(size_t x, size_t y)
{
    return this->_map[y][x];
}