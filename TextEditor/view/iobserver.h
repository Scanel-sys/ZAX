#pragma once


struct Mods {
    unsigned char content;
    unsigned char command;
    unsigned char cursor;
};

class IObserver {
    public:
        virtual void update(const Mods* mods) = 0;
};