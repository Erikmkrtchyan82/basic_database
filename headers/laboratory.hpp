#ifndef _laboratory_header_
#define _laboratory_header_

#include <string>

class Laboratory {
public:
    Laboratory(std::string name, uint room_number);
    std::string get_name();
    uint get_room_number();
private:
    std::string _name;
    uint _room_number;
};

std::ostream& operator<<(std::ostream& os, Laboratory& obj);

#endif // _laboratory_header_
