#pragma once

#include "../Model/Model.h"
#include "../view/ncurses_adapter.h"
#include "../controller_model_interactive_structures.h"


class Controller {
	private:
		char input_char_;
		Model* model_;
		NcursesAdapter* adapter_;
		
		bool is_navigation_button();
		bool is_in_navigation_one_symbol_commands();
		bool is_in_navigation_command_symbols();

		bool is_in_regime_change_symbols();

		bool is_in_find_one_symbol_commands();
		bool is_in_find_command_symbols();

		bool is_text();
		bool is_in_alphabet();
		bool is_ciph();
		bool is_symbol();

		bool is_valid_navigation_input();
		bool is_valid_find_input();
		bool is_valid_write_input();
		bool is_valid_command_input();

		void handle_navigation();
		void handle_other_regimes();
		void handle_cursor_moving_keys();

	public:
		Controller(Model* model, NcursesAdapter* adapter);
		void read_input();
		void pass_input_to_model();
		bool is_valid_input();
		void handle_input();
		char get_input_char();
};

