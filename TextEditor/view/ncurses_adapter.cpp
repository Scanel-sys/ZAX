#include "ncurses_adapter.h"


NcursesAdapter::NcursesAdapter() {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);

    //raw();
    //nonl();
    noecho();
    //curs_set(0);

    // Colors
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    // Show
    refresh();
}

NcursesAdapter::~NcursesAdapter() {
    for (unsigned int i = 0; i < this->windows_.size(); i++)
        delwin(this->windows_[i]);
    endwin();
}

void NcursesAdapter::get_size(unsigned int *x, unsigned int *y) {
    *x = getmaxx(stdscr);
    *y = getmaxy(stdscr);
}

unsigned int NcursesAdapter::add_window(unsigned int sy, unsigned int sx,
                                        unsigned int h, unsigned int w, 
                                        unsigned int color_pair_id) {
    WINDOW *new_window = newwin(h, w, sy, sx);
    if (color_pair_id > 0)
        wbkgd(new_window, COLOR_PAIR(color_pair_id));
    keypad(new_window, TRUE);
    this->windows_.push_back(new_window);
    wrefresh(new_window);
    return this->windows_.size() - 1;
}

void NcursesAdapter::delete_window(unsigned int window_id) {
    WINDOW* cur_window = this->windows_[window_id];
    this->windows_.erase(this->windows_.begin() + window_id);
    delwin(cur_window);
    refresh();
}

void NcursesAdapter::clear_window(unsigned int window_id) {
    WINDOW* cur_window = this->windows_[window_id];
    wclear(cur_window);
}

void NcursesAdapter::refresh_window(unsigned int window_id) {
    WINDOW* cur_window = this->windows_[window_id];
    wrefresh(cur_window);
}

void NcursesAdapter::set_active_window(unsigned int window_id) {
    this->active_window_ = this->windows_[window_id];
}

void NcursesAdapter::write_window(unsigned int window_id, MyString str, int line_number) {
    WINDOW* cur_window = this->windows_[window_id];
    mvwprintw(cur_window, line_number, 0, str.c_str());
}

void NcursesAdapter::set_cursor(unsigned int window_id, unsigned int y, unsigned int x) {
    this->active_window_ = this->windows_[window_id];
    wmove(this->active_window_, y, x);
}

int NcursesAdapter::get_input() {
    return wgetch(this->active_window_);
}