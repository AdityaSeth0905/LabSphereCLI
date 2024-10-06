#include "log_util.hpp"
#include <fstream>
#include <ctime>

void LogUtil::logChange(const std::string& directory, const std::string& changeDetails) {
    std::string logFileName = "logs/common_changes.log"; // Common log file
    std::ofstream logFile(logFileName, std::ios_base::app);
    std::time_t now = std::time(nullptr);
    logFile << std::ctime(&now) << " - [" << directory << "] " << changeDetails << "\n";
    logFile.close();
    
    // Additional logs for specific directories
    std::string specificLogFileName;
    if (directory == "src") {
        specificLogFileName = "logs/src_changes.log";
    } else if (directory == "include") {
        specificLogFileName = "logs/include_changes.log";
    } else {
        specificLogFileName = "logs/other_changes.log";
    }
    
    std::ofstream specificLogFile(specificLogFileName, std::ios_base::app);
    specificLogFile << std::ctime(&now) << " - " << changeDetails << "\n";
    specificLogFile.close();
}
