#pragma once

#include "../view/iobserver.h"
#include "../MyString/MyString.h"
#include <vector>


class Model {
    private:
        ModelData model_data_;
        MyString regime_name_;
        MyString user_input_;
        std::vector<IObserver*> observers_;
    public:
        Model();
        void attach(IObserver* observer);
        void detach(IObserver* observer);
        void notify();
        MyString& get_command();
        enum Regime get_regime();
        void take_new_input(char new_input);
        void handle_input();
};