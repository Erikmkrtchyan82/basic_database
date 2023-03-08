#include "../headers/utils.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using json = nlohmann::json;

std::vector<std::string> split(std::string input, char sep) {
    std::vector<std::string> chunks;
    std::string chunk{};

    std::for_each(input.begin(), input.end(), [&](char ch) {
        if (ch == sep && chunk != "") {
            chunks.push_back(chunk);
            chunk = "";
        } else if (ch != sep) {
            chunk += ch;
        }
    });

    if (chunk != "") chunks.push_back(chunk);

    return chunks;
}

std::string prompt() {
    std::string command;
    std::cout << DEFAULT_PROMPT;
    std::getline(std::cin, command);
    return command;
}

std::filesystem::path get_db_path(int argc, char* argv[]) {
    namespace fs = std::filesystem;
    fs::path db_path{"db.json"};
    if (argc >= 2) {
        db_path = fs::path{argv[1]};
    }
    if (!fs::exists(db_path) || fs::is_empty(db_path)) {
        std::ofstream{fs::absolute(db_path)} << "{}";
    }
    return db_path;
}

std::filesystem::path get_scheme_path(int argc, char* argv[]) {
    namespace fs = std::filesystem;
    fs::path scheme_path{"scheme.json"};
    if (argc >= 3) {
        scheme_path = fs::path{argv[2]};
    }
    if (!fs::exists(scheme_path) || fs::is_empty(scheme_path)) {
        auto error_message = "[ERROR]: " + scheme_path.string() + " does not exist or empty!\n";
        std::cout<<error_message<<"\n";
        throw error_message;
    }
    return scheme_path;
}

bool all(const std::string& s, int (*pred)(int)) {
    return std::all_of(s.begin(), s.end(), pred);
}

json deserialize(std::vector<std::string>& keys, std::vector<std::string>& values) {
    json js;
    for (int i = 0; i < keys.size(); ++i) {
        if (all(values[i], std::isdigit))
            js[keys[i]] = stoi(values[i]);
        else
            js[keys[i]] = values[i];
    }
    return js;
}

std::string print_table(const nlohmann::json& js) {
    std::stringstream table;
    for (auto& [table_name, contents] : js.items()) {
        table << " * " << table_name << "\n\n\t";
        if (contents[0].size() != 0) {
            for (auto obj : contents[0].items()) {
                table << "| " << std::left << std::setw(10) << obj.key();
            }
        }
        for (auto& content : contents) {
            table << "\n\t";
            for (auto obj : content.items()) {
                table << "| " << std::left << std::setw(10) << obj.value().dump();
            }
        }
        table << "\n";
    }
    return table.str();
}