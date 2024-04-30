#pragma once

#include "ModelVars.hpp"
#include "NoiseMap.hpp"
#include "BlockMap.hpp"

class Model
{
    public:
        Model(void);
        ~Model(void);

        NoiseMap *getNoiseMap(void);

    private:
        NoiseMap *_noise_map;
        BlockMap *_block_map;
};