#include "Map.hpp"

Map::Map(void)
{
    int y = -(int)(RENDER_DISTANCE);
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    {
        int x = -(int)(RENDER_DISTANCE);
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
        {
            this->_map[i][j] = new Chunk(x, y, Mountain());
            x++;
        }
        y++;
    }
}

Map::~Map(void)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            delete this->_map[i][j];
    }
}

void Map::updateUp(void)
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
    for (int i = x; i < x + 10; i++)
        this->_map[0][i] = new Chunk(x, y, Mountain());
}

void Map::updateDown(void)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
        delete this->_map[0][i];
    for (size_t i = 0; i < RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[i][j] = this->_map[i + 1][j];
    }

    int y = this->_map[RENDER_DISTANCE * 2][0]->getCoordY() + 1;
    int x = this->_map[RENDER_DISTANCE * 2][0]->getCoordX();
    for (int i = x; i < x + 10; i++)
        this->_map[0][i] = new Chunk(x, y, Mountain());
}

void Map::updateLeft(void)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
        delete this->_map[i][RENDER_DISTANCE * 2];
    for (size_t i = RENDER_DISTANCE * 2; i > 0; i--)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[j][i] = this->_map[i][j - 1];
    }

    int y = this->_map[0][1]->getCoordY();
    int x = this->_map[0][1]->getCoordX() - 1;
    for (int i = x; i < x + 10; i++)
        this->_map[i][0] = new Chunk(x, y, Mountain());
}

void Map::updateRight(void)
{
    for (size_t i = 0; i <= RENDER_DISTANCE * 2; i++)
        delete this->_map[i][0];
    for (size_t i = 0; i < RENDER_DISTANCE * 2; i++)
    {
        for (size_t j = 0; j <= RENDER_DISTANCE * 2; j++)
            this->_map[j][i] = this->_map[j][i + 1];
    }

    int y = this->_map[0][RENDER_DISTANCE * 2]->getCoordY();
    int x = this->_map[0][RENDER_DISTANCE * 2]->getCoordX() + 1;
    for (int i = x; i < x + 10; i++)
        this->_map[i][0] = new Chunk(x, y, Mountain());
}

Chunk *Map::getChunk(size_t x, size_t y)
{
    return this->_map[y][x];
}
