#pragma once

#include "ViewVars.hpp"
#include "ViewChunk.hpp"
#include <Model/BlockMap.hpp>

class ViewMap
{
    public:
        ViewMap(BlockMap *block_map);
        ~ViewMap(void);

    private:
        ViewChunk   *_map[RENDER_DISTANCE * 2 + 1][RENDER_DISTANCE * 2 + 1];
};