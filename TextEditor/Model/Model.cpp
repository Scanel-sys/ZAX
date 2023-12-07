#include "Model.h"


Model::Model() {
    this->regime_name_ = "NAVIGATION";
    this->regime_ = NAVIGATION;
    this->user_input_;
    this->model_data_ = {0x00, 0x00, 0x00};
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

MyString& Model::get_regime_name_str(){
    return this->regime_name_;
}

enum Regime Model::get_regime() const
{
    return this->regime_;
}

void Model::take_new_input(char new_input)
{
    this->model_data_.content = new_input;
}

void Model::handle_text_input() {
    this->model_data_.command = 0xFF;
    notify();
}

unsigned int Model::get_command_size() const
{
    return this->command_.size();
}

void Model::handle_navigation_one_symbol_command()
{

}

void Model::move_cursor(enum MoveCursorWays way)
{

}

void Model::change_regime()
{

}