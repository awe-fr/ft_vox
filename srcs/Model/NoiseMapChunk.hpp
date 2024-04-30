#pragma once
#include <stddef.h>
#include <exception>
#include <math.h>
#include <iostream>
#include <vector>

#include <MLX42/MLX42.h>
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

		const static size_t	SIZE = 16;
		const static size_t	MAX_HEIGHT = 256;
		const static size_t SEA_LEVEL = 42;
		constexpr static float SCALE = 2.f;

		void					Generate(void);
		unsigned char			getValue(size_t x, size_t y);
		int						getCoordX(void);
		int						getCoordY(void);
		std::vector<BlockLayer>	getBlockLayers(void);

	private:
		unsigned char	_map[SIZE][SIZE];
		const int		_coord[2];
		bool			_is_generated;
		Biome			_biome;
};

float	SimplexNoise(float x, float y);
