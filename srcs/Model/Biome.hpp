#pragma once
#include <stddef.h>
#include <string>
#include <vector>

#include "Block.hpp"

class BlockLayer
{
    public:
        BlockLayer(size_t min_height, size_t max_height, Block block, Block top_block);
        ~BlockLayer(void);

        const size_t    min_height;
        const size_t    max_height;
        const Block     block;
        const Block     top_block;
};

class Biome
{
	public:
        ~Biome(void);

        const std::string   name;
		const size_t        min_height;
		const size_t        max_height;
        float               (*topology_curve)(float noise);

        std::vector<BlockLayer> getBlockLayers(void);
    
    protected:
        Biome(std::string name, size_t min_height, size_t max_height, float (*topology_curve)(float noise));

        std::vector<BlockLayer> _layers;
};

class Plain : public Biome
{
    public:
        Plain(void);
};

class Mountain : public Biome
{
    public:
        Mountain(void);
};

class Desert : public Biome
{
    public:
        Desert(void);
};

float plain_curve(float noise);
float mountain_curve(float noise);
float desert_curve(float noise);