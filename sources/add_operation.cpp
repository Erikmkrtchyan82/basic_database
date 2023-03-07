#include "../headers/add_operation.hpp"

#include "../headers/group.hpp"
#include "../headers/laboratory.hpp"
#include "../headers/utils.hpp"

#include <vector>
#include <string>
#include <functional>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

Add::Add(std::string name) {
    _class_name = name;
}
#include <iostream>
std::function<bool(json&)> Add::execute(const std::vector<std::string>& query) {
    // ADD Lab name VALUES "abcd";     (defaults: str -> N/A, int -> 0)
    std::vector<std::string> name_chunks = split(query[1], ',');
    std::vector<std::string> value_chunks = split(query[3], ',');

    json js = deserialize(name_chunks, value_chunks);

    std::string type_name = query[0];

    return [=](json& db){
        if(!db.contains(type_name))
            db[type_name] = json::array();

        for(auto& obj: db[type_name]) {
            bool same_obj = true;
            for (auto& [key, _]: js.items()) {
                same_obj &= (obj[key] == js[key]);
            }
            if (same_obj) {
                std::cout << "[ERROR]: element already exists!" << std::endl;
                return false;
            }
        }

        db[type_name].push_back(js);
        
        return true;
    };

    return 0;
}

