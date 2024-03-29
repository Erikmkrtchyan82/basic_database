#ifndef _delete_operation_hpp_
#define _delete_operation_hpp_

#include <functional>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../headers/operation.hpp"

class Delete : public Operation {
   public:
    Delete();
    std::function<bool(nlohmann::json&)> execute(const std::vector<std::string>&) override;
    void validate(const std::vector<std::string>&, const nlohmann::json&) override;

   private:
    void _validate_all(const std::vector<std::string>& query, const nlohmann::json& scheme);
};

#endif  // _delete_operation_hpp_