#ifndef _operation_hpp_
#define _operation_hpp_

#include <functional>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

class Operation {
   public:
    virtual std::function<bool(nlohmann::json&)> execute(const std::vector<std::string>&) = 0;
    virtual void validate(const std::vector<std::string>&, const nlohmann::json&) = 0;
    std::string get_name() const;
    virtual ~Operation(){};

   protected:
    void _check_size(size_t, size_t);
    std::string _class_name;
};

using operation_ptr = std::unique_ptr<Operation>;

#endif  // _operation_hpp_