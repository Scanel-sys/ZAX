#pragma once

#include "iobserver.h"
#include "ncurses_adapter.h"
#include "../Model/Model.h"
#include "../MyString/MyString.h"

MyString itoms(unsigned int n);

class View: public IObserver {
    private:
        Model *model_;
        NcursesAdapter *adapter_;
        MyString status_bar;
        unsigned int screen_size_x_, screen_size_y_;
        unsigned int command_window_id_, content_window_id_;
        MyString gather_status_bar();
        void write_strings(const std::vector <MyString>& output_strings);
        bool cursor_on_content();
    public:
        View(Model* model, NcursesAdapter* adapter);
        virtual void update(const ModelData* model_data) override;
};
