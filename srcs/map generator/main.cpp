#include "Map.hpp"
#include <iostream>

size_t get_nb_chunk(size_t length, size_t block_size)
{
    return (length / block_size) / Chunk::SIZE;
}

unsigned long	rgba_to_long(int r, int g, int b, int a)
{
	return (((r & 0xff) << 24) + ((g & 0xff) << 16)
		+ ((b & 0xff) << 8) + (a & 0xff));
}

size_t get_block_size(size_t max_width, size_t max_height)
{
    if (max_height <= max_width)
        return max_height / ((Map::RENDER_DISTANCE * 2 + 1) * Chunk::SIZE);
    return max_width / ((Map::RENDER_DISTANCE * 2 + 1) * Chunk::SIZE);
}

int main(void)
{
    size_t max_width = 2560;
    size_t max_height = 1300;
    size_t block_size = get_block_size(max_width, max_height);
    size_t width = block_size * ((Map::RENDER_DISTANCE * 2 + 1) * Chunk::SIZE);
    size_t height = block_size * ((Map::RENDER_DISTANCE * 2 + 1) * Chunk::SIZE);

    Biome biome = Plain();
    Map map(biome);

    mlx_t *mlx = mlx_init(width, height, "map", false);
	if (!mlx)
		exit(EXIT_FAILURE);
	mlx_image_t *img = mlx_new_image(mlx, width, height);
	if (!img)
		exit(EXIT_FAILURE);

    for (size_t i = 0; i < (Map::RENDER_DISTANCE * 2 + 1) * Chunk::SIZE * block_size; i++)
    {
        size_t chunk_y = i / (Chunk::SIZE * block_size);
        size_t chunk_val_y = (i / block_size) % Chunk::SIZE;
        for (size_t j = 0; j < width; j++)
        {
            size_t chunk_x = j / (Chunk::SIZE * block_size);
            size_t chunk_val_x = (j / block_size) % Chunk::SIZE;

            unsigned char h = map.getChunk(chunk_x, chunk_y)->getValue(chunk_val_x, chunk_val_y);
            unsigned color;
            if (h < 42)
                color = rgba_to_long(0, 127, 255, (int)(((float)h / 42.f) * 255.f));
            else if (h < 60)
                color = rgba_to_long(0, 216, 58, (int)(((float)h / 60.f) * 255.f));
            else if (h < 90)
                color = rgba_to_long(206, 206, 206, (int)(((float)h / 90.f) * 255.f));
            else
                color = rgba_to_long(255, 255, 255, (int)(((float)h / 255.f) * 255.f));
            mlx_put_pixel(img, j, i, color);
        }
    }

	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		exit(EXIT_FAILURE);

	mlx_loop(mlx);
}