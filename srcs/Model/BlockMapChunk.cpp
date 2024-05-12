#include <Model/BlockMapChunk.hpp>

BlockMapChunk::BlockMapChunk(NoiseMapChunk noise_chunk) : _coord{noise_chunk.getCoordX(), noise_chunk.getCoordY()}
{
    // std::vector<BlockLayer> layers = noise_chunk.getBlockLayers();
    for (size_t i = 0; i < CHUNK_SIZE; i++)
    {
        float y_t = (float)this->_coord[1] / TEMPERATURE_SCALE + ((float)i / (float)CHUNK_SIZE) / TEMPERATURE_SCALE;
        for (size_t j = 0; j < CHUNK_SIZE; j++)
        {
            float x_t = (float)this->_coord[0] / TEMPERATURE_SCALE + ((float)j / (float)CHUNK_SIZE) / TEMPERATURE_SCALE;

            float temp_noise = octaves(x_t, y_t, 0.5f, 2.f, 1.f, 1.f / TEMPERATURE_SCALE, 1);
            Biome biome = get_biome(temp_noise);
            std::vector<BlockLayer> layers = biome.getBlockLayers();

            unsigned char height = noise_chunk.getValue(j, i);
            for (size_t k = CHUNK_HEIGHT - 1; k >= height; k--)
                this->_map[i][j][k] = Void();
            for (size_t k = height - 1; k > 0; k--)
            {
                for (size_t l = 0; l < layers.size(); l++)
                {
                    if (k + 1 >= layers[l].min_height && k + 1 <= layers[l].max_height)
                    {
                        if (k == (size_t)(height - 1))
                            this->_map[i][j][k] = layers[l].top_block;
                        else if (k >= (size_t)(height - 1) - layers[l].subtop_height)
                            this->_map[i][j][k] = layers[l].subtop_block;
                        else
                            this->_map[i][j][k] = layers[l].bottom_block;
                        break;
                    }
                }
            }
        }
    }
}

Biome get_biome(float noise)
{
    if (noise <= -0.333f)
        return TestSnow();
    if (noise <= 0.333f)
        return TestPlain();
    return TestDesert();
}

BlockMapChunk::~BlockMapChunk(void) {}

Block BlockMapChunk::getBlock(size_t x, size_t y, size_t z)
{
    return this->_map[y][x][z];
}

int BlockMapChunk::getCoordX(void)
{
    return this->_coord[0];
}

int BlockMapChunk::getCoordY(void)
{
    return this->_coord[1];
}