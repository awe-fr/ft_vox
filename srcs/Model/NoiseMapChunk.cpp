#include <Model/NoiseMapChunk.hpp>

NoiseMapChunk::NoiseMapChunk(int x, int y, Biome biome) : _coord{x, y}, _is_generated(false), _biome(biome)
{
	// this->Generate();

	// int start_y = y * CHUNK_SIZE;
	// size_t map_y = 0;
	// for (int i = start_y; i < start_y + 16; i++)
	// {
	// 	size_t map_x = 0;
	// 	int start_x = x * CHUNK_SIZE;
	// 	for (int j = start_x; j < start_x + 16; j++)
	// 	{
	// 		float amplitude = 20.f;
	// 		float frequency = 1.f / 3.f;
	// 		float persistance = 0.5f;
	// 		float lacunarity = 2.f;
	// 		float noise = 0.f;
	// 		size_t nb_octave = 4;

	// 		for (size_t k = 0; k < nb_octave; k++)
	// 		{
	// 			noise += amplitude * SimplexNoise(j * frequency, i * frequency);
	// 			amplitude *= persistance;
	// 			frequency *= lacunarity;
	// 		}

	// 		unsigned char level = BASE_LEVEL + noise * amplitude;

	// 		this->_map[map_y][map_x] = level;
	// 		map_x++;
	// 	}
	// 	map_y++;
	// }

	for (size_t i = 0; i < CHUNK_SIZE; i++)
	{
		float y_c = (float)this->_coord[1] / CONTINENTAL_SCALE + ((float)i / (float)CHUNK_SIZE) / CONTINENTAL_SCALE;
		float y_e = (float)this->_coord[1] / EROSION_SCALE + ((float)i / (float)CHUNK_SIZE) / EROSION_SCALE;
		float y_pv = (float)this->_coord[1] / PEAKS_VALLEYS_SCALE + ((float)i / (float)CHUNK_SIZE) / PEAKS_VALLEYS_SCALE;
		for (size_t j = 0; j < CHUNK_SIZE; j++)
		{
			float x_c = (float)this->_coord[0] / CONTINENTAL_SCALE + ((float)j / (float)CHUNK_SIZE) / CONTINENTAL_SCALE;
			float x_e = (float)this->_coord[0] / EROSION_SCALE + ((float)j / (float)CHUNK_SIZE) / EROSION_SCALE;
			float x_pv = (float)this->_coord[0] / PEAKS_VALLEYS_SCALE + ((float)j / (float)CHUNK_SIZE) / PEAKS_VALLEYS_SCALE;

			// Erosion
			float persistence = 0.5f;
			float lacunarity = 2.f;
			float amplitude = 0.8f;
			float frequency = 1.f / EROSION_SCALE;
			float noise = 0.f;
			for (size_t k = 0; k < 2; k++)
			{
				noise += amplitude * SimplexNoise(x_e * frequency, y_e * frequency);
				amplitude *= persistence;
				frequency *= lacunarity;
			}
			float e = erosion(noise);

			// Continentalness
			persistence = 0.55f;
			lacunarity = 2.2f;
			amplitude = 0.7f;
			frequency = 1.f / CONTINENTAL_SCALE;
			noise = 0.f;
			for (size_t k = 0; k < 5; k++)
			{
				noise += amplitude * SimplexNoise(x_c * frequency, y_c * frequency);
				amplitude *= persistence;
				frequency *= lacunarity;
			}
			float c = continentalness(noise);

			// Peaks and valleys
			persistence = 0.5f;
			lacunarity = 2.f;
			amplitude = 1.f;
			frequency = 1.f / PEAKS_VALLEYS_SCALE;
			noise = 0.f;
			for (size_t k = 0; k < 4; k++)
			{
				noise += amplitude * SimplexNoise(x_pv * frequency, y_pv * frequency);
				amplitude *= persistence;
				frequency *= lacunarity;
			}
			float pv = peaks_valleys(noise);

			float e_weight = 1.8f;
			float c_weight = 2.5f;
			float pv_weight = 1.f;

			float avg = (e * e_weight + c * c_weight + pv * pv_weight) / (e_weight + c_weight + pv_weight);

			unsigned char level = (unsigned char)10 + (unsigned char)(150.f * avg);

			this->_map[i][j] = (unsigned char)level;
		}
	}

	this->_is_generated = true;
}

