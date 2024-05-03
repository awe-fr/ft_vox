#pragma once

#include "ViewVars.hpp"
#include "ViewChunk.hpp"
#include <Model/BlockMap.hpp>

class ViewMap
{
    public:
        ViewMap(BlockMap *block_map);
        ~ViewMap(void);

        ViewChunk *getChunk(size_t x, size_t y);
        void updateUp(BlockMap *block_map);
        void updateDown(BlockMap *block_map);
        void updateLeft(BlockMap *block_map);
        void updateRight(BlockMap *block_map);

    private:
        ViewChunk   *_map[RENDER_DISTANCE * 2 + 1][RENDER_DISTANCE * 2 + 1];
};