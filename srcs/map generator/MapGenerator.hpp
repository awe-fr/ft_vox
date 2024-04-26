#pragma once
#include <stddef.h>
#include <exception>
#include <math.h>
#include <iostream>

#include <MLX42/MLX42.h>

class Chunck
{
	public:
		Chunck(void);
		Chunck(int x, int y);
		~Chunck(void);

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
		const static size_t SEA_LEVEL = 127;
		constexpr static float SCALE = 5.f;

		void			Generate(void);
		unsigned char	getValue(size_t x, size_t y);

	private:
		unsigned char	_map[SIZE][SIZE];
		const int		_coord[2];
		bool			_is_generated;
};

// class Map
// {
// 	public:
// 		Map(void);
// 		~Map(void);

// 		const static size_t RENDER_DISTANCE = 10;

// 	private:
// 		Chunck _map[RENDER_DISTANCE * 2][RENDER_DISTANCE * 2];
// };

float	SimplexNoise(float x, float y);
