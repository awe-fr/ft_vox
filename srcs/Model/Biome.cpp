#include <Model/Biome.hpp>

BlockLayer::BlockLayer(size_t min_height, size_t max_height, Block bottom_block, Block subtop_block, Block top_block, size_t subtop_height) : min_height(min_height), max_height(max_height), bottom_block(bottom_block), subtop_block(subtop_block), top_block(top_block), subtop_height(subtop_height) {}

BlockLayer::~BlockLayer(void) {}

Biome::Biome(std::string name, size_t min_height, size_t max_height, float (*topology_curve)(float noise)) : name(name), min_height(min_height), max_height(max_height), topology_curve(topology_curve) {}

Biome::~Biome(void) {}

std::vector<BlockLayer> Biome::getBlockLayers(void)
{
    return this->_layers;
}

Plain::Plain(void) : Biome("plain", 42, 54, plain_curve)
{
    this->_layers.push_back(BlockLayer(1, 38, Stone(), Stone(), Stone(), 0));
    this->_layers.push_back(BlockLayer(39, 54, Stone(), Dirt(), Grass(), 3));
}

Mountain::Mountain(void) : Biome("mountain", 48, 100, mountain_curve)
{
    this->_layers.push_back(BlockLayer(1, 45, Stone(), Stone(), Stone(), 0));
    this->_layers.push_back(BlockLayer(46, 70, Stone(), Dirt(), Grass(), 3));
    this->_layers.push_back(BlockLayer(71, 90, Stone(), Stone(), Stone(), 0));
    this->_layers.push_back(BlockLayer(91, 100, Stone(), Dirt(), SnowyGrass(), 3));
}

Desert::Desert(void) : Biome("desert", 42, 54, desert_curve)
{
    this->_layers.push_back(BlockLayer(1, 38, Stone(), Stone(), Stone(), 0));
    this->_layers.push_back(BlockLayer(39, 54, Stone(), Sand(), Sand(), 3));
}

TestPlain::TestPlain(void) : Biome("test", 1, 255, plain_curve)
{
    this->_layers.push_back(BlockLayer(1, 56, Stone(), Stone(), Stone(), 0));
    this->_layers.push_back(BlockLayer(57, 255, Stone(), Dirt(), Grass(), 4));
}

TestDesert::TestDesert(void) : Biome("test", 1, 255, plain_curve)
{
    this->_layers.push_back(BlockLayer(1, 56, Stone(), Stone(), Stone(), 0));
    this->_layers.push_back(BlockLayer(57, 255, Stone(), Sand(), Sand(), 7));
}

TestSnow::TestSnow(void) : Biome("test", 1, 255, plain_curve)
{
    this->_layers.push_back(BlockLayer(1, 56, Stone(), Stone(), Stone(), 0));
    this->_layers.push_back(BlockLayer(57, 255, Stone(), Dirt(), SnowyGrass(), 4));
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