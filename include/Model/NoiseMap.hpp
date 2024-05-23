#pragma once

#include "NoiseMapChunk.hpp"

class NoiseMap
{
    public:
        NoiseMap(void);
        ~NoiseMap(void);

        void updateRight(void);
        void updateLeft(void);
        void updateUp(void);
        void updateDown(void);

        NoiseMapChunk *getChunk(size_t x, size_t y);

    private:
        NoiseMapChunk *_map[RENDER_DISTANCE * 2 + 1][RENDER_DISTANCE * 2 + 1];
        
        static void generateChunk(NoiseMap *map, size_t map_x, size_t map_y, int chunk_x, int chunk_y);
};
