#include "MapGenerator.hpp"
#include <iostream>

int main(void)
{
    Chunck test(0, 0);
    for (size_t i = 0; i < Chunck::SIZE; i++)
    {
        for (size_t j = 0; j < Chunck::SIZE; j++)
            std::cout << (int)test.getValue(j, i) << " ";
        std::cout << std::endl;
    }
    Chunck test1(0, 1);
    for (size_t i = 0; i < Chunck::SIZE; i++)
    {
        for (size_t j = 0; j < Chunck::SIZE; j++)
            std::cout << (int)test1.getValue(j, i) << " ";
        std::cout << std::endl;
    }
}