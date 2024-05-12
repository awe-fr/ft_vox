#pragma once
#include <stddef.h>
#include <exception>
#include <math.h>
#include <iostream>
#include <vector>

#include "ModelVars.hpp"
#include "Biome.hpp"

class NoiseMapChunk
{
	public:
		NoiseMapChunk(int x, int y);
		~NoiseMapChunk(void);

		class NotGeneratedException : public std::exception
		{
			virtual const char *what() const throw();
		};

		class OutOfBoundsException : public std::exception
		{
			virtual const char *what() const throw();
		};

		unsigned char			getValue(size_t x, size_t y);
		int						getCoordX(void);
		int						getCoordY(void);

	private:
		unsigned char	_map[CHUNK_SIZE][CHUNK_SIZE];
		const int		_coord[2];
		bool			_is_generated;
};

float	SimplexNoise(float x, float y);
float	octaves(float x, float y, float persistence, float lacunarity, float amplitude, float frequency, size_t nb_octaves);
float 	continentalness(float noise);
float 	erosion(float noise);
float 	peaks_valleys(float noise);
