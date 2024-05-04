#include <Model/BlockMap.hpp>

BlockMap::BlockMap(NoiseMap *noise_map)
{
    std::thread threads[RENDER_DISTANCE * 2 + 1][RENDER_DISTANCE * 2 + 1];

    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            threads[i][j] = std::thread(BlockMap::generateChunk, this, noise_map, j, i);
    }
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            threads[i][j].join();
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

void BlockMap::updateUp(NoiseMap *noise_map)
{
    // for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    //     delete this->_map[RENDER_DISTANCE * 2][i];
    for (size_t i = RENDER_DISTANCE * 2; i > 0; i--)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[i][j] = this->_map[i - 1][j];
    }

    std::thread threads[RENDER_DISTANCE * 2 + 1];
    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i] = std::thread(BlockMap::generateChunk, this, noise_map, i, 0);

    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i].join();
}

void BlockMap::updateDown(NoiseMap *noise_map)
{
    // for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    //     delete this->_map[0][i];
    for (size_t i = 0; i < RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[i][j] = this->_map[i + 1][j];
    }

    std::thread threads[RENDER_DISTANCE * 2 + 1];
    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i] = std::thread(BlockMap::generateChunk, this, noise_map, i, RENDER_DISTANCE * 2);

    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i].join();
}

void BlockMap::updateLeft(NoiseMap *noise_map)
{
    // for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    //     delete this->_map[i][RENDER_DISTANCE * 2];
    for (size_t i = RENDER_DISTANCE * 2; i > 0; i--)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[j][i] = this->_map[j][i - 1];
    }

    std::thread threads[RENDER_DISTANCE * 2 + 1];
    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i] = std::thread(BlockMap::generateChunk, this, noise_map, 0, i);

    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i].join();
}

void BlockMap::updateRight(NoiseMap *noise_map)
{
    // for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    //     delete this->_map[i][0];
    for (size_t i = 0; i < RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[j][i] = this->_map[j][i + 1];
    }

    std::thread threads[RENDER_DISTANCE * 2 + 1];
    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i] = std::thread(BlockMap::generateChunk, this, noise_map, RENDER_DISTANCE * 2, i);

    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i].join();
}

BlockMapChunk *BlockMap::getChunk(size_t x, size_t y)
{
    return this->_map[y][x];
}

void BlockMap::generateChunk(BlockMap *map, NoiseMap *noise_map, size_t x, size_t y)
{
    map->_map[y][x] = new BlockMapChunk(*noise_map->getChunk(x, y));
}