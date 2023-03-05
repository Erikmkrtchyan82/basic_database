#include "../headers/add_operation.hpp"

#include "../headers/group.hpp"
#include "../headers/laboratory.hpp"
#include "../headers/utils.hpp"

#include <vector>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;


Add::Add(std::string name) {
    _class_name = name;
}
#include <iostream>
int Add::execute(const std::vector<std::string>& query, std::vector<type_ptr>& types) {
    // ADD Lab name VALUES "abcd";     (defaults: str -> N/A, int -> 0)
    json js;
    std::vector<std::string> name_chunks = split(query[1], ',');
    std::vector<std::string> value_chunks = split(query[3], ',');

    for(int i = 0; i < name_chunks.size(); ++i) {
        js[name_chunks[i]] = value_chunks[i];
    }

    std::string type_name = query[0];
    auto type = std::find_if(types.begin(), types.end(), 
                            [&type_name](type_ptr& tp){
                                return tp->get_class_name() == type_name;
                            });
    auto new_obj = (*type)->serialize(js);
    std::cout<<new_obj->get_student_count()<<std::endl;

    return 0;
}

