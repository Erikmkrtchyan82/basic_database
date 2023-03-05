#ifndef _select_operation_hpp_
#define _select_operation_hpp_

#include <vector>
#include <string>

#include "../headers/operation.hpp"

class Select: public Operation {
public:
    Select(std::string name = "SELECT");
    int execute (const std::vector<std::string>&, std::vector<type_ptr>&) override;
};


#endif // _select_operation_hpp_