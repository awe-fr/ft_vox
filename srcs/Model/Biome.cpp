#include <Model/Biome.hpp>

BlockLayer::BlockLayer(size_t min_height, size_t max_height, Block block, Block top_block) : min_height(min_height), max_height(max_height), block(block), top_block(top_block) {}

BlockLayer::~BlockLayer(void) {}

Biome::Biome(std::string name, size_t min_height, size_t max_height, float (*topology_curve)(float noise)) : name(name), min_height(min_height), max_height(max_height), topology_curve(topology_curve) {}

Biome::~Biome(void) {}

std::vector<BlockLayer> Biome::getBlockLayers(void)
{
    return this->_layers;
}

Plain::Plain(void) : Biome("plain", 42, 54, plain_curve)
{
    this->_layers.push_back(BlockLayer(1, 38, Stone(), Stone()));
    this->_layers.push_back(BlockLayer(39, 54, Dirt(), Grass()));
}

Mountain::Mountain(void) : Biome("mountain", 48, 100, mountain_curve)
{
    this->_layers.push_back(BlockLayer(1, 45, Stone(), Stone()));
    this->_layers.push_back(BlockLayer(46, 60, Dirt(), Grass()));
    this->_layers.push_back(BlockLayer(61, 90, Stone(), Stone()));
    this->_layers.push_back(BlockLayer(91, 100, SnowyGrass(), SnowyGrass()));
}

Desert::Desert(void) : Biome("desert", 42, 54, desert_curve)
{
    this->_layers.push_back(BlockLayer(1, 38, Stone(), Stone()));
    this->_layers.push_back(BlockLayer(39, 54, Sand(), Sand()));
}

float plain_curve(float noise)
{
    return noise;
}

float mountain_curve(float noise)
{
    if (noise >= 0)
        return noise * noise * noise;
    return noise;
}

float desert_curve(float noise)
{
    return noise;
}