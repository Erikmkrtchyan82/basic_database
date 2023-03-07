// #ifndef _group_header_
// #define _group_header_

// #include "../headers/type.hpp"

// #include <string>
// #include <nlohmann/json.hpp>

// using json = nlohmann::json;

// class Group: public Type {
// public:
//     virtual ~Group(){};
//     Group(std::string name = "N/A",
//           std::string department = "N/A",
//           uint student_count = 0);

//     std::string get_name();
//     std::string get_department();
//     uint get_student_count();

//     std::unique_ptr<Type> serialize(json&) override;
//     json deserialize(std::unique_ptr<Type>&) override;
//     // static Group create(json js);
// private:
//     std::string _name;
//     std::string _department;
//     uint _student_count;
// };
// // init(Group);

// std::ostream& operator<<(std::ostream& os, Group& obj);

// #endif // _group_header_