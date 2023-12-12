#pragma once

#include "../view/iobserver.h"
#include "../MyString/MyString.h"
#include <vector>
#include "../controller_model_interactive_structures.h"


class Model {
    private:
        ModelData model_data_;
        MyString command_;
        MyString filename_{"NULL"};

        std::vector<IObserver*> observers_;
        
        std::vector <MyString> content_;
        std::vector <MyString> view_content_;
        
        int line_size_;

        enum Regime regime_;

        void set_regime(enum Regime new_regime);

        unsigned int get_cmd_cursor_position();
        unsigned int get_text_cursor_position();

        void clear_command();

    public:
        Model();
        void attach(IObserver* observer);
        void detach(IObserver* observer);
        void notify();

        void take_new_input(int new_input);
        void handle_navigation_one_symbol_command();
        void handle_text_input();
        void move_cursor(enum MoveCursorWays way);

        void handle_regime_change();
        void handle_cursor_change(int cursor_command);

        int get_input();
        unsigned int get_command_size() const;
        MyString get_regime_name_str();
        enum Regime get_regime() const;
        
        void set_max_xy(unsigned int x, unsigned int y);

        void execute_command();
        void erase_with_backspace();

        MyString& get_actual_line();
        MyString get_output_line(unsigned int line_number);
        unsigned int get_actual_line_number();
        unsigned int get_max_line_number();
        MyString get_filename();
};