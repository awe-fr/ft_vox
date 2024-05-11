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
		NoiseMapChunk(int x, int y, Biome biome);
		~NoiseMapChunk(void);

		class NotGeneratedException : public std::exception
		{
			virtual const char *what() const throw();
		};

		class OutOfBoundsException : public std::exception
		{
			virtual const char *what() const throw();
		};

		void					Generate(void);
		unsigned char			getValue(size_t x, size_t y);
		int						getCoordX(void);
		int						getCoordY(void);
		std::vector<BlockLayer>	getBlockLayers(void);

	private:
		unsigned char	_map[CHUNK_SIZE][CHUNK_SIZE];
		const int		_coord[2];
		bool			_is_generated;
		Biome			_biome;
};

float	SimplexNoise(float x, float y);
unsigned char continentalness(float noise);
float erosion(float noise);
