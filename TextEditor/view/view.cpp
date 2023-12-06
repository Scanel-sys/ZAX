#include "view.h"


View::View(Model* model, NcursesAdapter* adapter) {
    this->model_ = model;
    this->adapter_ = adapter;
    this->adapter_->get_size(&this->screen_size_x_, &this->screen_size_y_);
    this->content_window_id_ = this->adapter_->add_window(0, 0, this->screen_size_y_-1, this->screen_size_x_, 0);
    this->command_window_id_ = this->adapter_->add_window(this->screen_size_y_-1, 0, 1, this->screen_size_x_, 1);
    this->model_->attach(this);
}

void View::update(const ModelData* model_data) {
    if (model_data->command == 0xFF) {
        this->adapter_->clear_window(command_window_id_);
        this->adapter_->write_window(command_window_id_, this->model_->get_command());
        this->adapter_->refresh_window(command_window_id_);
    }
}