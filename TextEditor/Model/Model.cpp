#include "Model.h"


Model::Model() {
    this->command_ = "Init";
    this->mods_ = {0x00, 0x00, 0x00};
}


void Model::attach(IObserver* observer) {
    this->observers_.push_back(observer);
    Mods all = {0xFF, 0xFF, 0xFF};
    observer->update((const Mods*)&all);
}

void Model::detach(IObserver* observer) {
    std::vector<IObserver*>::const_iterator i;
    i = find(this->observers_.begin(), this->observers_.end(), observer);
    this->observers_.erase(i);
}

void Model::notify() {
    for (unsigned int i = 0; i < this->observers_.size(); i++)
        this->observers_[i]->update((const Mods*)&mods_);
}

MyString& Model::get_command() {
    return this->command_;
}

void Model::do_something() {
    this->command_ = "Finish";
    this->mods_.command = 0xFF;
    notify();
}