#pragma once

struct ModelData {
    char content;
    char command;
    char cursor;
};

class IObserver {
    public:
        virtual void update(const ModelData* mods) = 0;
};