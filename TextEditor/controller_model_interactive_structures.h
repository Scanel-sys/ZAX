#pragma once

enum Regime {
    NAVIGATION, WRITE, COMMAND, FIND, QUIT
};

enum MoveCursorWays {
    UP, DOWN, LEFT, RIGHT, PAGE_UP, PAGE_DOWN
};

enum KeyWays {
    KEY_DOWN_W = 0x102,
    KEY_UP_W = 0x103,
    KEY_LEFT_W = 0x104,
    KEY_RIGHT_W = 0x105,
    PAGE_UP_W,
    PAGE_DOWN_W
};