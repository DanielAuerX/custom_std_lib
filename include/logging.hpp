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

    std::string get_prefix(const std::string &aLevel);
    LogLevel parse_log_level(const char *aLevel);
    std::string pointer_to_string(void *ptr);

    class Log
    {
    public:
        static Log &get_instance();
        static bool &is_initialized();
        void log(const LogLevel &aLevel, const std::string &aMessage);
        void set_log_level(const LogLevel &aLevel);

    private:
        Log();
        ~Log();

        std::string log_level_to_string(const LogLevel &aLevel);
        void write_to_console(const std::string &aMessage);
        std::string get_prefix(const LogLevel &aLevel);
        std::string get_date_time();
        std::string get_thread();

        // TODO write to file

        static Log mInstance;
        static bool mIsInitialized;
        LogLevel mCurrentLevel;
        std::mutex mMutex;
    };
}
