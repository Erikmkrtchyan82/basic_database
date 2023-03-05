#ifndef _add_operation_hpp_
#define _add_operation_hpp_

#include <vector>
#include <string>

#include "../headers/operation.hpp"

class Add: public Operation {
public:
    Add();
    int execute (const std::vector<std::string>& ) override;
public:
    const static std::string NAME;
};
const std::string Add::NAME = "ADD";

#endif // _add_operation_hpp_