#ifndef LOG_UTIL_HPP
#define LOG_UTIL_HPP

#include <string>

class LogUtil {
public:
    static void logChange(const std::string& directory, const std::string& changeDetails);
};

#endif // LOG_UTIL_HPP
