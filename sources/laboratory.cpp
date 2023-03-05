#include <ostream>
#include "../headers/laboratory.hpp"

std::ostream& operator<<(std::ostream& os, Laboratory& obj){
    os << "Laboratory <name: " <<obj.get_name() << ", room_number: " << obj.get_room_number() << '>';
    return os;
}


Laboratory::Laboratory(std::string name, 
                       uint room_number) : _name(name),
                                           _room_number(room_number){}

std::string Laboratory::get_name() {
    return this->_name;
}
uint Laboratory::get_room_number() {
    return this->_room_number;
}

