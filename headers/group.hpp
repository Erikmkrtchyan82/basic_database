#ifndef _group_header_
#define _group_header_

#include <string>

class Group {
public:
    Group();
    Group(std::string name, 
          std::string department, 
          uint student_count);

    std::string get_name();
    std::string get_department();
    uint get_student_count();

private:
    std::string _name;
    std::string _department;
    uint _student_count;
};

std::ostream& operator<<(std::ostream& os, Group& obj);

#endif // _group_header_