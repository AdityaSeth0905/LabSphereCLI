#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <nlohmann/json.hpp>

bool execute_command(const std::string& command, const nlohmann::json& command_dict);

#endif
