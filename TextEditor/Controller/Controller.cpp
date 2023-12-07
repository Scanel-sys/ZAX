#include "Controller.h"

MyString symbols_{ "~`!@#$%^&*()-_=+[{]}\\|;:'\",<.>/?" };
MyString navigation_one_symbol_commands_{ "^&wbxpg" };
MyString navigation_command_symbols_{ "diwywG" };
MyString regime_change_symbols_{ "iISAr:/?" };
MyString find_one_symbol_commands_{ "nN" };
MyString find_command_symbols_{ "/?" };
MyString command_regime_symbols_{ "oxwq!h" };

const std::vector <int> navigation_keys_ = { KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT };

Controller::Controller(Model* model, NcursesAdapter* adapter){
	this->model_ = model;
	this->adapter_ = adapter;
	this->input_char_ = 0xFF;
}


bool Controller::is_navigation_button()
{
	for (int i = 0; i < navigation_keys_.size(); i++)
	{
		if (this->get_input_char() == navigation_keys_[i])
			return true;
	}
	return false;
}

bool Controller::is_in_navigation_one_symbol_commands()
{
	return navigation_one_symbol_commands_.simple_find(this->get_input_char());
}

bool Controller::is_in_navigation_command_symbols()
{
	return navigation_command_symbols_.simple_find(this->get_input_char());
}


bool Controller::is_in_regime_change_symbols()
{
	return regime_change_symbols_.simple_find(this->get_input_char());
}


bool Controller::is_in_find_one_symbol_commands()
{
	return find_one_symbol_commands_.simple_find(this->get_input_char());
}

bool Controller::is_in_find_command_symbols()
{
	return find_command_symbols_.simple_find(this->get_input_char());
}


bool Controller::is_text()
{
	return this->is_ciph() || this->is_in_alphabet() || this->is_symbol();
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
	return symbols_.simple_find(this->get_input_char());
}


bool Controller::is_valid_navigation_input()
{
	return this->is_in_regime_change_symbols() || this->is_navigation_button()
		|| this->is_in_navigation_one_symbol_commands()
		|| this->is_in_navigation_command_symbols() || this->is_ciph();
}

bool Controller::is_valid_find_input()
{
	return this->is_text() || this->is_navigation_button();
}

bool Controller::is_valid_write_input()
{
	return this->is_text() || this->is_navigation_button();
}

bool Controller::is_valid_command_input()
{
	return this->is_text();
}


void Controller::handle_navigation()
{
	if (this->is_in_regime_change_symbols())
	{
		this->pass_input_to_model();
		this->model_->change_regime();
	}
	else if (this->is_navigation_button())
	{
		this->handle_cursor_moving_keys();
	}
	else if (this->is_in_navigation_one_symbol_commands())
	{
		this->pass_input_to_model();
		this->model_->handle_navigation_one_symbol_command();
	}
	else if (this->is_in_navigation_command_symbols() || this->is_ciph())
	{
		this->pass_input_to_model();
		this->model_->handle_text_input();
	}
}

void Controller::handle_other_regimes()
{
	if (this->is_navigation_button())
	{
		this->handle_cursor_moving_keys();
	}
	else
	{
		this->pass_input_to_model();
		this->model_->handle_text_input();
	}
}

void Controller::handle_cursor_moving_keys()
{
	switch (this->get_input_char())
	{
	case KEY_DOWN_W:
		this->model_->move_cursor(DOWN);
		break;
	case KEY_UP_W:
		this->model_->move_cursor(UP);
		break;
	case KEY_LEFT_W:
		this->model_->move_cursor(LEFT);
		break;
	case KEY_RIGHT_W:
		this->model_->move_cursor(RIGHT);
		break;
	case PAGE_UP_W:
		this->model_->move_cursor(PAGE_UP);
		break;
	case PAGE_DOWN_W:
		this->model_->move_cursor(PAGE_DOWN);
		break;
	default:
		return;
	}
}

// public

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
	return this->is_text() || this->is_in_navigation_command_symbols() || this->is_valid_navigation_input();
}

void Controller::handle_input()
{
	enum Regime actual_regime = this->model_->get_regime();
	switch (actual_regime)
	{
	case NAVIGATION:
		if (this->is_valid_navigation_input())
			this->handle_navigation();
		break;

	case WRITE:
		if (this->is_valid_write_input())
			this->handle_other_regimes();
		break;

	case COMMAND:
		if (this->is_valid_command_input())
			this->handle_other_regimes();
		break;

	case FIND:
		if (is_valid_find_input())
			this->handle_other_regimes();
		break;
	}
}

char Controller::get_input_char()
{
	return this->input_char_;
}