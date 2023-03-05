#ifndef _operation_hpp_
#define _operation_hpp_

#include <string>

class Operation {
public:
    virtual int execute(const std::vector<std::string>&) = 0;
    // std::string get_name() {return this->_name;};
public:
    const static std::string NAME;
};



class Select: public Operation {};

#endif // _operation_hpp_