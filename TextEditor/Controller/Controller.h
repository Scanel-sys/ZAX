#pragma once

#include "../Model/Model.h"
#include "../view/ncurses_adapter.h"

class Controller {
	private:
		MyString symbols{ "~`!@#$%^&*()-_=+[{]}\\|;:'\",<.>/?" };
		std::vector <int> keys = {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT};
		char input_char_;
		Model* model_;
		NcursesAdapter* adapter_;
		bool is_in_alphabet();
		bool is_ciph();
		bool is_symbol();
	public:
		Controller(Model* model, NcursesAdapter* adapter);
		void read_input();
		void pass_input_to_model();
		bool is_valid_input();
		char get_input_char();
};

