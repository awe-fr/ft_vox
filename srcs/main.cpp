#include <Controller/Controller.hpp>
#include <time.h>
#include <sstream>
#include <iostream>

int main(int argc, char **argv)
{
	if (argc > 2)
	{
		std::cout << "ft_vox error: Bad usage" << std::endl;
		std::cout << "./ft_vox [SEED]" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (argc == 2)
	{
		unsigned int seed;
		std::stringstream str_seed(argv[1]);
		str_seed >> seed;
		srand(seed);
	}
	else
		srand(time(NULL));

	Controller controller;
	controller.loop();
}