#include "MapGenerator.hpp"
#include <iostream>

size_t get_nb_chunk(size_t length, size_t block_size)
{
    return (length / block_size) / Chunck::SIZE;
}

unsigned long	rgba_to_long(int r, int g, int b, int a)
{
	return (((r & 0xff) << 24) + ((g & 0xff) << 16)
		+ ((b & 0xff) << 8) + (a & 0xff));
}

int main(void)
{
    // Chunck test_10(-1, 0);
    // Chunck test_11(-1, 1);
    // Chunck test00(0, 0);
    // Chunck test01(0, 1);
    // Chunck test10(1, 0);
    // Chunck test11(1, 1);

    // for (size_t i = 0; i < Chunck::SIZE; i++)
    // {
    //     for (size_t j = 0; j < Chunck::SIZE; j++)
    //         std::cout << (int)test_10.getValue(j, i) << " ";
    //     for (size_t j = 0; j < Chunck::SIZE; j++)
    //         std::cout << (int)test00.getValue(j, i) << " ";
    //     for (size_t j = 0; j < Chunck::SIZE; j++)
    //         std::cout << (int)test10.getValue(j, i) << " ";
    //     std::cout << std::endl;
    // }
    // for (size_t i = 0; i < Chunck::SIZE; i++)
    // {
    //     for (size_t j = 0; j < Chunck::SIZE; j++)
    //         std::cout << (int)test_11.getValue(j, i) << " ";
    //     for (size_t j = 0; j < Chunck::SIZE; j++)
    //         std::cout << (int)test01.getValue(j, i) << " ";
    //     for (size_t j = 0; j < Chunck::SIZE; j++)
    //         std::cout << (int)test11.getValue(j, i) << " ";
    //     std::cout << std::endl;
    // }
    size_t block_size = 5;
    size_t height = 994;
    size_t width = 1920;
    int start_x = 0;
    int start_y = 0;

    size_t nb_chunk_x = get_nb_chunk(width, block_size);
    size_t nb_chunk_y = get_nb_chunk(height, block_size);

    Chunck *map[nb_chunk_y][nb_chunk_x];
    for (size_t i = start_y; i < nb_chunk_y; i++)
    {
        for (size_t j = start_x; j < nb_chunk_x; j++)
            map[i][j] = new Chunck(j, i);
    }

    (void)map;

    mlx_t *mlx = mlx_init(width, height, "map", false);
	if (!mlx)
		exit(EXIT_FAILURE);
	mlx_image_t *img = mlx_new_image(mlx, width, height);
	if (!img)
		exit(EXIT_FAILURE);

    for (size_t i = 0; i < nb_chunk_y * Chunck::SIZE * block_size; i++)
    {
        size_t chunk_y = i / (Chunck::SIZE * block_size);
        size_t chunk_val_y = (i / block_size) % Chunck::SIZE;
        for (size_t j = 0; j < width; j++)
        {
            size_t chunk_x = j / (Chunck::SIZE * block_size);
            size_t chunk_val_x = (j / block_size) % Chunck::SIZE;

            unsigned char h = map[chunk_y][chunk_x]->getValue(chunk_val_x, chunk_val_y);
            unsigned color;
            if (h < Chunck::SEA_LEVEL)
                color = rgba_to_long(0, 127, 255, (int)(((float)h / (float)Chunck::SEA_LEVEL) * 255.f));
            else if (h < 210)
                color = rgba_to_long(0, 216, 58, (int)(((float)h / 210.f) * 255.f));
            else
                color = rgba_to_long(255, 255, 255, (int)(((float)h / 255.f) * 255.f));
            mlx_put_pixel(img, j, i, color);
        }
    }
    
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		exit(EXIT_FAILURE);

	mlx_loop(mlx);
}