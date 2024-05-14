#include <Model/Block.hpp>

Block::Block(void) : _name("void"), _texture_top{}, _texture_bottom{}, _texture_side{} {}

Block::Block(const Block &block)
{
    *this = block;
}

Block::Block(const std::string name, const std::array<float, 4> texture_top, const std::array<float, 4> texture_bottom, const std::array<float, 4> texture_side) : _name(name),
    _texture_top(texture_top), _texture_bottom(texture_bottom), _texture_side(texture_side) {}

Block::~Block(void) {}

Block &Block::operator=(const Block &block)
{
    this->_name = block._name;
    this->_texture_top = block._texture_top;
    this->_texture_bottom = block._texture_bottom;
    this->_texture_side = block._texture_side;

    return *this;
}

const std::string Block::getName(void)
{
    return this->_name;
}

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

Grass::Grass(void) : Block("grass", {0.875f, 0.84375, 0.6875f, 0.71875f}, {0.875f, 0.84375, 0.125f, 0.15625f}, {0.875f, 0.84375, 0.40625f, 0.4375f}) {}

Dirt::Dirt(void) : Block("dirt", {0.875f, 0.84375, 0.125f, 0.15625f}, {0.875f, 0.84375, 0.125f, 0.15625f}, {0.875f, 0.84375, 0.125f, 0.15625f}) {}

Stone::Stone(void) : Block("stone", {0.59375f, 0.5625f, 0.125f, 0.15625f}, {0.59375f, 0.5625f, 0.125f, 0.15625f}, {0.59375f, 0.5625f, 0.125f, 0.15625f}) {}

Sand::Sand(void) : Block("sand", {0.59375f, 0.5625f, 0.40625f, 0.4375f}, {0.59375f, 0.5625f, 0.40625f, 0.4375f}, {0.59375f, 0.5625f, 0.40625f, 0.4375f}) {}

SnowyGrass::SnowyGrass(void) : Block("snowy grass", {0.3125f, 0.28125f, 0.125f, 0.15625f}, {0.875f, 0.84375, 0.125f, 0.15625f}, {0.59375f, 0.5625f, 0.6875f, 0.71875f}) {}

Waheur::Waheur(void) : Block("waheur", {0.3125f, 0.28125f, 0.40625f, 0.4375f}, {0.875f, 0.84375, 0.40625f, 0.4375f}, {0.59375f, 0.5625f, 0.40625f, 0.4375f}) {}