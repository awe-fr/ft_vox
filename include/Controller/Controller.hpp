#pragma once

#include <Model/Model.hpp>
#include <View/View.hpp>

class Controller
{
    public:
        Controller(void);
        ~Controller(void);

    private:
        Model   *_model;
        View    *_view;

};