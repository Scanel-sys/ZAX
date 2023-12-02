#include "Controller.h"


Controller::Controller(Model* model, NcursesAdapter* adapter){
	this->model_ = model;
	this->adapter_ = adapter;
	this->input_char_ = 0xFF;
}

void Controller::read_input()
{
	this->input_char_ = this->adapter_->get_input();
}

void Controller::pass_input()
{

}