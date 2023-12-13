#include "Model.h"


Model::Model() {
    this->model_data_.content = 0;
    this->model_data_.command = 0;
    
    this->cursor_position_text = { 0, 0};
    this->cursor_position_cmd = { 0, 0};

    this->model_data_.view_actual_line_number = 0;
    this->model_data_.general_actual_line_number = 0;
    this->model_data_.max_line_number = 1;

    this->command_;
    this->regime_ = NAVIGATION;
    this->line_size_ = 0;
    this->view_content_.push_back("");
    this->content_.push_back("");
}

void Model::set_regime(enum Regime new_regime)
{
    this->regime_ = new_regime;
}


struct xy_coords Model::get_cmd_cursor_position()
{
    return this->cursor_position_cmd;
}

struct xy_coords Model::get_text_cursor_position()
{
    return this->cursor_position_text;
}

void Model::move_text_cursor_up()
{

}

void Model::move_text_cursor_down()
{

}

void Model::move_text_cursor_left()
{
    if (this->cursor_position_text.x > 0)
    {
        this->cursor_position_text.x--;
    }
    else if (this->cursor_position_text.y > 0)
    {
        this->cursor_position_text.x = this->model_data_.x_max;
        this->cursor_position_text.y--;
    }
}

void Model::move_text_cursor_right()
{
    if (this->cursor_position_text.x < this->model_data_.x_max && this->cursor_position_text.x < this->get_actual_content_line().size())
    {
        this->cursor_position_text.x++;
    }
    else if (this->cursor_position_text.x == this->model_data_.x_max && this->cursor_position_text.y < this->view_content_.size())
    {
        this->cursor_position_text.x = 0;
        this->cursor_position_text.y++;
    }
}

void Model::clear_command()
{
    this->command_.clear();
}

void Model::clear_view_output()
{
    this->view_content_.clear();
}

void Model::reset_command_coords()
{
    this->cursor_position_cmd.x = 0;
}

void Model::open_file()
{
    std::ifstream fin;
    fin.open(this->filename_.c_str(), std::ios::binary);
    if (!fin.is_open())
    {
        this->filename_ = "NULL";
        return;
    }

    content_.clear();
    content_.push_back("");
    char c;
    int row_iter = 0, line_iter = 0;
    while (1)
    {
        c = fin.get();
        if (fin.eof())
            break;
        //else if (c == '\r')
            //continue;
        else if (c == '\n')
        {
            content_[row_iter].append(1, c);
            content_.push_back("");
            row_iter++;
            line_iter = 0;
        }
        else if (line_iter == MAX_LINE_SIZE)
        {
            content_.push_back("");
            line_iter = 0;
            row_iter++;
            content_[row_iter].append(1, c);
            line_iter++;
        }
    }
    fin.close();
}

void Model::build_output()
{
    int symbols_to_load = this->model_data_.x_max * this->model_data_.y_max * DEAFULT_PAGES_TO_LOAD;
    int needed_strings = symbols_to_load / MAX_LINE_SIZE + 1;
    this->clear_view_output();

    unsigned int line_iter = 0;
    unsigned int line_start = this->get_actual_line_number() -  this->model_data_.y_max;
    unsigned int line_stop = line_start + this->model_data_.y_max;

    while (line_iter < this->content_.size() && line_iter < needed_strings)
    {

    }

}



void Model::attach(IObserver* observer) {
    this->observers_.push_back(observer);
    ModelData all = {0xFF, 0xFF, 0xFF};
    observer->update((const ModelData*)&all);
}

void Model::detach(IObserver* observer) {
    std::vector<IObserver*>::const_iterator i;
    i = find(this->observers_.begin(), this->observers_.end(), observer);
    this->observers_.erase(i);
}

void Model::notify() {
    for (unsigned int i = 0; i < this->observers_.size(); i++)
        this->observers_[i]->update((const ModelData*)&model_data_);
}


void Model::take_new_input(int new_input)
{
    this->model_data_.content = new_input;
}

void Model::handle_navigation_one_symbol_command()
{

    this->notify();
}

void Model::handle_text_input() {
    if (this->get_regime() != WRITE)
    {
        this->command_.insert(this->get_cmd_cursor_position().x, 1, (char)this->get_input());
        this->move_cmd_cursor(RIGHT);
    }
    else
    {
        xy_coords temp_text_coords = this->get_text_cursor_position();
        if (this->get_actual_view_line().size() < MAX_LINE_SIZE)
        {
            
            this->get_actual_view_line().insert(temp_text_coords.x, 1, (char)this->get_input());
        }
        this->move_text_cursor(RIGHT);
    }
    this->notify();
}


void Model::move_text_cursor(enum MoveCursorWays direction)
{
    if (direction == RIGHT)
        this->move_text_cursor_right();
    else if (direction == LEFT)
        this->move_text_cursor_left();
    else if (direction == UP)
        this->move_text_cursor_up();
    else if (direction == DOWN)
        this->move_text_cursor_down();
    else if (direction == PAGE_DOWN)
        this->go_page_down();
    else if (direction == PAGE_UP)
        this->go_page_up();
}

