#pragma once

#include "ModelVars.hpp"
#include "NoiseMapChunk.hpp"
#include "Block.hpp"

class BlockMapChunk
{
    public:
        BlockMapChunk(NoiseMapChunk noise_chunk);
        ~BlockMapChunk(void);

    private:
        Block       _map[CHUNK_SIZE][CHUNK_SIZE][CHUNK_HEIGHT];
        const int   _coord[2];
};