NoiseMapChunk::~NoiseMapChunk(void) {}

const char *NoiseMapChunk::NotGeneratedException::what() const throw()
{
	return "Chunk not generated";
}

const char *NoiseMapChunk::OutOfBoundsException::what() const throw()
{
	return "Value out of bounds";
}

void NoiseMapChunk::Generate(void)
{
	if (this->_is_generated)
		return;

	float biome_half = (float)(this->_biome.max_height - this->_biome.min_height) / 2.f;
	float biome_avg = (float)this->_biome.min_height + biome_half;
	
	for (size_t i = 0; i < CHUNK_SIZE; i++)
	{
		float y = (float)this->_coord[1] / CONTINENTAL_SCALE + ((float)i / (float)CHUNK_SIZE) / CONTINENTAL_SCALE;
		for (size_t j = 0; j < CHUNK_SIZE; j++)
		{
			float x = (float)this->_coord[0] / CONTINENTAL_SCALE + ((float)j / (float)CHUNK_SIZE) / CONTINENTAL_SCALE;
			float persistence = 0.5f;
			float lacunarity = 2.f;
			float amplitude = 1.f;
			float frequency = 1.f / CONTINENTAL_SCALE;
			float noise = 0.f;
			for (size_t k = 0; k < 3; k++)
			{
				noise += amplitude * SimplexNoise(x * frequency, y * frequency);
				amplitude *= persistence;
				frequency *= lacunarity;
			}
			// float noise = SimplexNoise(x, y);
			this->_map[i][j] = (unsigned char)(biome_avg + (biome_half * this->_biome.topology_curve(noise)));
		}
	}

	this->_is_generated = true;
}

unsigned char NoiseMapChunk::getValue(size_t x, size_t y)
{
	if (!this->_is_generated)
		throw NoiseMapChunk::NotGeneratedException();

	if (x >= CHUNK_SIZE || y >= CHUNK_SIZE)
		throw NoiseMapChunk::OutOfBoundsException();

	return this->_map[y][x];
}

int NoiseMapChunk::getCoordX(void)
{
	return this->_coord[0];
}

int NoiseMapChunk::getCoordY(void)
{
	return this->_coord[1];
}

std::vector<BlockLayer> NoiseMapChunk::getBlockLayers(void)
{
	return this->_biome.getBlockLayers();
}

float continentalness(float noise)
{
	float c_noise = noise + 1.f;
	// if (c_noise <= 0.5f)
	// {
	// 	float a = c_noise / 0.5f;
	// 	unsigned char c = (unsigned char)(30 + a * 25.f);
	// 	return c;
	// }
	// if (c_noise <= 1.4f)
	// {
	// 	float a = (c_noise - 0.5f) / 1.f;
	// 	unsigned char c = (unsigned char)(56.f + a * 14.f);
	// 	return c;
	// }
	// if (c_noise <= 1.8f)
	// {
	// 	float a = (c_noise - 1.4f) / 0.4f;
	// 	unsigned char c = (unsigned char)(70.f + a * 58.f);
	// 	return c;
	// }
	// float a = (c_noise - 1.8f) / 0.2f;
	// unsigned char c = (unsigned char)(128.f + a * 3.f);
	// return c;

	// if (c_noise <= 0.1f)
	// {
	// 	float a = c_noise / 0.1f;
	// 	float c = 1.f - a * 0.95f;
	// 	return c;
	// }
	if (c_noise <= 0.5)
	{
		float c = 0.05f;
		return c;
	}
	if (c_noise <= 0.6)
	{
		float a = (c_noise - 0.5f) / 0.1f;
		float c = 0.05f + a * 0.2f;
		return c;
	}
	if (c_noise <= 0.75)
	{
		float c = 0.25f;
		return c;
	}
	if (c_noise <= 0.85)
	{
		float a = (c_noise - 0.75f) / 0.1f;
		float c = 0.25f + a * 0.2f;
		return c;
	}
	if (c_noise <= 1.2)
	{
		float a = (c_noise - 0.85f) / 0.35f;
		float c = 0.45f + a * 0.3f;
		return c;
	}
	if (c_noise <= 1.4)
	{
		float a = (c_noise - 1.2f) / 0.2f;
		float c = 0.75f + a * 0.05f;
		return c;
	}
	if (c_noise <= 1.7)
	{
		float a = (c_noise - 1.4f) / 0.3f;
		float c = 0.80f + a * 0.15f;
		return c;
	}
	float c = 0.95f;
	return c;
}

