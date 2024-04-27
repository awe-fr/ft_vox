#include "Biome.hpp"

Biome::Biome(size_t min_height, size_t max_height, float (*topology_curve)(float noise)) : min_height(min_height), max_height(max_height), topology_curve(topology_curve) {}

Plain::Plain(void) : Biome(42, 54, mountain_curve) {}

Mountain::Mountain(void) : Biome(48, 92, mountain_curve) {}

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