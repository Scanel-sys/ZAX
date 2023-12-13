#pragma once

#include <vector>
#include <curses.h>
#include "../MyString/MyString.h"



class NcursesAdapter {
    private:
        std::vector<WINDOW*> windows_;
        WINDOW* active_window_;
    public:
        NcursesAdapter ();
        ~NcursesAdapter ();
        void get_size(unsigned int *x, unsigned int *y);
        unsigned int add_window(unsigned int sy, unsigned int sx,
                                unsigned int h, unsigned int w, 
                                unsigned int color_pair_id);
        void delete_window(unsigned int window_id);
        void clear_window(unsigned int window_id);
        void refresh_window(unsigned int window_id);
        void write_window(unsigned int window_id, MyString str, int line_number=0);
        virtual void set_active_window(unsigned int window_id);
        void set_cursor(unsigned int window_id, unsigned int y, unsigned int x);
        int get_input();
};