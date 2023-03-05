#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>

#include "../headers/utils.hpp"
#include "../headers/group.hpp"
#include "../headers/laboratory.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    std::string command;
    fs::path db_path = get_db_path(argc, argv);
    std::vector<std::string> chunks;
    do
    {
        command = prompt();
        if (command == EXIT_COMMANDS) break;

        chunks = split(command);


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
       
       */



    } while (true);

    return 0;
}
