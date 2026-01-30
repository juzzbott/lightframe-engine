/**
 * @file LinuxPlatform.h
 * @author Justin McKay
 * @brief [...add brief description...]
 * @date 2025-12-20
 */

#pragma once

#include "Platform.h"

class LinuxPlatform final : public Platform {
public:
    
    void startup() override;
    void shutdown() override;

    /**
     * @brief Return seconds since startup using a monotonic high-resolution clock.
     *
     * @return double seconds since first call (or since program start).
     */
    double getRunningTime() override;

    /**
     * @brief Return delta seconds since last call (suitable for frame deltaTime).
     *
     * This updates the internal previous time and returns the elapsed seconds
     * between consecutive calls, avoiding large absolute times and loss of precision.
     *
     * @return double seconds elapsed since previous call
     */
    double getDeltaTime() override;
    
    /**
     * @brief Retrieves the current system time
     *
     * This method should return the current system time in seconds since 
     * the unix epoch.
     */
    double getSystemTime() override;

    /**
     * @brief Writes a log message to the platform-specific console
     *
     * This method handles writing log messages to the console
     * or terminal in a platform-specific manner. It takes the
     * log level and message as parameters.
     *
     * @param logLevel The severity level of the log message
     * @param message The log message to be written
     */
    void consoleWrite(LogLevel logLevel, const std::string& message) override;

};