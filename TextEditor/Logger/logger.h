#pragma once
#include "iobserver.h"
#include "../model/model.h"

class Logger: public IObserver {
    private:
        Model *model_;
        MyString file_name_;
    public:
        Logger(Model *model, const MyString& file_name);
        ~Logger() {};
        virtual void update();
};