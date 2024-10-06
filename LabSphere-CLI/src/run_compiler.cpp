 
#include "run_compiler.hpp"
#include <iostream>
#include <cstdlib>

void run_compiler(const std::string& language, const std::string& filename) {
    std::string command;

    if (language == "c") {
        command = "gcc " + filename + " -o output && ./output";
    } else if (language == "cpp") {
        command = "g++ " + filename + " -o output && ./output";
    } else if (language == "java") {
        command = "javac " + filename + " && java " + filename.substr(0, filename.find_last_of('.'));
    } else if (language == "python") {
        command = "python " + filename;
    } else {
        std::cout << "Unknown language: " << language << std::endl;
        return;
    }

    std::system(command.c_str());
}
