#include "logging.hpp"
#include <ctime>
#include <thread>
#include <sstream>
#include <iomanip>
#include <cstdint>

namespace clib
{
    Log Log::mInstance;

    Log::Log()
    {
        const char *logLevelFromEnv = std::getenv("CLIB_LOG_LEVEL");
        if (!logLevelFromEnv)
        {
            std::cout << "no log level set. falling back to defaul: INFO\n";
            mCurrentLevel = LogLevel::INFO;
        }
        else
        {
            mCurrentLevel = parse_log_level(logLevelFromEnv);
        }
    }

    Log::~Log()
    {
        log(LogLevel::DEBUG, "destroying singleton for logging");
    }

    Log &Log::get_instance()
    {
        return mInstance; // eager implementation singleton
    }

    std::string get_date_time()
    {
        time_t timestamp = time(nullptr);
        struct tm localTime;
        localtime_r(&timestamp, &localTime);
        char buffer[64];
        strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S]", &localTime);
        return std::string(buffer);
    }

    std::string get_thread()
    {
        std::thread::id id = std::this_thread::get_id();
        std::ostringstream oss;
        oss << "[Thread " << id << "]";
        return oss.str();
    }

    void Log::log(const LogLevel &aLevel, const std::string &aMessage)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        if (mCurrentLevel > aLevel)
        {
            return;
        }

        const std::string message = get_date_time() + log_level_to_string(aLevel) + get_thread() + ": " + aMessage;
        write_to_console(message);
    }

    void Log::set_log_level(const LogLevel &aLevel)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        mCurrentLevel = aLevel;
    }

    std::string Log::log_level_to_string(const LogLevel &aLevel)
    {
        switch (aLevel)
        {
        case LogLevel::DEBUG:
            return "[DEBUG]";
        case LogLevel::INFO:
            return "[INFO]";
        case LogLevel::WARNING:
            return "[WARNING]";
        case LogLevel::ERROR:
            return "[ERROR]";

        default:
            return "[UNKNOWN LOG LEVEL]";
        }
    }
    void Log::write_to_console(const std::string &aMessage)
    {
        std::cout << aMessage << "\n";
    }
    
    LogLevel parse_log_level(const char *aLevel)
    {
        std::string lLevel(aLevel);
            
        if (lLevel == "DEBUG")
            return LogLevel::DEBUG;
        if (lLevel == "INFO")
            return LogLevel::INFO;
        if (lLevel == "WARNING")
            return LogLevel::WARNING;
        if (lLevel == "ERROR")
            return LogLevel::ERROR;
        std::cout << "unknown log level: " << aLevel << ". falling back to default INFO\n";
        return LogLevel::INFO;
    }

    std::string pointer_to_string(void *ptr)
{
    std::ostringstream oss;
    oss << "0x" << std::hex << std::setw(sizeof(void*) * 2) << std::setfill('0') << reinterpret_cast<std::uintptr_t>(ptr);
    return oss.str();
}
}