#include "Model.h"


Model::Model() {
    this->model_data_.content = 0;
    this->model_data_.command = 0;
    
    this->model_data_.cursor_position_text = 0;
    this->model_data_.cursor_position_cmd = 0;

    this->model_data_.view_actual_line_number = 0;
    this->model_data_.general_actual_line_number = 0;
    this->model_data_.max_line_number = 0;

    this->command_;
    this->regime_ = NAVIGATION;
    this->line_size_ = 0;
    this->view_content_.push_back("");
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

void Model::take_new_input(int new_input)
{
    this->model_data_.content = new_input;
}

void Model::handle_text_input() {
    if (this->get_regime() != WRITE)
    {
        this->command_.insert(this->get_cmd_cursor_position(), 1, (char)this->get_input());
        this->move_cursor(RIGHT);
    }
    else
    {
        this->get_actual_line().insert(this->get_text_cursor_position(), 1, (char)this->get_input());
        this->move_cursor(RIGHT);
    }
    this->notify();
}

unsigned int Model::get_command_size() const
{
    return this->command_.size();
}

void Model::handle_navigation_one_symbol_command()
{

    this->notify();
}

void Model::move_cursor(enum MoveCursorWays way)
{
    if (this->get_regime() != WRITE)
    {
        
    }
    else
    {
        this->get_actual_line().insert(this->get_text_cursor_position(), 1, (char)this->get_input());
        this->move_cursor(RIGHT);
    }
}

void Model::handle_regime_change()
{
    this->clear_command();
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

void Model::handle_cursor_change(int cursor_command)
{

}

void Model::clear_command()
{
    this->command_.clear();
}

int Model::get_input()
{
    return this->model_data_.content;
}

unsigned int Model::get_cmd_cursor_position()
{
    return this->model_data_.cursor_position_text;
}

unsigned int Model::get_text_cursor_position()
{
    return this->model_data_.cursor_position_cmd;
}

void Model::set_regime(enum Regime new_regime)
{
    this->regime_ = new_regime;
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

    this->notify();
}

MyString& Model::get_actual_line()
{
    return this->view_content_[this->model_data_.view_actual_line_number];
}

MyString Model::get_output_line(unsigned int line_number)
{
    return this->view_content_[line_number];
}

unsigned int Model::get_actual_line_number()
{
    return this->model_data_.general_actual_line_number;
}

unsigned int Model::get_max_line_number()
{
    return this->model_data_.max_line_number;
}

MyString Model::get_filename()
{
    return this->filename_;
}