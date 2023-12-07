#include "Model/Model.h"
#include "view/view.h"
#include "view/ncurses_adapter.h"
#include "Controller/Controller.h"

/*
    TODO:
        + > Controller::regime handler
        + > Controller::validation
        > backspace | delete add
        > mystringS in model
*/

int main() {
    Model model;
    NcursesAdapter adapter;
    View view(&model, &adapter);
    Controller controller(&model, &adapter);

    while (model.get_regime() != QUIT)
    {
        do {
            controller.read_input();
        } while (controller.is_valid_input() != true);
        controller.handle_input();
    }
    return 0;
}