float erosion(float noise)
{
	// float e_noise = noise + 1.f;
	// int e;
	// if (e_noise <= 1.f)
	// {
	// 	float a = e_noise / 1.f;
	// 	e = (int)(a * 20.f);
	// }
	// else if (e_noise <= 1.65f)
	// {
	// 	float a = (e_noise - 1.f) / 0.65f;
	// 	e = (int)(20.f + a * 4.f);
	// }
	// else if (e_noise <= 1.7f)
	// {
	// 	float a = (e_noise - 1.65f) / 0.05f;
	// 	e = (int)(24.f - a * 8.f);
	// }
	// else if (e_noise <= 1.8f)
	// 	e = (int)8;
	// else if (e_noise <= 1.85f)
	// {
	// 	float a = (e_noise - 1.8f) / 0.05f;
	// 	e = (int)(16.f + a * 8.f);
	// }
	// else
	// {
	// 	float a = (e_noise - 1.85f) / 0.15;
	// 	e = (int)(24.f + a * 4.f);
	// }
	// if (e <= 14)
	// 	return (float)e / 14.f;

	// e -= 14;
	// return -(float)e / 14.f;

	float e_noise = noise + 1.f;
	if (e_noise <= 0.22f)
	{
		float a = e_noise / 0.15f;
		float e = 1.f - a * 0.3f;
		return e;
	}
	if (e_noise <= 0.6f)
	{
		float a = (e_noise - 0.22f) / 0.38f;
		float e = 0.7f - a * 0.2f;
		return e;
	}
	if (e_noise <= 0.7f)
	{
		float a = (e_noise - 0.6f) / 0.1f;
		float e = 0.5f + a * 0.1f;
		return e;
	}
	if (e_noise <= 1.f)
	{
		float a = (e_noise - 0.7f) / 0.3f;
		float e = 0.6f - a * 0.4f;
		return e;
	}
	if (e_noise <= 1.5f)
	{
		float a = (e_noise - 1.f) / 0.5f;
		float e = 0.2f - a * 0.05f;
		return e;
	}
	if (e_noise <= 1.65f)
	{
		float a = (e_noise - 1.5f) / 0.15f;
		float e = 0.15f + a * 0.1f;
		return e;
	}
	if (e_noise <= 1.8f)
	{
		float e = 0.25f;
		return e;
	}
	if (e_noise <= 1.95f)
	{
		float a = (e_noise - 1.8f) / 0.15f;
		float e = 0.25f - a * 0.1f;
		return e;
	}
	float a = (e_noise - 1.95f) / 0.05f;
	float e = 0.15f - a * 0.05f;
	return e;
}

float peaks_valleys(float noise)
{
	float pv_noise = noise + 1.f;
	if (pv_noise <= 0.2f)
	{
		float a = pv_noise / 0.2f;
		float pv = a * 0.1f;
		return pv;
	}
	if (pv_noise <= 0.4f)
	{
		float a = (pv_noise - 0.2f) / 0.2f;
		float pv = 0.1f + a * 0.08f;
		return pv;
	}
	if (pv_noise <= 0.6f)
	{
		float a = (pv_noise - 0.4f) / 0.2f;
		float pv = 0.18f + a * 0.04f;
		return pv;
	}
	if (pv_noise <= 0.9f)
	{
		float a = (pv_noise - 0.6f) / 0.3f;
		float pv = 0.22f + a * 0.06f;
		return pv;
	}
	if (pv_noise <= 1.4f)
	{
		float a = (pv_noise - 0.9f) / 0.5f;
		float pv = 0.28f + a * 0.52f;
		return pv;
	}
	if (pv_noise <= 1.5f)
	{
		float a = (pv_noise - 1.4f) / 0.1f;
		float pv = 0.80f + a * 0.15f;
		return pv;
	}
	if (pv_noise <= 1.75f)
	{
		float a = (pv_noise - 1.5f) / 0.25f;
		float pv = 0.95f - a * 0.1f;
		return pv;
	}
	float pv = 0.85f;
	return pv;
}




