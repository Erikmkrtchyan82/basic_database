#include <filesystem>
#include <fstream>

#include "../headers/connection.hpp"
#include "../headers/utils.hpp"

#include <iostream>
Connection::Connection(const fs::path& path) {
    this->_db_path = path;
    this->_database = json::parse(std::ifstream(path));
}

Connection::~Connection() {
    std::ofstream(this->_db_path) << this->_database.dump(4);
}

bool Connection::add_new_operation(operation_ptr&& op) {
    auto will_add = std::find_if(this->_operations.begin(), this->_operations.end(),
                                [&op](operation_ptr& op1){
                                    return op1->get_name() == op->get_name();
                                }) == this->_operations.end();
    if (will_add) {
        std::cout<<"[INFO] Adding "<<op->get_name()<<" operation\n";
        this->_operations.emplace_back(std::move(op));
    }
    return will_add;
}

// bool Connection::add_new_type(type_ptr&& tp){
//     this->_types.emplace_back(std::move(tp));
//     return true;
// }

int Connection::execute(const std::string& query) {
    auto query_chunks = split(query);
    const std::string& operation_name = query_chunks[0];

    auto operation = std::find_if( this->_operations.begin(), 
                                this->_operations.end(), 
                                [operation_name](const operation_ptr& op) {
                                    return op->get_name() == operation_name;
                                });
    int status = 0;
    if (operation != this->_operations.end()) {
        status = (*operation)->execute({query_chunks.begin() + 1, query_chunks.end()})(this->_database);
    }
    return status;
}


