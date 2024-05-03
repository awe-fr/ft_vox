#pragma once

#include <Model/Model.hpp>
#include <View/View.hpp>

class Controller
{
    public:
        Controller(void);
        ~Controller(void);

        void loop(void);
        void updateMap(std::array<int, 2> prev_pos, std::array<int, 2> new_pos);

    private:
        Model   *_model;
        View    *_view;

};