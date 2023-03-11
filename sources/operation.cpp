#include "../headers/operation.hpp"

#include "../headers/utils.hpp"

std::string Operation::get_name() const {
    return this->_class_name;
}

void Operation::_check_size(size_t actual_size, size_t expected_size) {
    if (actual_size != expected_size) {
        throw "[ERROR]: Arguments count doesn't match for '" + to_upper(this->_class_name) + "' operation!";
    }
}