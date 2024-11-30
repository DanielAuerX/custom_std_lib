#pragma once

#include <iostream>
#include <mutex>
#include <string>

namespace clib
{
    enum class LogLevel
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    LogLevel parse_log_level(const char* aLevel);
    std::string pointer_to_string(void* ptr);

    class Log
    {
    public:
        static Log &get_instance();
        void log(const LogLevel &level, const std::string &aMessage);
        void set_log_level(const LogLevel &aLevel);

    private:
        Log();
        ~Log();

        std::string log_level_to_string(const LogLevel &aLevel);
        void write_to_console(const std::string &aMessage);
        // TODO write to file

        static Log mInstance;
        LogLevel mCurrentLevel;
        std::mutex mMutex;
    };
}
