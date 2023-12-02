#include <iostream>
#include <fstream>
#include "logger.h"

Logger::Logger(Model *model, const MyString& file_name) {
    this->model_ = model;
    this->file_name_ = file_name;
    this->model_->attach(this);
}

void Logger::update() {
    std::ofstream log_file;
    log_file.open (this->file_name_.c_str(), std::ios::out | std::ios::app);
    log_file << model_->get_command() << "\n";
    log_file.close();
}