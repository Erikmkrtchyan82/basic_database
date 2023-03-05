#ifndef _type_hpp_
#define _type_hpp_

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Type {
public:
    virtual std::unique_ptr<Type> serialize(json&) = 0;
    virtual json deserialize(std::unique_ptr<Type>&) = 0;
    std::string get_class_name(){return this->_class_name;};
protected:
    std::string _class_name;
};

using type_ptr = std::unique_ptr<Type>;

#endif // _type_hpp_