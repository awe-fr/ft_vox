#pragma once

#include "BlockMapChunk.hpp"
#include "NoiseMap.hpp"

class BlockMap
{
    public:
        BlockMap(NoiseMap noise_map);
        ~BlockMap(void);

        void updateUp(NoiseMap noise_map);
        void updateDown(NoiseMap noise_map);
        void updateLeft(NoiseMap noise_map);
        void updateRight(NoiseMap noise_map);

        BlockMapChunk   *getChunk(size_t x, size_t y);

    private:
        BlockMapChunk   *_map[RENDER_DISTANCE * 2 + 1][RENDER_DISTANCE * 2 + 1];
};