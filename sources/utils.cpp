#include <iostream>
#include <fstream>
#include "../headers/utils.hpp"

std::vector<std::string> split(std::string input) {
    std::vector<std::string> chunks;
    std::string chunk{};
    
    for( char ch:input) {
        if (ch == ' ' && chunk != "") {
            chunks.push_back(chunk);
            chunk = "";
        } else if (ch != ' '){
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

