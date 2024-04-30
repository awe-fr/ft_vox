#pragma once

#include "NoiseMap.hpp"
#include "BlockMap.hpp"

class Model
{
    public:
        Model(void);
        ~Model(void);

    private:
        NoiseMap _noise_map;
        BlockMap _block_map;
};