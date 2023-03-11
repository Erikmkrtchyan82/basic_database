#ifndef _utils_header_
#define _utils_header_

#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

const static std::string DEFAULT_PROMPT = ">>> ";
const static std::string EXIT_COMMANDS = "EXIT";
const static std::string PRINT_COMMAND = "p";
const static std::string REIMPORT_COMMAND = "r";

std::string prompt();
// std::vector<std::string> split(const std::string& input, char sep = ' ');
std::vector<std::string> split(const std::string& input, const std::string& sep = "");
std::string to_lower(std::string input);

std::filesystem::path get_db_path(int argc, char* argv[]);
std::filesystem::path get_scheme_path(int argc, char* argv[]);
nlohmann::json deserialize(std::vector<std::string>& keys, std::vector<std::string>& values);
bool all(const std::string& s, int (*pred)(int));

std::string print_table(const nlohmann::json&);
bool match(const std::string& type, const std::string& value);

#endif  // _utils_header_