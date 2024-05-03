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
        BlockMap *getBlockMap(void);

        void updateUp(void);
        void updateDown(void);
        void updateLeft(void);
        void updateRight(void);

    private:
        NoiseMap *_noise_map;
        BlockMap *_block_map;
};