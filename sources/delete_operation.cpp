#include "../headers/delete_operation.hpp"

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../headers/utils.hpp"

using json = nlohmann::json;

Delete::Delete() {
    this->_class_name = "delete";
}

void Delete::validate(const std::vector<std::string>& query, const json& scheme) {
    this->_check_size(query.size(), 3);

    std::string table_name = query[0];
    std::vector<std::string> chunks = split(query[2], ",");

    std::vector<std::string> name_chunks;
    std::vector<std::string> compares;
    std::vector<std::string> value_chunks;

    for (auto& chunk : chunks) {
        std::string name, compare, value;
        if (chunk.find("!=") != std::string::npos) {
            compare = "!=";
        } else {
            compare = "=";
        }
        auto name_value = split(chunk, compare);
        name_chunks.push_back(name_value[0]);
        compares.push_back(compare);
        value_chunks.push_back(name_value[1]);
    }

    if (!scheme.contains(table_name)) {
        throw "[ERROR]: Unknown table '" + table_name + "'!";
    }
    if (to_lower(query[1]) != "where") {
        throw "[ERROR]: Unknown keyword '" + query[1] + "'!";
    }
    if (name_chunks.size() != value_chunks.size()) {
        throw "[ERROR]: Expected " + std::to_string(name_chunks.size()) + " values, found " + std::to_string(value_chunks.size()) + "!";
    }
    for (int i = 0; i < name_chunks.size(); ++i) {
        auto& key = name_chunks[i];
        auto& value = value_chunks[i];
        if (!scheme[table_name].contains(key)) {
            throw "[ERROR]: Unknown column '" + key + "' in '" + table_name + "' table!";
        }
        if (!match(scheme[table_name][key], value)) {
            throw "[ERROR]: " + value + " is not " + std::string(scheme[table_name][key]) + " type!";
        }
    }
}

std::function<bool(json&)> Delete::execute(const std::vector<std::string>& query) {
    std::string table_name = query[0];
    std::vector<std::string> chunks = split(query[2], ",");

    std::vector<std::string> name_chunks;
    std::vector<std::string> compares;
    std::vector<std::string> value_chunks;

    for (auto& chunk : chunks) {
        std::string name, compare, value;
        if (chunk.find("!=") != std::string::npos) {
            compare = "!=";
        } else {
            compare = "=";
        }
        auto name_value = split(chunk, compare);
        name_chunks.push_back(name_value[0]);
        compares.push_back(compare);
        value_chunks.push_back(name_value[1]);
    }

    return [=](json& db) {
        json not_matched_objs;
        not_matched_objs[table_name] = json::array();
        for (auto& obj : db[table_name]) {
            bool match = true;
            for (int i = 0; i < name_chunks.size(); ++i) {
                if (compares[i] == "=") {
                    if (obj[name_chunks[i]].is_string()) {
                        if (obj[name_chunks[i]].get<std::string>() != value_chunks[i]) {
                            match = false;
                            break;
                        }
                    } else {
                        if (obj[name_chunks[i]] != std::stoi(value_chunks[i])) {
                            match = false;
                            break;
                        }
                    }
                } else if (compares[i] == "!=") {
                    if (obj[name_chunks[i]].is_string()) {
                        if (obj[name_chunks[i]].get<std::string>() == value_chunks[i]) {
                            match = false;
                            break;
                        }
                    } else {
                        if (obj[name_chunks[i]] == std::stoi(value_chunks[i])) {
                            match = false;
                            break;
                        }
                    }
                }
            }
            if (!match) {
                not_matched_objs[table_name].push_back(obj);
            }
        }
        db[table_name] = not_matched_objs[table_name];
        std::cout << "DELETED" << std::endl;

        return true;
    };
}
