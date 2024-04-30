#include "BlockMapChunk.hpp"
#include <iostream>

BlockMapChunk::BlockMapChunk(NoiseMapChunk noise_chunk) : _coord{noise_chunk.getCoordX(), noise_chunk.getCoordY()}
{
    std::vector<BlockLayer> layers = noise_chunk.getBlockLayers();
    for (size_t i = 0; i < CHUNK_SIZE; i++)
    {
        for (size_t j = 0; j < CHUNK_SIZE; j++)
        {
            unsigned char height = noise_chunk.getValue(j, i);
            for (size_t k = 0; k < height; k++)
            {
                for (size_t l = 0; l < layers.size(); l++)
                {
                    if (k + 1 >= layers[l].min_height && k + 1 <= layers[l].max_height)
                    {
                        if (k == height - 1)
                            this->_map[i][j][k] = layers[l].top_block;
                        else
                            this->_map[i][j][k] = layers[l].block;
                        break;
                    }
                }
            }
            for (size_t k = height; k < CHUNK_HEIGHT; k++)
                this->_map[i][j][k] = Void();
        }
    }
}

BlockMapChunk::~BlockMapChunk(void) {}