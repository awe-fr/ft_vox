#include <Controller/Controller.hpp>

Controller::Controller(void)
{
    this->_model = new Model();
    this->_view = new View(this->_model->getBlockMap());
}

Controller::~Controller(void)
{
    delete this->_view;
    delete this->_model;
}