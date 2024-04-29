#pragma once
#include <map>

#include "Chunk.hpp"
#include "Block.hpp"

class Map
{
    public:
        Map(Biome biome);
        ~Map(void);

        const static size_t RENDER_DISTANCE = 10;

        void updateRight(void);
        void updateLeft(void);
        void updateUp(void);
        void updateDown(void);

        Chunk *getChunk(size_t x, size_t y);

    private:
        Chunk *_map[RENDER_DISTANCE * 2 + 1][RENDER_DISTANCE * 2 + 1];
        Biome _biome;
        std::map<int[2], Block> _changes;
};
