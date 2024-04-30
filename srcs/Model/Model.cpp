#include <Model/Model.hpp>

Model::Model(void)
{
    this->_noise_map = new NoiseMap(Plain());
    this->_block_map = new BlockMap(*this->_noise_map);
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