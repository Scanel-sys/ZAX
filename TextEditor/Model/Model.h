#pragma once

#include "../view/iobserver.h"
#include "../MyString/MyString.h"
#include <vector>


class Model {
    private:
        Mods mods_;
        MyString command_;
        std::vector<IObserver*> observers_;
    public:
        Model();
        void attach(IObserver* observer);
        void detach(IObserver* observer);
        void notify();
        MyString& get_command();
        void do_something();
};