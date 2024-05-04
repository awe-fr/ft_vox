#pragma once

#include <thread>

#include "NoiseMapChunk.hpp"

class NoiseMap
{
    public:
        NoiseMap(Biome biome);
        ~NoiseMap(void);

        void updateRight(void);
        void updateLeft(void);
        void updateUp(void);
        void updateDown(void);

        NoiseMapChunk *getChunk(size_t x, size_t y);

    private:
        NoiseMapChunk *_map[RENDER_DISTANCE * 2 + 1][RENDER_DISTANCE * 2 + 1];
        Biome _biome;
        
        static void generateChunk(NoiseMap *map, size_t map_x, size_t map_y, int chunk_x, int chunk_y, Biome biome);
};
