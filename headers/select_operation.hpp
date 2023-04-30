#ifndef _select_operation_hpp_
#define _select_operation_hpp_

#include <functional>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../headers/operation.hpp"

class Select : public Operation {
   public:
    Select();
    std::function<bool(nlohmann::json&)> execute(const std::vector<std::string>&) override;
    void validate(const std::vector<std::string>&, const nlohmann::json&) override;

   private:
    void _validate_all(const std::vector<std::string>&, const nlohmann::json&);
};

#endif  // _select_operation_hpp_