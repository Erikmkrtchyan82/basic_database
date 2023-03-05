#ifndef _connection_hpp_
#define _connection_hpp_

#include <filesystem>
#include <vector>
#include <nlohmann/json.hpp>

#include "../headers/operation.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

class Connection {
public:
    Connection(const fs::path& db_path);
    int execute(const std::string& query);
    bool add_operation(Operation&& op);
private:
    json _database;
    std::vector<Operation> _operations;
};


#endif // _connection_hpp_