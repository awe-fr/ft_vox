#pragma once
#include <string>
#include <array>

class Block
{
    public:
        Block(void);
        ~Block(void);
        
        Block &operator=(const Block &block);

        const std::string getName(void);
        const std::array<float, 4> getTextureTop(void);
        const std::array<float, 4> getTextureBottom(void);
        const std::array<float, 4> getTextureSide(void);

    protected:
        Block(const std::string name, const std::array<float, 4> texture_top, const std::array<float, 4> texture_bottom, const std::array<float, 4> texture_side);

        std::string             _name;
        std::array<float, 4>    _texture_top;
        std::array<float, 4>    _texture_bottom;
        std::array<float, 4>    _texture_side;
};

class Void : public Block
{
    public:
        Void(void);
};

class Grass : public Block
{
    public:
        Grass(void);
};

class Dirt : public Block
{
    public:
        Dirt(void);
};

class Stone : public Block
{
    public:
        Stone(void);
};

class Sand : public Block
{
    public:
        Sand(void);
};

class SnowyGrass : public Block
{
    public:
        SnowyGrass(void);
};