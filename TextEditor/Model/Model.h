#pragma once

#include "../view/iobserver.h"
#include "../MyString/MyString.h"
#include <vector>
#include "../controller_model_interactive_structures.h"


class Model {
    private:
        ModelData model_data_;
        MyString user_input_;
        MyString command_;
        enum Regime regime_;
        MyString regime_name_;

        std::vector<IObserver*> observers_;
    public:
        Model();
        void attach(IObserver* observer);
        void detach(IObserver* observer);
        void notify();
        MyString& get_regime_name_str();
        enum Regime get_regime() const;
        void take_new_input(char new_input);
        unsigned int get_command_size() const;
        
        void handle_text_input();
        void handle_navigation_one_symbol_command();
        void move_cursor(enum MoveCursorWays way);
        void change_regime();
};