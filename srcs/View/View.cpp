#include <View/View.hpp>

View::View(BlockMap *block_map)
{
    this->_map = new ViewMap(block_map);
}

View::~View(void)
{
    delete this->_map;
}