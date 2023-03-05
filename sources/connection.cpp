#include <filesystem>
#include <fstream>

#include "../headers/connection.hpp"
#include "../headers/utils.hpp"


Connection::Connection(const fs::path& path) {
    this->_database = json::parse(std::ifstream(path));
}

int Connection::execute(const std::string& query) {
    auto query_chunks = split(query);
    const std::string& operation_name = query_chunks[0];

    auto operation = std::find_if( this->_operations.begin(), 
                                this->_operations.end(), 
                                [operation_name](const Operation& op) {
                                    return op.NAME == operation_name;
                                });
    int status = 0;
    if (operation != this->_operations.end()) {
        status = operation->execute({query_chunks.begin() + 1, query_chunks.end()});
    }
    return status;
}


