#pragma once
#include <map>

#include "NoiseMapChunk.hpp"

class NoiseMap
{
    public:
        NoiseMap(Biome biome);
        ~NoiseMap(void);

        const static size_t RENDER_DISTANCE = 10;

        void updateRight(void);
        void updateLeft(void);
        void updateUp(void);
        void updateDown(void);

        NoiseMapChunk *getChunk(size_t x, size_t y);

    private:
        NoiseMapChunk *_map[RENDER_DISTANCE * 2 + 1][RENDER_DISTANCE * 2 + 1];
        Biome _biome;
};
