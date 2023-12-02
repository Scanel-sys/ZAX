#pragma once

#include "../Model/Model.h"
#include "../view/ncurses_adapter.h"


class Controller {
	private:
		unsigned char input_char_;
		Model* model_;
		NcursesAdapter* adapter_;
	public:
		Controller(Model* model, NcursesAdapter* adapter);
		void read_input();
		void pass_input();
};