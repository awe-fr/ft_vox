#include <Model/NoiseMap.hpp>

NoiseMap::NoiseMap(Biome biome) : _biome(biome)
{
    std::thread threads[RENDER_DISTANCE * 2 + 1][RENDER_DISTANCE * 2 + 1];

    int y = -(int)(RENDER_DISTANCE);
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    {
        int x = -(int)(RENDER_DISTANCE);
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
        {
            threads[i][j] = std::thread(NoiseMap::generateChunk, this, j, i, x, y, biome);
            x++;
        }
        y++;
    }
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            threads[i][j].join();
    }
}

NoiseMap::~NoiseMap(void)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            delete this->_map[i][j];
    }
}

void NoiseMap::updateUp(void)
{
    // for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    //     delete this->_map[RENDER_DISTANCE * 2][i];this->generateChunk
    for (size_t i = RENDER_DISTANCE * 2; i > 0; i--)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[i][j] = this->_map[i - 1][j];
    }

    int y = this->_map[1][0]->getCoordY() - 1;
    int x = this->_map[1][0]->getCoordX();

    std::thread threads[RENDER_DISTANCE * 2 + 1];
    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i] = std::thread(NoiseMap::generateChunk, this, i, 0, x + i, y, this->_biome);

    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i].join();
}

void NoiseMap::updateDown(void)
{
    // for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    //     delete this->_map[0][i];
    for (size_t i = 0; i < RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[i][j] = this->_map[i + 1][j];
    }

    int y = this->_map[RENDER_DISTANCE * 2 - 1][0]->getCoordY() + 1;
    int x = this->_map[RENDER_DISTANCE * 2 - 1][0]->getCoordX();

    std::thread threads[RENDER_DISTANCE * 2 + 1];
    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i] = std::thread(NoiseMap::generateChunk, this, i, RENDER_DISTANCE * 2, x + i, y, this->_biome);

    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i].join();
}

void NoiseMap::updateLeft(void)
{
    // for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    //     delete this->_map[i][RENDER_DISTANCE * 2];
    for (size_t i = RENDER_DISTANCE * 2; i > 0; i--)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[j][i] = this->_map[j][i - 1];
    }

    int y = this->_map[0][1]->getCoordY();
    int x = this->_map[0][1]->getCoordX() - 1;

    std::thread threads[RENDER_DISTANCE * 2 + 1];
    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i] = std::thread(NoiseMap::generateChunk, this, 0, i, x, y + i, this->_biome);

    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i].join();
}

void NoiseMap::updateRight(void)
{
    // for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    //     delete this->_map[i][0];
    for (size_t i = 0; i < RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[j][i] = this->_map[j][i + 1];
    }

    int y = this->_map[0][RENDER_DISTANCE * 2 - 1]->getCoordY();
    int x = this->_map[0][RENDER_DISTANCE * 2 - 1]->getCoordX() + 1;

    std::thread threads[RENDER_DISTANCE * 2 + 1];
    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i] = std::thread(NoiseMap::generateChunk, this, RENDER_DISTANCE * 2, i, x, y + i, this->_biome);

    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        threads[i].join();
}

NoiseMapChunk *NoiseMap::getChunk(size_t x, size_t y)
{
    return this->_map[y][x];
}

void NoiseMap::generateChunk(NoiseMap *map, size_t map_x, size_t map_y, int chunk_x, int chunk_y, Biome biome)
{
    map->_map[map_y][map_x] = new NoiseMapChunk(chunk_x, chunk_y, biome);
}
