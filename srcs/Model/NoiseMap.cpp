#include <Model/NoiseMap.hpp>

NoiseMap::NoiseMap(void)
{
    int y = -(int)(RENDER_DISTANCE);
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    {
        int x = -(int)(RENDER_DISTANCE);
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
        {
            this->_map[i][j] = new NoiseMapChunk(x, y);
            x++;
        }
        y++;
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
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
        delete this->_map[RENDER_DISTANCE * 2][i];
    for (size_t i = RENDER_DISTANCE * 2; i > 0; i--)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[i][j] = this->_map[i - 1][j];
    }

    int y = this->_map[1][0]->getCoordY() - 1;
    int x = this->_map[1][0]->getCoordX();

    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        this->_map[0][i] = new NoiseMapChunk(x + i, y);
}

void NoiseMap::updateDown(void)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
        delete this->_map[0][i];
    for (size_t i = 0; i < RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[i][j] = this->_map[i + 1][j];
    }

    int y = this->_map[RENDER_DISTANCE * 2 - 1][0]->getCoordY() + 1;
    int x = this->_map[RENDER_DISTANCE * 2 - 1][0]->getCoordX();

    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        this->_map[RENDER_DISTANCE * 2][i] = new NoiseMapChunk(x + i, y);
}

void NoiseMap::updateLeft(void)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
        delete this->_map[i][RENDER_DISTANCE * 2];
    for (size_t i = RENDER_DISTANCE * 2; i > 0; i--)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[j][i] = this->_map[j][i - 1];
    }

    int y = this->_map[0][1]->getCoordY();
    int x = this->_map[0][1]->getCoordX() - 1;

    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        this->_map[i][0] = new NoiseMapChunk(x, y + i);
}

void NoiseMap::updateRight(void)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
        delete this->_map[i][0];
    for (size_t i = 0; i < RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[j][i] = this->_map[j][i + 1];
    }

    int y = this->_map[0][RENDER_DISTANCE * 2 - 1]->getCoordY();
    int x = this->_map[0][RENDER_DISTANCE * 2 - 1]->getCoordX() + 1;

    for (int i = 0; i <= RENDER_DISTANCE * 2; i++)
        this->_map[i][RENDER_DISTANCE * 2] = new NoiseMapChunk(x, y + i);
}

NoiseMapChunk *NoiseMap::getChunk(size_t x, size_t y)
{
    return this->_map[y][x];
}

void NoiseMap::generateChunk(NoiseMap *map, size_t map_x, size_t map_y, int chunk_x, int chunk_y)
{
    map->_map[map_y][map_x] = new NoiseMapChunk(chunk_x, chunk_y);
}
