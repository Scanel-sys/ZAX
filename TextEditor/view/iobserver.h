#pragma once

enum Regime {
    NAVIGATION, WRITE, COMMAND, FIND, QUIT
};

struct ModelData {
    enum Regime regime;
    char content;
    char command;
    char cursor;
};

class IObserver {
    public:
        virtual void update(const ModelData* mods) = 0;
};