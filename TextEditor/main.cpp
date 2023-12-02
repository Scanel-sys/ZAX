#include "Model/Model.h"
#include "view/view.h"
#include "view/ncurses_adapter.h"
#include "Controller/Controller.h"


int main() {
    Model model;
    NcursesAdapter adapter;
    View view(&model, &adapter);
    Controller controller(&model, &adapter);

    adapter.get_input();
    model.do_something();
    adapter.get_input();

    return 0;
}