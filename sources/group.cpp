// #include "../headers/group.hpp"
// #include <ostream>

// std::ostream& operator<<(std::ostream& os, Group& obj) {
//     os << "Group <name: " << obj.get_name() 
//        << ", department: " << obj.get_department()
//        << ", student count: " << obj.get_student_count() << '>';
//     return os;
// }

// Group::Group(std::string name,
//              std::string department,
//              uint student_count): _name(name), 
//                                   _department(department), 
//                                   _student_count(student_count) {
//     this->_class_name = "Group";
// }

// std::string Group::get_name() {
//     return this->_name;
// }

// std::string Group::get_department() {
//     return this->_department;
// }

// uint Group::get_student_count() {
//     return this->_student_count;
// }

// std::unique_ptr<Type> Group::serialize(json& js) {
//     std::string name = js["name"];
//     std::string department = js["department"];
//     uint student_count = static_cast<uint>(js["student_count"]);
//     return std::make_unique<Group>(name, department, student_count);
// }

// json Group::deserialize(std::unique_ptr<Type>& obj) {
//     return json{};
// }

