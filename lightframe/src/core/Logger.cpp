#include "Logger.h"

#include "../platform/Platform.h"

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>


void Logger::log(LogLevel level, const std::string& message) {

    std::stringstream ss;
    ss << timestamp();
    ss << " [" << logLevelToString(level) << "] " << message;

    Platform::get()->consoleWrite(level, ss.str());
}

std::string Logger::timestamp() {
    // TODO: Make this non-allocating

    // TODO: Get this from Platform.get()->getTime() and format accordingly
    const auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    const auto ms = duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::tm tm{};
#ifdef LF_PLATFORM_WINDOWS
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
        << '.' << std::setw(3) << std::setfill('0') << ms.count();

    return oss.str();
}

const char* Logger::logLevelToString(const LogLevel level) {
    switch (level) {
        case LogLevel::Fatal: return "FATAL";
        case LogLevel::Error: return "ERROR";
        case LogLevel::Warning:  return "WARNING";
        case LogLevel::Info:  return "INFO";
        case LogLevel::Debug: return "DEBUG";
        case LogLevel::Trace: return "TRACE";
        default:    return "";
    }
}