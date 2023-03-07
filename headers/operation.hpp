#ifndef _operation_hpp_
#define _operation_hpp_

#include <string>
#include <memory>
#include <functional>
#include <nlohmann/json.hpp>

#include "../headers/type.hpp"

class Operation {
public:
    virtual std::function<bool(nlohmann::json&)> execute(const std::vector<std::string>&) = 0;
    std::string get_name() const {return this->_class_name;};
    virtual ~Operation(){};
protected:
    std::string _class_name;
};

using operation_ptr = std::unique_ptr<Operation>;

#endif // _operation_hpp_