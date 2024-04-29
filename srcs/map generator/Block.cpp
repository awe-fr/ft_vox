#include "Block.hpp"

Block::Block(const std::string name, const std::array<float, 4> texture_top, const std::array<float, 4> texture_bottom, const std::array<float, 4> texture_side) : name(name),
    _texture_top(texture_top), _texture_bottom(texture_bottom), _texture_side(texture_side) {}

Block::~Block(void) {}

const std::array<float, 4> Block::getTextureTop(void)
{
    return this->_texture_top;
}

const std::array<float, 4> Block::getTextureBottom(void)
{
    return this->_texture_bottom;
}

const std::array<float, 4> Block::getTextureSide(void)
{
    return this->_texture_side;
}



Void::Void(void) : Block("void", {}, {}, {}) {}

Grass::Grass(void) : Block("grass", {1.f, 0.75f, 50.f, 0.75f}, {1.f, 0.75f, 0.f, 0.25f}, {1.f, 0.75f, 25.f, 0.50f}) {}

Dirt::Dirt(void) : Block("dirt", {1.f, 0.75f, 0.f, 0.25f}, {1.f, 0.75f, 0.f, 0.25f}, {1.f, 0.75f, 0.f, 0.25f}) {}

Stone::Stone(void) : Block("stone", {1.f, 0.75f, 0.75f, 1.f}, {1.f, 0.75f, 0.75f, 1.f}, {1.f, 0.75f, 0.75f, 1.f}) {}

Sand::Sand(void) : Block("sand", {0.75f, 0.5f, 0.f, 0.25f}, {0.75f, 0.5f, 0.f, 0.25f}, {0.75f, 0.5f, 0.25f, 0.5f}) {}

SnowyGrass::SnowyGrass(void) : Block("snowy grass", {0.75f, 0.5f, 0.5f, 0.75f}, {1.f, 0.75f, 0.f, 0.25f}, {0.75f, 0.5f, 0.25f, 0.5f}) {}