void Model::move_cmd_cursor(enum MoveCursorWays direction)
{
    if (direction == RIGHT)
    {
        if (this->cursor_position_cmd.x < this->command_.size())
            this->cursor_position_cmd.x++;
    }
    else if (direction == LEFT)
    {
        if (this->cursor_position_cmd.x > 0)
            this->cursor_position_cmd.x--;
    }
}

void Model::go_page_up()
{

}

void Model::go_page_down()
{

}


void Model::handle_regime_change()
{
    this->clear_command();
    this->reset_command_coords();
    if (this->get_input() == K_ESCAPE)
    {
        this->set_regime(NAVIGATION);
    }
    else if (this->get_regime() == NAVIGATION)
    {
        switch (this->get_input())
        {
        case 'i':
            this->set_regime(WRITE);
            break;
        case 'I':
            this->set_regime(WRITE);
            break;
        case 'S':
            this->set_regime(WRITE);
            break;
        case 'A':
            this->set_regime(WRITE);
            break;
        case 'r':
            this->set_regime(WRITE);
            break;
        case ':':
            this->set_regime(COMMAND);
            break;
        case '/':
            this->set_regime(FIND);
            break;
        case '?':
            this->set_regime(FIND);
            break;
        default:
            break;
        }
    }
    this->notify();
}

void Model::handle_cursor_change()
{
    if (this->get_regime() == NAVIGATION || this->get_regime() == WRITE)
    {
        enum MoveCursorWays direction = (enum MoveCursorWays)this->get_input();
        switch (this->get_input())
        {
            case UP:
                this->move_text_cursor(UP);
                break;
            case DOWN:
                this->move_text_cursor(DOWN);
                break;
            case LEFT:
                this->move_text_cursor(LEFT);
                break;
            case RIGHT:
                this->move_text_cursor(RIGHT);
                break;
            case PAGE_UP:
                this->move_text_cursor(PAGE_UP);
                break;
            case PAGE_DOWN:
                this->move_text_cursor(PAGE_DOWN);
                break;
            default:
                break;
        }
    }
    else
    {
        switch (this->get_input())
        {
            case LEFT:
                this->move_cmd_cursor(LEFT);
                break;
            case RIGHT:
                this->move_cmd_cursor(RIGHT);
                break;
            default:
                break;
        }
    }
    this->notify();
}


int Model::get_input()
{
    return this->model_data_.content;
}

unsigned int Model::get_command_size() const
{
    return this->command_.size();
}

MyString Model::get_regime_name_str(){
    switch (this->regime_)
    {
        case NAVIGATION:
            return MyString("navigation");
        case WRITE:
            return MyString("write");
        case COMMAND:
            return MyString("command");
        case FIND:
            return MyString("find");
        case QUIT:
            return MyString("quit");
        default:
            return MyString("none");
    }
}

enum Regime Model::get_regime() const
{
    return this->regime_;
}

MyString Model::get_command()
{
    return this->command_;
}


void Model::set_max_xy(unsigned int x, unsigned int y)
{
    this->model_data_.x_max = x;
    this->model_data_.y_max = y;
}


void Model::execute_command()
{

    this->notify();
}

void Model::erase_with_backspace()
{
    Regime regime = this->get_regime();
    if (regime == NAVIGATION || regime == FIND || regime == COMMAND)
    {
        int cursor_pos = this->get_cmd_cursor_position().x;
        if (0 < cursor_pos)
        {
            this->command_.erase(cursor_pos - 1, 1);
            this->move_cmd_cursor(LEFT);
        }
    }
    else if (regime == WRITE)
    {
        xy_coords cursor_coords = this->get_text_cursor_position();
        if (0 < cursor_coords.x)
        {
            this->get_actual_view_line().erase(cursor_coords.x - 1, 1);
            this->move_text_cursor(LEFT);
        }
    }
    this->notify();
}


xy_coords Model::get_cursor_position()
{
    if (this->get_regime() == WRITE || this->get_regime() == NAVIGATION)
        return this->cursor_position_text;
    else
        return this->cursor_position_cmd;
}

MyString& Model::get_actual_view_line()
{
    return this->view_content_[this->model_data_.view_actual_line_number];
}

MyString& Model::get_actual_content_line()
{
    return this->content_[this->model_data_.general_actual_line_number];
}

MyString Model::get_view_line(unsigned int line_number)
{
    return this->view_content_[line_number];
}

unsigned int Model::get_actual_line_number()
{
    return this->model_data_.general_actual_line_number + 1;
}

const std::vector<MyString>& Model::get_view_content() const 
{
    return this->view_content_;
}


unsigned int Model::get_max_line_number()
{
    return this->model_data_.max_line_number;
}

MyString Model::get_filename()
{
    return this->filename_;
}
