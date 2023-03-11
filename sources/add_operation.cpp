#include "../headers/add_operation.hpp"

#include <functional>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../headers/utils.hpp"

using json = nlohmann::json;

Add::Add() {
    this->_class_name = "add";
}

void Add::validate(const std::vector<std::string>& query, const json& scheme) {
    this->_check_size(query.size(), 4);

    std::string table_name = query[0];
    std::vector<std::string> name_chunks = split(query[1], ",");
    std::vector<std::string> value_chunks = split(query[3], ",");

    if (!scheme.contains(table_name)) {
        throw "[ERROR]: Unknown table '" + table_name + "'!";
    }
    if (to_lower(query[2]) != "values") {
        throw "[ERROR]: Unknown keyword '" + query[2] + "'!";
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
    std::vector<std::string> absent_keys;
    for (auto& [key, value] : scheme[table_name].items()) {
        if (std::find(name_chunks.begin(), name_chunks.end(), key) == name_chunks.end()) {
            absent_keys.push_back(key);
        }
    }
    if (absent_keys.size() != 0) {
        std::string error_message{};
        for (auto& key : absent_keys) {
            error_message += "\n[ERROR]: Value for '" + key + "' is not set!";
        }
        throw error_message;
    }
}

std::function<bool(json&)> Add::execute(const std::vector<std::string>& query) {
    std::string table_name = query[0];
    std::vector<std::string> name_chunks = split(query[1], ",");
    std::vector<std::string> value_chunks = split(query[3], ",");

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

    return 0;
}
