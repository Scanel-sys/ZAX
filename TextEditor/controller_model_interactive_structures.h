#pragma once

#define K_ESCAPE       0x1b
#define K_BACKSPACE 0x8
#define K_ENTER     0xa


enum Regime {
    NAVIGATION, WRITE, COMMAND, FIND, QUIT
};

enum MoveCursorWays {
    UP, DOWN, LEFT, RIGHT, PAGE_UP, PAGE_DOWN
};