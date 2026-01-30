#include "WindowsPlatform.h"

#include <chrono>
#include <iostream>

void WindowsPlatform::startup() {
    // Windows-specific initialization code
    
    LOG_DEBUG("Win32 platform started up successfully.");
}

void WindowsPlatform::shutdown() {
    // Windows-specific cleanup code
    
    LOG_DEBUG("Win32 platform shut down successfully.");
}

double WindowsPlatform::getRunningTime() {
    static auto startTime = std::chrono::steady_clock::now();
    return std::chrono::duration<double>(std::chrono::steady_clock::now() - startTime).count();
}

double WindowsPlatform::getSystemTime() {
    return std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
}

double WindowsPlatform::getDeltaTime() {
    static bool firstCall = true;
    static auto previous = std::chrono::steady_clock::now();

    auto const current = std::chrono::steady_clock::now();
    double const deltaTime = firstCall ? 0.0 : std::chrono::duration<double>(current - previous).count();

    firstCall = false;
    previous = current;
    return deltaTime;
}

void WindowsPlatform::consoleWrite(const LogLevel logLevel, const std::string& message) {

    // Choose output stream based on log level
    std::ostream &out = (logLevel == LogLevel::Fatal || logLevel == LogLevel::Error) ? std::cerr : std::cout;

    // Write to the console with color coding
    out << message << std::endl;
}