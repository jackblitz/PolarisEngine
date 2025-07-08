#ifndef POLARIS_LOGGER_H
#define POLARIS_LOGGER_H

#include <memory>
#include <string>

namespace polaris {

enum class LogLevel {
    TRACE = 0,
    DEBUG_LEVEL = 1,  // Renamed from DEBUG to avoid macro conflicts
    INFO = 2,
    WARN = 3,
    ERROR_LOG = 4,
    CRITICAL = 5
};

class Logger {
public:
    static Logger& getInstance();
    
    void initialize(const std::string& logFile = "vega42.log");
    void shutdown();
    
    void setLogLevel(LogLevel level);
    
    // Logging methods
    void trace(const std::string& message);
    void debug(const std::string& message);
    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);
    void critical(const std::string& message);
    
    // Platform-specific methods
    void logToConsole(const std::string& message, LogLevel level);
    void logToFile(const std::string& message, LogLevel level);
    
private:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
    class Impl;
    std::unique_ptr<Impl> m_impl;
    
    bool m_initialized = false;
    LogLevel m_currentLevel = LogLevel::INFO;
};

// Convenience macros
#define LOG_TRACE(msg) polaris::Logger::getInstance().trace(msg)
#define LOG_DEBUG(msg) polaris::Logger::getInstance().debug(msg)
#define LOG_INFO(msg) polaris::Logger::getInstance().info(msg)
#define LOG_WARN(msg) polaris::Logger::getInstance().warn(msg)
#define LOG_ERROR(msg) polaris::Logger::getInstance().error(msg)
#define LOG_CRITICAL(msg) polaris::Logger::getInstance().critical(msg)

// Conditional logging
#define LOG_DEBUG_IF(condition, msg) if(condition) LOG_DEBUG(msg)
#define LOG_INFO_IF(condition, msg) if(condition) LOG_INFO(msg)

} // namespace polaris

#endif // POLARIS_LOGGER_H 