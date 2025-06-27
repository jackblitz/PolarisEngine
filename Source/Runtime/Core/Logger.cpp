#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <mutex>

#ifdef _WIN32
#include <windows.h>
#elif defined(__APPLE__)
#include <os/log.h>
#elif defined(__ANDROID__)
#include <android/log.h>
#endif

namespace polaris {

class Logger::Impl {
public:
    std::ofstream logFile;
    std::mutex logMutex;
    LogLevel currentLevel = LogLevel::INFO;
    bool initialized = false;
    
    std::string getTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;
        
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
        return ss.str();
    }
    
    std::string getLevelString(LogLevel level) {
        switch (level) {
            case LogLevel::TRACE: return "TRACE";
            case LogLevel::DEBUG_LEVEL: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARN: return "WARN";
            case LogLevel::CRITICAL: return "CRITICAL";
            case LogLevel::ERROR_LOG: return "ERROR";
            default: return "UNKNOWN";
        }
    }
    
    void logToConsole(const std::string& message, LogLevel level) {
        std::lock_guard<std::mutex> lock(logMutex);
        
        std::string timestamp = getTimestamp();
        std::string levelStr = getLevelString(level);
        
        std::string formattedMessage = "[" + timestamp + "] [" + levelStr + "] " + message;
        
        // Platform-specific console output
#ifdef _WIN32
        // Windows: Use colored output if available
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // White
        
        switch (level) {
            case LogLevel::ERROR_LOG:
            case LogLevel::CRITICAL:
                color = FOREGROUND_RED | FOREGROUND_INTENSITY;
                break;
            case LogLevel::WARN:
                color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                break;
            case LogLevel::INFO:
                color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                break;
            case LogLevel::DEBUG_LEVEL:
                color = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                break;
        }
        
        SetConsoleTextAttribute(hConsole, color);
        std::cout << formattedMessage << std::endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        
#elif defined(__APPLE__)
        // macOS: Use os_log for system integration
        os_log_type_t logType = OS_LOG_TYPE_DEFAULT;
        switch (level) {
            case LogLevel::ERROR_LOG:
            case LogLevel::CRITICAL:
                logType = OS_LOG_TYPE_ERROR;
                break;
            case LogLevel::WARN:
                logType = OS_LOG_TYPE_DEFAULT;
                break;
            case LogLevel::INFO:
                logType = OS_LOG_TYPE_INFO;
                break;
            case LogLevel::DEBUG_LEVEL:
                logType = OS_LOG_TYPE_DEBUG;
                break;
        }
        os_log_with_type(OS_LOG_DEFAULT, logType, "%{public}s", formattedMessage.c_str());
        
#elif defined(__ANDROID__)
        // Android: Use android_log
        android_LogPriority priority = ANDROID_LOG_INFO;
        switch (level) {
            case LogLevel::ERROR_LOG:
            case LogLevel::CRITICAL:
                priority = ANDROID_LOG_ERROR;
                break;
            case LogLevel::WARN:
                priority = ANDROID_LOG_WARN;
                break;
            case LogLevel::INFO:
                priority = ANDROID_LOG_INFO;
                break;
            case LogLevel::DEBUG_LEVEL:
                priority = ANDROID_LOG_DEBUG;
                break;
        }
        __android_log_print(priority, "Vega42", "%s", formattedMessage.c_str());
        
#else
        // Linux/Other: Standard console output
        std::cout << formattedMessage << std::endl;
#endif
    }
    
    void logToFile(const std::string& message, LogLevel level) {
        if (!logFile.is_open()) return;
        
        std::lock_guard<std::mutex> lock(logMutex);
        
        std::string timestamp = getTimestamp();
        std::string levelStr = getLevelString(level);
        
        logFile << "[" + timestamp + "] [" + levelStr + "] " + message << std::endl;
        logFile.flush();
    }
};

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::initialize(const std::string& logFile) {
    if (m_initialized) return;
    
    m_impl = std::make_unique<Impl>();
    
    // Open log file
    m_impl->logFile.open(logFile, std::ios::app);
    if (!m_impl->logFile.is_open()) {
        std::cerr << "Failed to open log file: " << logFile << std::endl;
    }
    
    m_initialized = true;
    info("Logger initialized");
}

void Logger::shutdown() {
    if (!m_initialized) return;
    
    info("Logger shutting down");
    
    if (m_impl->logFile.is_open()) {
        m_impl->logFile.close();
    }
    
    m_impl.reset();
    m_initialized = false;
}

void Logger::setLogLevel(LogLevel level) {
    if (m_impl) {
        m_impl->currentLevel = level;
    }
    m_currentLevel = level;
}

void Logger::trace(const std::string& message) {
    if (m_currentLevel <= LogLevel::TRACE && m_impl) {
        m_impl->logToConsole(message, LogLevel::TRACE);
        m_impl->logToFile(message, LogLevel::TRACE);
    }
}

void Logger::debug(const std::string& message) {
    if (m_currentLevel <= LogLevel::DEBUG_LEVEL && m_impl) {
        m_impl->logToConsole(message, LogLevel::DEBUG_LEVEL);
        m_impl->logToFile(message, LogLevel::DEBUG_LEVEL);
    }
}

void Logger::info(const std::string& message) {
    if (m_currentLevel <= LogLevel::INFO && m_impl) {
        m_impl->logToConsole(message, LogLevel::INFO);
        m_impl->logToFile(message, LogLevel::INFO);
    }
}

void Logger::warn(const std::string& message) {
    if (m_currentLevel <= LogLevel::WARN && m_impl) {
        m_impl->logToConsole(message, LogLevel::WARN);
        m_impl->logToFile(message, LogLevel::WARN);
    }
}

void Logger::error(const std::string& message) {
    if (m_currentLevel <= LogLevel::ERROR_LOG && m_impl) {
        m_impl->logToConsole(message, LogLevel::ERROR_LOG);
        m_impl->logToFile(message, LogLevel::ERROR_LOG);
    }
}

void Logger::critical(const std::string& message) {
    if (m_currentLevel <= LogLevel::CRITICAL && m_impl) {
        m_impl->logToConsole(message, LogLevel::CRITICAL);
        m_impl->logToFile(message, LogLevel::CRITICAL);
    }
}

void Logger::logToConsole(const std::string& message, LogLevel level) {
    if (m_impl) {
        m_impl->logToConsole(message, level);
    }
}

void Logger::logToFile(const std::string& message, LogLevel level) {
    if (m_impl) {
        m_impl->logToFile(message, level);
    }
}

} // namespace polaris 