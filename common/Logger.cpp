#include <iostream>
#include <sstream>
#include <string>

#include "common/Logger.h"

using namespace NetworkAnalytical;

void Logger::log(LOGLEVEL level, const std::string& message, const char* functionName)
{
    // Only log if the message's level is higher than or equal to the current level
    // Change currentLevel in Logger.h if you want to change the logging level
    if (level >= currentLevel) {
        std::string prefix;
        switch (level) {
            case LOGLEVEL::INFO:
                prefix = "INFO";
                break;
            case LOGLEVEL::DEBUG:
                prefix = "DEBUG";
                break;
            default:
                prefix = "UNKNOWN";
                break;
        }

        std::cout << "ANOC: " << functionName << ": " << prefix << ": " << message << std::endl;
    }
}

