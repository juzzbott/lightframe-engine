#include "LinuxPlatform.h"

#include "debug/Assertions.h"

#include <chrono>
#include <iostream>

void LinuxPlatform::startup() {
    // Linux-specific initialization code
    
    LOG_DEBUG("Linux platform started up successfully.");
    
}

void LinuxPlatform::shutdown() {
    // Linux-specific cleanup code
    
    LOG_DEBUG("Linux platform shut down successfully.");
}

double LinuxPlatform::getRunningTime() {
    static auto startTime = std::chrono::steady_clock::now();
    return std::chrono::duration<double>(std::chrono::steady_clock::now() - startTime).count();
}

double LinuxPlatform::getSystemTime() {
    return std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
}

double LinuxPlatform::getDeltaTime() {
    static bool firstCall = true;
    static auto previous = std::chrono::steady_clock::now();

    auto const current = std::chrono::steady_clock::now();
    double const deltaTime = firstCall ? 0.0 : std::chrono::duration<double>(current - previous).count();

    firstCall = false;
    previous = current;
    return deltaTime;
}

void LinuxPlatform::consoleWrite(const LogLevel logLevel, const std::string& message) {

    // Choose output stream based on log level
    std::ostream &out = (logLevel == LogLevel::Fatal || logLevel == LogLevel::Error) ? std::cerr : std::cout;

    // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
    const std::string color_strings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};

    // Write to the console with color coding
    out << "\033[" << color_strings[static_cast<int>(logLevel)] << "m" << message << "\033[0m" << std::endl;
}