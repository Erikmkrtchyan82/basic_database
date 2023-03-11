#ifndef _connection_hpp_
#define _connection_hpp_

#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../headers/operation.hpp"

using json = nlohmann::json;

namespace fs = std::filesystem;

class Connection {
   public:
    Connection(const fs::path&, const fs::path&);
    void reimport();
    int execute(const std::string&);
    bool add_new_operation(operation_ptr&&);
    ~Connection();
    json get_db();

   private:
    fs::path _db_path;
    fs::path _db_scheme;
    json _database;
    json _scheme;
    std::vector<operation_ptr> _operations;
};

#endif  // _connection_hpp_