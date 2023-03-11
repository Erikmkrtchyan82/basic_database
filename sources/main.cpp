#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../headers/add_operation.hpp"
#include "../headers/connection.hpp"
#include "../headers/delete_operation.hpp"
#include "../headers/select_operation.hpp"
#include "../headers/utils.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    std::string command;
    fs::path db_path = get_db_path(argc, argv);
    fs::path scheme_path = get_scheme_path(argc, argv);
    std::vector<std::string> chunks;

    Connection conn(db_path, scheme_path);
    conn.add_new_operation(std::make_unique<Add>());
    conn.add_new_operation(std::make_unique<Select>());
    conn.add_new_operation(std::make_unique<Delete>());

    do {
        command = prompt();
        if (all(command, [](int c) -> int { return c == ' '; }))
            continue;
        else if (command == EXIT_COMMANDS)
            break;
        else if (command == PRINT_COMMAND)
            std::cout << print_table(conn.get_db()) << std::endl;
        else if (command == REIMPORT_COMMAND)
            conn.reimport();
        else
            conn.execute(command);

    } while (true);

    return 0;
}
