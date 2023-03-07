#ifndef _connection_hpp_
#define _connection_hpp_

#include <filesystem>
#include <vector>
#include <nlohmann/json.hpp>

#include "../headers/operation.hpp"
#include "../headers/type.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

class Connection {
public:
    Connection(const fs::path& db_path);
    int execute(const std::string& query);
    bool add_new_operation(operation_ptr&& op);
    // bool add_new_type(type_ptr&& tp);
    ~Connection();
    json db(){return this->_database;};
private:
    fs::path _db_path;
    json _database;
    std::vector<operation_ptr> _operations;
    // std::vector<type_ptr> _types;
};


#endif // _connection_hpp_