#pragma once

#include "../Model/Model.hpp"

class Controller
{
    public:
        Controller(void);
        ~Controller(void);

    private:
        Model *_model;

};