#include "view.h"


View::View(Model* model, NcursesAdapter* adapter) {
    this->model_ = model;
    this->adapter_ = adapter;
    this->adapter_->get_size(&this->screen_size_x_, &this->screen_size_y_);
    this->content_window_id_ = this->adapter_->add_window(0, 0, this->screen_size_y_-1, this->screen_size_x_, 0);
    this->command_window_id_ = this->adapter_->add_window(this->screen_size_y_-1, 0, 1, this->screen_size_x_, 1);
    this->adapter_->set_active_window(this->content_window_id_);
    this->model_->attach(this);
}

void View::update(const ModelData* model_data) {
    xy_coords cursor_coords = this->model_->get_cursor_position();

    MyString status_bar = this->gather_status_bar();
    this->adapter_->clear_window(command_window_id_);
    this->adapter_->write_window(command_window_id_, status_bar);
    if (!this->cursor_on_content())
        this->adapter_->set_cursor(this->command_window_id_, cursor_coords.y, cursor_coords.x + status_bar.size() - this->model_->get_command_size());
    this->adapter_->refresh_window(command_window_id_);

    this->adapter_->clear_window(content_window_id_);
    this->write_strings(this->model_->get_view_content());
    if(this->cursor_on_content())
        this->adapter_->set_cursor(this->content_window_id_, cursor_coords.y, cursor_coords.x);
    this->adapter_->refresh_window(content_window_id_);
}

MyString View::gather_status_bar()
{
    MyString output;
    output = this->model_->get_regime_name_str() + " | " + this->model_->get_filename() + " | ";
    output += itoms(this->model_->get_actual_line_number()) + "/";
    output += itoms(this->model_->get_max_line_number()) + " $: ";
    output += this->model_->get_command();
    return output;
}

void View::write_strings(const std::vector <MyString>& output_strings)
{
    for (int i = 0; i < output_strings.size(); i++)
        this->adapter_->write_window(content_window_id_, output_strings[i], i);
}

bool View::cursor_on_content()
{
    return this->model_->get_regime() == WRITE || this->model_->get_regime() == NAVIGATION;

}

MyString itoms(unsigned int n)
{
    MyString output;
    unsigned int temp_n = n;
    do
    {
        output.append(1, '0' + temp_n % 10);
        temp_n /= 10;
    } while (temp_n > 0);
    char temp;
    for (unsigned int i = 0; i < output.size() / 2; i++)
    {
        char temp = output[i];
        output[i] = output[output.size() - i - 1];
        output[output.size() - i - 1] = temp;
    }
    return output;
}
