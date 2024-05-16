#pragma once

#include "ModelVars.hpp"
#include "NoiseMapChunk.hpp"
#include "Block.hpp"

class BlockMapChunk
{
    public:
        BlockMapChunk(NoiseMapChunk noise_chunk);
        ~BlockMapChunk(void);

        Block   getBlock(size_t x, size_t y, size_t z);
        int     getCoordX(void);
		int     getCoordY(void);

    private:
        Block       _map[CHUNK_SIZE][CHUNK_SIZE][CHUNK_HEIGHT];
        const int   _coord[2];
};

Biome get_biome(float noise);
bool is_void(float noise);