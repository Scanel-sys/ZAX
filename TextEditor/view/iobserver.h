#pragma once

struct ModelData {
    int content;
    char command;
    unsigned int cursor_position_cmd;
    unsigned int cursor_position_text;
    unsigned int y_max;
    unsigned int x_max;
    unsigned int view_actual_line_number;
    unsigned int general_actual_line_number;
    unsigned int max_line_number;
};

class IObserver {
    public:
        virtual void update(const ModelData* mods) = 0;
};