#include "../headers/select_operation.hpp"

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

Select::Select() {
    this->_class_name = "SELECT";
}

std::function<bool(json&)> Select::execute(const std::vector<std::string>& query) {
    // SELECT LAB WHERE name="lab1",dep!="dep1"
    std::string table_name = query[0];
    std::vector<std::string> chunks = split(query[2], ',');

    // TODO:
    std::vector<std::string> name_chunks;
    std::vector<std::string> compares;
    std::vector<std::string> value_chunks;

    json js = deserialize(name_chunks, value_chunks);

    return [=](json& db) {
        if (!db.contains(table_name))
            db[table_name] = json::array();

        for (auto& obj : db[table_name]) {
            bool same_obj = true;
            for (auto& [key, _] : js.items()) {
                same_obj &= (obj[key] == js[key]);
            }
            if (same_obj) {
                std::cout << "[ERROR]: element already exists!" << std::endl;
                return false;
            }
        }

        db[table_name].push_back(js);

        return true;
    };
}
