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

void Controller::pass_input_to_model()
{
	this->model_->take_new_input(this->get_input_char());
}

bool Controller::is_valid_input()
{
	return true;
}

char Controller::get_input_char()
{
	return this->input_char_;
}


bool Controller::is_in_alphabet()
{
	return ('a' <= this->get_input_char() && this->get_input_char() <= 'z' ||
		'A' <= this->get_input_char() && this->get_input_char() <= 'Z');
}
bool Controller::is_ciph()
{
	return ('0' <= this->get_input_char() && this->get_input_char() <= '9');
}

bool Controller::is_symbol()
{
	char c = this->get_input_char();
	for (unsigned int i = 0; i < symbols.size(); i++)
	{
		if (c == symbols[i])
			return true;
	}
	return false;
}