#pragma once

#include <stddef.h>
#include <math.h>

float	SimplexNoise(float x, float y);
float	SimplexNoise(float x, float y, float z);
float   octaves(float x, float y, float persistence, float lacunarity, float amplitude, float frequency, size_t nb_octaves);
float   octaves(float x, float y, float z, float persistence, float lacunarity, float amplitude, float frequency, float frequency_z, size_t nb_octaves);