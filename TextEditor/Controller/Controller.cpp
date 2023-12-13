#include "Controller.h"

MyString symbols_{ "~`!@#$%^&*()-_=+[{]}\\|;:'\",<.>/? " };
MyString navigation_one_symbol_commands_{ "^&wbxpg" };
MyString navigation_command_symbols_{ "diwywG" };
MyString regime_change_symbols_{ "iISAr:/?" };
MyString find_one_symbol_commands_{ "nN" };
MyString find_command_symbols_{ "/?" };
MyString command_regime_symbols_{ "oxwq!h" };

const std::vector <int> navigation_keys_ = { KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_NPAGE, KEY_PPAGE };
const std::vector <int> special_keys_ = { K_BACKSPACE, K_ENTER, K_ESCAPE };

// public

Controller::Controller(Model* model, NcursesAdapter* adapter){
	this->model_ = model;
	this->adapter_ = adapter;
	this->input_char_ = 0xFF;
	unsigned int x_max, y_max;
	adapter->get_size(&x_max, &y_max);
	this->model_->set_max_xy(x_max - 1, y_max - 1);
}

void Controller::read_input()
{
	this->input_char_ = this->adapter_->get_input();
}

void Controller::pass_input_to_model()
{
	this->model_->take_new_input(this->get_input_code());
}

bool Controller::is_valid_input()
{
	return this->is_text() || this->is_in_navigation_command_symbols()
		|| this->is_valid_navigation_input() || this->is_special_key();
}

void Controller::handle_input()
{
	if (this->is_special_key())
	{
		int code = this->get_input_code();
		switch (code)
		{
		case K_BACKSPACE:
			this->model_->erase_with_backspace();
			break;

		case K_ESCAPE:
			this->pass_input_to_model();
			this->model_->handle_regime_change();
			break;

		case K_ENTER:
			this->model_->execute_command();
			break;

		default:
			break;
		}
	}
	else
	{
		enum Regime actual_regime = this->model_->get_regime();
		switch (actual_regime)
		{
		case NAVIGATION:
			if (this->is_valid_navigation_input())
				this->handle_navigation();
			break;

		default:
			if (this->is_valid_cmdline_input())
				this->handle_other_regimes();
			break;
		}
	}
}

int Controller::get_input_code()
{
	return this->input_char_;
}
/////////////////
//// PRIVATE ////
/////////////////
bool Controller::is_navigation_button()
{
	for (int i = 0; i < navigation_keys_.size(); i++)
	{
		if (this->get_input_code() == navigation_keys_[i])
			return true;
	}
	return false;
}

bool Controller::is_in_navigation_one_symbol_commands()
{
	return navigation_one_symbol_commands_.simple_find(this->get_input_code());
}

bool Controller::is_in_navigation_command_symbols()
{
	return navigation_command_symbols_.simple_find(this->get_input_code());
}


bool Controller::is_in_regime_change_symbols()
{
	return regime_change_symbols_.simple_find(this->get_input_code()) || this->get_input_code() == K_ESCAPE;
}


bool Controller::is_in_find_one_symbol_commands()
{
	return find_one_symbol_commands_.simple_find(this->get_input_code());
}

bool Controller::is_in_find_command_symbols()
{
	return find_command_symbols_.simple_find(this->get_input_code());
}


bool Controller::is_text()
{
	return this->is_ciph() || this->is_in_alphabet() || this->is_symbol();
}

bool Controller::is_special_key()
{
	for (int i = 0; i < special_keys_.size(); i++)
	{
		if (this->get_input_code() == special_keys_[i])
			return true;
	}
	return false;
}

bool Controller::is_in_alphabet()
{
	return ('a' <= this->get_input_code() && this->get_input_code() <= 'z' ||
		'A' <= this->get_input_code() && this->get_input_code() <= 'Z');
}

bool Controller::is_ciph()
{
	return ('0' <= this->get_input_code() && this->get_input_code() <= '9');
}

bool Controller::is_symbol()
{
	return symbols_.simple_find(this->get_input_code());
}


bool Controller::is_valid_navigation_input()
{
	return this->is_in_regime_change_symbols() || this->is_navigation_button()
		|| this->is_in_navigation_one_symbol_commands()
		|| this->is_in_navigation_command_symbols() || this->is_ciph();
}

bool Controller::is_valid_cmdline_input()
{
	return this->is_text() || this->is_navigation_button();
}



void Controller::handle_navigation()
{
	if (this->is_navigation_button())
	{
		this->mutate_cursor_moving_keys_for_model();
		this->pass_input_to_model();
		this->model_->handle_cursor_change();
	}
	else
	{
		this->pass_input_to_model();

		if (this->is_in_regime_change_symbols())
			this->model_->handle_regime_change();

		else if (this->is_in_navigation_one_symbol_commands())
			this->model_->handle_navigation_one_symbol_command();

		else if (this->is_in_navigation_command_symbols() || this->is_ciph())
			this->model_->handle_text_input();
	}
}

void Controller::handle_other_regimes()
{
	if (this->is_navigation_button())
	{
		this->mutate_cursor_moving_keys_for_model();
		this->pass_input_to_model();
		this->model_->handle_cursor_change();
	}
	else
	{
		this->pass_input_to_model();
		this->model_->handle_text_input();
	}
}

void Controller::mutate_cursor_moving_keys_for_model()
{
	enum MoveCursorWays model_format = DOWN;
	switch (this->get_input_code())
	{
		case KEY_DOWN:
			model_format = DOWN;
			break;
		case KEY_UP:
			model_format = UP;
			break;
		case KEY_LEFT:
			model_format = LEFT;
			break;
		case KEY_RIGHT:
			model_format = RIGHT;
			break;
		case KEY_PPAGE:
			model_format = PAGE_UP;
			break;
		case KEY_NPAGE:
			model_format = PAGE_DOWN;
			break;
	}
	this->input_char_ = model_format;
}

void Controller::adapt_model_for_window_size()
{
	//unsigned int x_max, y_max;
	//this->adapter_->get_size(&x_max, &y_max);
	//this->model_->set_max_xy(x_max, y_max);
}