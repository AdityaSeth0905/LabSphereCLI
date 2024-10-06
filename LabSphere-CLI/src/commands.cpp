#include "commands.hpp"
#include <cstdlib>
#include <iostream>
#include <nlohmann/json.hpp>

bool execute_command(const std::string& command, const nlohmann::json& command_dict) {
    std::string system_command;

    // Check if the command exists in the JSON dictionary
    if (command_dict.contains(command)) {
        system_command = command_dict[command].get<std::string>();
    } else {
        system_command = command;
    }

    int result = std::system(system_command.c_str());
    return result == 0;
}
