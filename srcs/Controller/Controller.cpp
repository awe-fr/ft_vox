#include "Controller.hpp"

Controller::Controller(void)
{
    this->_model = new Model();
}

Controller::~Controller(void)
{
    delete this->_model;
}