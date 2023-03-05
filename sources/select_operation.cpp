#include "../headers/select_operation.hpp"

#include "../headers/group.hpp"
#include "../headers/laboratory.hpp"

#include <vector>
#include <string>

Select::Select(std::string name) {
    _class_name = name;
}

int Select::execute(const std::vector<std::string>& query) {
    // ADD Lab.(name) VALUES "abcd";     (defaults: str -> N/A, int -> 0)
    return 0;
}

