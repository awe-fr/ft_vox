#include "Biome.hpp"

Biome::Biome(std::string name, size_t min_height, size_t max_height, float (*topology_curve)(float noise)) : name(name), min_height(min_height), max_height(max_height), topology_curve(topology_curve) {}

Biome::~Biome(void) {}

Plain::Plain(void) : Biome("plain", 42, 54, plain_curve) {}

Mountain::Mountain(void) : Biome("mountain", 48, 92, mountain_curve) {}

Desert::Desert(void) : Biome("desert", 42, 54, desert_curve) {}

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