// Simplex noise

static int fastfloor(float x)
{
	return x > 0 ? (int)x : (int)x - 1;
}

static float dot(const int g[], float x, float y)
{
	return g[0] * x + g[1] * y;
}

float	SimplexNoise(float x, float y)
{
	const int grad3[12][3] = {
		{1,1,0},{-1,1,0},{1,-1,0},{-1,-1,0},
		{1,0,1},{-1,0,1},{1,0,-1},{-1,0,-1},
		{0,1,1},{0,-1,1},{0,1,-1},{0,-1,-1}
	};

	const int p[] = {151,160,137,91,90,15,  131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,  190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,  88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,  77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,  102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,  135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,  5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,  223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,  129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,  251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,  49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,  138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};

	// To remove the need for index wrapping, double the permutation table length
	int perm[512];
	for(int i = 0; i < 512; i++)
		perm[i]= p[i & 255];

	float n0, n1, n2; // Noise contributions from the three corners
	// Skew the input space to determine which simplex cell we're in
	float F2 = 0.5 * (sqrt(3.0) - 1.0);
	float s = (x + y) * F2; // Hairy factor for 2D
	int i = fastfloor(x + s);
	int j = fastfloor(y + s);
	
	float G2 = (3.0 - sqrt(3.0)) / 6.0;
	float t = (i + j) * G2;
	float X0 = i - t; // Unskew the cell origin back to (x,y) space
	float Y0 = j - t;
	float x0 = x - X0; // The x,y distances from the cell origin
	float y0 = y - Y0;
	
	// For the 2D case, the simplex shape is an equilateral triangle.
	// Determine which simplex we are in.
	int i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
	if(x0 > y0)
	{
		// lower triangle, XY order: (0,0)->(1,0)->(1,1)
		i1 = 1;
		j1 = 0;
	}
	else
	{
		// upper triangle, YX order: (0,0)->(0,1)->(1,1)
		i1 = 0;
		j1 = 1;
	}

	// A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
	// a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
	// c = (3-sqrt(3))/6
	
	float x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
	float y1 = y0 - j1 + G2;
	float x2 = x0 - 1.0 + 2.0 * G2; // Offsets for last corner in (x,y) unskewed coords
	float y2 = y0 - 1.0 + 2.0 * G2;
	
	// Work out the hashed gradient indices of the three simplex corners
	int ii = i & 255;
	int jj = j & 255;
	int gi0 = perm[ii+perm[jj]] % 12;
	int gi1 = perm[ii+i1+perm[jj+j1]] % 12;
	int gi2 = perm[ii+1+perm[jj+1]] % 12;
	
	// Calculate the contribution from the three corners
	float t0 = 0.5 - x0*x0-y0*y0;
	if (t0 < 0)
		n0 = 0.0;
	else
	{
		t0 *= t0;
		n0 = t0 * t0 * dot(grad3[gi0], x0, y0);  // (x,y) of grad3 used for 2D gradient
	}
	float t1 = 0.5 - x1*x1-y1*y1;
	if (t1 < 0) n1 = 0.0;
	else
	{
		t1 *= t1;
		n1 = t1 * t1 * dot(grad3[gi1], x1, y1);
	}
    float t2 = 0.5 - x2 * x2 - y2 * y2;
	if(t2 < 0) n2 = 0.0;
	else
	{
		t2 *= t2;
		n2 = t2 * t2 * dot(grad3[gi2], x2, y2);
	}
	
	// Add contributions from each corner to get the final noise value.
	// The result is Chunk::CONTINENTAL_SCALEd to return values in the interval [-1,1].
	
	return 70.0 * (n0 + n1 + n2);
}