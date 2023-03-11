#ifndef _add_operation_hpp_
#define _add_operation_hpp_

#include <functional>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../headers/operation.hpp"

class Add : public Operation {
   public:
    Add();
    std::function<bool(nlohmann::json&)> execute(const std::vector<std::string>&) override;
    void validate(const std::vector<std::string>&, const nlohmann::json&) override;
};

#endif  // _add_operation_hpp_