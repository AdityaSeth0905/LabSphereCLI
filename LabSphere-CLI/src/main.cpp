#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include "commands.hpp"
#include "sensor_data.hpp"
#include "kafka_integration.hpp"
#include "run_compiler.hpp"
#include "os_capabilities.hpp"
#include "log_util.hpp" // Include log utility header

// For convenience
using json = nlohmann::json;

json command_dict;

// Function to load the command mapping from a JSON file
void load_command_dict(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) {
        std::cerr << "Could not open the command dictionary file." << std::endl;
        LogUtil::logChange("src", "Could not open the command dictionary file.");
        return;
    }

    file >> command_dict;
}

// Function to execute a command and log input/output
bool execute_command(const std::string& command) {
    LogUtil::logChange("src", "User input: " + command);
    
    // Check if the command exists in the JSON dictionary
    if (command_dict.contains(command)) {
        // Simulate the execution of the command
        std::string output = "Executing: " + command_dict[command].get<std::string>();
        std::cout << output << std::endl;
        LogUtil::logChange("src", output);

        // Simulate a delay for execution
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::string completionMessage = "Completed: " + command;
        std::cout << completionMessage << std::endl;
        LogUtil::logChange("src", completionMessage);
        
        return true; // Command executed successfully
    } else {
        std::string errorMessage = "Unknown command: " + command;
        std::cout << errorMessage << std::endl;
        LogUtil::logChange("src", errorMessage);
        return false; // Command not found
    }
}

int main() {
    std::string command;
    std::string current_directory = "C:\\Users\\adity>";  // Windows-like prompt

    // Load command dictionary from JSON
    load_command_dict("../config/commands.json");

    std::cout << "Welcome to LabSphere CLI\n";
    std::cout << "Default background color: dark\n";
    
    while (true) {
        std::cout << current_directory << " ";
        std::getline(std::cin, command);
        
        if (command == "exit") {
            std::cout << "Exiting LabSphere CLI...\n";
            LogUtil::logChange("src", "Exiting LabSphere CLI...");
            break;
        }

        // Execute the command and log input/output
        execute_command(command);
    }

    return 0;
}
