#include "BlockMapChunk.hpp"

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
                for (size_t i = 0; i < layers.size())
                {
                    if (k + 1 >= layers[i].min_height && k + 1 <= layers[i].max_height)
                    {
                        if (k == height - 1)
                            this->_map[i][j][k] = layers[i].top_block;
                        else
                            this->_map[i][j][k] = layers[i].block;
                        break;
                    }
                }
            }
        }
    }
}

BlockMapChunk::~BlockMapChunk(void) {}