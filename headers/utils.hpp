#ifndef _utils_header_
#define _utils_header_

#include <vector>
#include <string>
#include <filesystem>
#include <map>

const static std::string DEFAULT_PROMPT = ">>> ";
const static std::string EXIT_COMMANDS = "EXIT";

std::string prompt();
std::vector<std::string> split(std::string input, char sep = ' ');

std::filesystem::path get_db_path(int argc, char*argv[]);

#endif // _utils_header_