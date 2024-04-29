#pragma once

#include <stddef.h>
#include <string>

class Biome
{
	public:
        ~Biome(void);

        const std::string name;
		const size_t min_height;
		const size_t max_height;
        float (*topology_curve)(float noise);

        const static size_t SEA_LEVEL = 42;
    
    protected:
        Biome(std::string name, size_t min_height, size_t max_height, float (*topology_curve)(float noise));
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