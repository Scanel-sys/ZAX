#include "Model.h"


Model::Model() {
    this->regime_name_ = "NAVIGATION";
    this->user_input_;
    this->model_data_ = {NAVIGATION, 0x00, 0x00, 0x00};
}


void Model::attach(IObserver* observer) {
    this->observers_.push_back(observer);
    ModelData all = {NAVIGATION, 0xFF, 0xFF, 0xFF};
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

MyString& Model::get_command() {
    return this->regime_name_;
}

enum Regime Model::get_regime()
{
    return this->model_data_.regime;
}

void Model::take_new_input(char new_input)
{
    this->model_data_.content = new_input;
}

void Model::handle_input() {
    this->regime_name_ = "QUIT";
    this->model_data_.command = 0xFF;
    notify();
}