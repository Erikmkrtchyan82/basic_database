#include "../headers/add_operation.hpp"

#include <functional>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../headers/utils.hpp"

using json = nlohmann::json;

Add::Add() {
    this->_class_name = "ADD";
}

std::function<bool(json&)> Add::execute(const std::vector<std::string>& query) {
    std::vector<std::string> name_chunks = split(query[1], ',');
    std::vector<std::string> value_chunks = split(query[3], ',');

    json js = deserialize(name_chunks, value_chunks);

    std::string type_name = query[0];

    return [=](json& db) {
        if (!db.contains(type_name))
            db[type_name] = json::array();

        for (auto& obj : db[type_name]) {
            bool same_obj = true;
            for (auto& [key, _] : js.items()) {
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
