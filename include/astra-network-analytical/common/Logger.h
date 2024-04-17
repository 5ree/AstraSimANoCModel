#pragma once

#include <iostream>
#include <sstream>
#include <string>

// Macro for convenience
#define DEBUG(message) Logger::log(LOGLEVEL::DEBUG, message, __func__)
#define INFO(message) Logger::log(LOGLEVEL::INFO, message, __func__)
#define WARNING(message) Logger::log(LOGLEVEL::WARNING, message, __func__)

namespace NetworkAnalytical
{
    enum class LOGLEVEL {
        DEBUG,
        INFO,
        NONE
    };

    class Logger
    {
        public:
        static const LOGLEVEL currentLevel = LOGLEVEL::DEBUG;

        static void log(LOGLEVEL level, const std::string& message, const char* functionName); 
    };

} // namespace NetworkAnalytical