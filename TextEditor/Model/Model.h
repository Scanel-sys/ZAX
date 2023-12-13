#pragma once

#include "../view/iobserver.h"
#include "../MyString/MyString.h"
#include <vector>
#include "../controller_model_interactive_structures.h"
#include <utility>
#include <fstream>

#define MAX_LINE_SIZE           (255)
#define DEAFULT_PAGES_TO_LOAD   (3)

struct xy_coords {
    int x;
    int y;
};



class Model {
    private:
        ModelData model_data_;
        MyString command_;
        MyString filename_{"NULL"};

        std::vector<IObserver*> observers_;
        
        xy_coords cursor_position_cmd{};
        xy_coords cursor_position_text{};
        std::vector <MyString> content_;
        std::vector <MyString> view_content_;
        
        int line_size_;

        enum Regime regime_;

        void set_regime(enum Regime new_regime);

        xy_coords get_cmd_cursor_position();
        xy_coords get_text_cursor_position();

        void move_text_cursor_up();
        void move_text_cursor_down();
        void move_text_cursor_left();
        void move_text_cursor_right();

        void clear_command();
        void clear_view_output();
        void reset_command_coords();

        void open_file();
        void build_output();

    public:
        Model();
        void attach(IObserver* observer);
        void detach(IObserver* observer);
        void notify();

        void take_new_input(int new_input);
        void handle_navigation_one_symbol_command();
        void handle_text_input();

        void move_text_cursor(enum MoveCursorWays);
        void move_cmd_cursor(enum MoveCursorWays);

        void go_page_up();
        void go_page_down();

        void handle_regime_change();
        void handle_cursor_change();

        int get_input();
        unsigned int get_command_size() const;
        MyString get_regime_name_str();
        enum Regime get_regime() const;
        MyString get_command();
        
        void set_max_xy(unsigned int x, unsigned int y);

        void execute_command();
        void erase_with_backspace();


        xy_coords  get_cursor_position();
        MyString& get_actual_view_line();
        MyString& get_actual_content_line();
        MyString get_view_line(unsigned int line_number);
        unsigned int get_actual_line_number();
        const std::vector<MyString>& get_view_content() const;
        unsigned int get_max_line_number();
        MyString get_filename();
};