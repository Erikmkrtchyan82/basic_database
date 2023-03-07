#ifndef _add_operation_hpp_
#define _add_operation_hpp_

#include <vector>
#include <string>
#include <functional>
#include <nlohmann/json.hpp>

#include "../headers/operation.hpp"

class Add: public Operation {
public:
    Add(std::string name = "ADD");
    std::function<bool(nlohmann::json&)> execute (const std::vector<std::string>&) override;
};

#endif // _add_operation_hpp_