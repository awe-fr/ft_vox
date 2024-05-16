#include <Model/NoiseMapChunk.hpp>

NoiseMapChunk::NoiseMapChunk(int x, int y) : _coord{x, y}, _is_generated(false)
{
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
			float noise = octaves(x_e, y_e, 0.5f, 2.f, 0.8f, 1.f / EROSION_SCALE, 2);
			float e = erosion(noise);

			// Continentalness
			noise = octaves(x_c, y_c, 0.55f, 2.2f, 0.7f, 1.f / CONTINENTAL_SCALE, 5);
			float c = continentalness(noise);

			// Peaks and valleys
			noise = octaves(x_pv, y_pv, 0.5f, 2.f, 1.f, 1.f / PEAKS_VALLEYS_SCALE, 4);
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

float continentalness(float noise)
{
	float c_noise = noise + 1.f;

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