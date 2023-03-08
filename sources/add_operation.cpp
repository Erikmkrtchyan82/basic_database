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

std::function<void(const json&)> Add::validate(const std::vector<std::string>& query) {
    std::string type_name = query[0];
    std::vector<std::string> name_chunks = split(query[1], ',');
    std::vector<std::string> value_chunks = split(query[3], ',');

    // ADD Lab name,count VALUES "abcd",12

    return [=](const json& scheme) {
        if (!scheme.contains(type_name)) {
            throw "[ERROR]: Unknown table '" + type_name + "'!";
        }
        if (query[2] != "VALUES") {
            throw "[ERROR]: Unknown keyword '" + query[2] + "'!";
        }
        if (name_chunks.size() != value_chunks.size()) {
            throw "[ERROR]: Expected " + std::to_string(name_chunks.size()) + " values, found " + std::to_string(value_chunks.size()) + "!";
        }
        for (int i = 0; i < name_chunks.size(); ++i) {
            auto& key = name_chunks[i];
            auto& value = value_chunks[i];
            if (!scheme[type_name].contains(key)) {
                throw "[ERROR]: Unknown column '" + key + "' in '" + type_name + "' table!";
            }
            if (!match(scheme[type_name][key], value)) {
                throw "[ERROR]: " + value + " is not " + std::string(scheme[type_name][key]) + " type!";
            }
        }
        std::vector<std::string> absent_keys;
        for (auto& [key, value] : scheme[type_name].items()) {
            if (std::find(name_chunks.begin(), name_chunks.end(), key) == name_chunks.end()) {
                absent_keys.push_back(key);
                // throw "[ERROR]: Value for '" + key + "' is not set!";
            }
        }
        if (absent_keys.size() != 0) {
            std::string error_message{};
            for (auto& key : absent_keys) {
                error_message += "\n[ERROR]: Value for '" + key + "' is not set!";
            }
            throw error_message;
        }
    };
}

std::function<bool(json&)> Add::execute(const std::vector<std::string>& query) {
    std::string type_name = query[0];
    std::vector<std::string> name_chunks = split(query[1], ',');
    std::vector<std::string> value_chunks = split(query[3], ',');

    json js = deserialize(name_chunks, value_chunks);

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
