#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../headers/add_operation.hpp"
#include "../headers/connection.hpp"
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
    // conn.add_new_operation(std::make_unique<Select>());

    do {
        command = prompt();
        if (all(command, [](int c) -> int { return c == ' '; })) continue;
        if (command == EXIT_COMMANDS) break;
        if (command == "p")
            std::cout << print_table(conn.get_db()) << std::endl;

        conn.execute(command);

        /*

        Connection conn{"<db_path>"};
        conn.execute("<command>");
            |
            |
            \--> vector<Operations> operations;
                 find operation that name is command[0], and call it's execute
        */

        /*
        ADD Lab.(name) VALUES "abcd";     (defaults: str -> N/A, int -> 0)
        SELECT LAB WHERE name=lab1"
        */

    } while (true);

    return 0;
}
