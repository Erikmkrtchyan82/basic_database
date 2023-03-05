#include "../headers/group.hpp"
#include <ostream>

std::ostream& operator<<(std::ostream& os, Group& obj) {
    os << "Group <name: " << obj.get_name() 
       << ", department: " << obj.get_department()
       << ", student count: " << obj.get_student_count() << '>';
    return os;
}

// Group::Group():_name("N/A"),

Group::Group(std::string name = "N/A",
             std::string department = "N/A", 
             uint student_count = 0): _name(name), 
                                  _department(department), 
                                  _student_count(student_count){}

std::string Group::get_name() {
    return this->_name;
}

std::string Group::get_department() {
    return this->_department;
}

uint Group::get_student_count() {
    return this->_student_count;
}

