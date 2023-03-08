#ifndef _utils_header_
#define _utils_header_

#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

const static std::string DEFAULT_PROMPT = ">>> ";
const static std::string EXIT_COMMANDS = "EXIT";

std::string prompt();
std::vector<std::string> split(std::string input, char sep = ' ');

std::filesystem::path get_db_path(int argc, char* argv[]);
std::filesystem::path get_scheme_path(int argc, char* argv[]);
nlohmann::json deserialize(std::vector<std::string>& keys, std::vector<std::string>& values);
bool all(const std::string& s, int (*pred)(int));

std::string print_table(const nlohmann::json&);

#endif  // _utils_header_