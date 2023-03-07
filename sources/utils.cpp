#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "../headers/utils.hpp"

using json = nlohmann::json;

std::vector<std::string> split(std::string input, char sep) {
    std::vector<std::string> chunks;
    std::string chunk{};
    
    for( char ch:input) {
        if (ch == sep && chunk != "") {
            chunks.push_back(chunk);
            chunk = "";
        } else if (ch != sep){
            chunk += ch;
        }
    }

    if(chunk != "")
        chunks.push_back(chunk);

    return chunks;
}

std::string prompt(){
    std::string command;
    std::cout << DEFAULT_PROMPT;
    std::getline(std::cin, command);
    return command;
}

std::filesystem::path get_db_path(int argc, char*argv[]) {
    namespace fs = std::filesystem;
    fs::path db_path{"db.json"};
    if (argc >= 2){
        db_path = fs::path{argv[1]};
    }
    if (!fs::exists(db_path) || fs::is_empty(db_path)) {
        std::ofstream{fs::absolute(db_path)} << "{}";
    }
    return db_path;
}

bool all(const std::string& s, int(*pred)(int)) {
    return std::all_of(s.begin(), s.end(), pred);
}

json deserialize(std::vector<std::string>& keys, std::vector<std::string>& values) {
    json js;
    for(int i = 0; i < keys.size(); ++i) {
        if(all(values[i], std::isdigit))
            js[keys[i]] = stoi(values[i]);
        else
            js[keys[i]] = values[i];
    }
    return js;
}