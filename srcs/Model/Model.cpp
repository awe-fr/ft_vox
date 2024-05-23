#include <Model/Model.hpp>

t_offsets offsets;

Model::Model(void)
{
    offsets.continental = rand() % 20000 - 10000;
    offsets.erosion = rand() % 20000 - 10000;
    offsets.peaks_and_valleys = rand() % 20000 - 10000;
    offsets.cave = rand() % 20000 - 10000;
    offsets.temperature = rand() % 20000 - 10000;

    this->_noise_map = new NoiseMap();
    this->_block_map = new BlockMap(this->_noise_map);
}

Model::~Model(void)
{
    delete this->_block_map;
    delete this->_noise_map;
}

NoiseMap *Model::getNoiseMap(void)
{
    return this->_noise_map;
}

BlockMap *Model::getBlockMap(void)
{
    return this->_block_map;
}

void Model::updateUp(void)
{
    this->_noise_map->updateUp();
    this->_block_map->updateUp(this->_noise_map);
}

void Model::updateDown(void)
{
    this->_noise_map->updateDown();
    this->_block_map->updateDown(this->_noise_map);
}

void Model::updateLeft(void)
{
    this->_noise_map->updateLeft();
    this->_block_map->updateLeft(this->_noise_map);
}

void Model::updateRight(void)
{
    this->_noise_map->updateRight();
    this->_block_map->updateRight(this->_noise_map);
}