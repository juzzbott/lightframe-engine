/**
 * @file Platform.h
 * @author Justin McKay
 * @brief An interface used by concrete implementations to define a Platform class.
 * @date 2025-12-20
 */

#pragma once

#include "core/Logger.h"

#include <memory>


class Platform {
public:
    virtual ~Platform() = default;

    /**
     * @brief Initializes the platform-specific components
     * 
     * This method performs platform-specific initialization tasks
     * such as setting up the graphics context, input systems, and
     * other necessary platform resources.
     */
    virtual void startup() = 0;

    /**
     * @brief Cleans up and releases platform-specific resources
     * 
     * This method performs platform-specific cleanup tasks
     * such as destroying the graphics context, releasing input
     * resources, and freeing other platform-allocated resources.
     */
    virtual void shutdown() = 0;

    /**
     * @brief Retrieves the current time from the platform
     *
     * This method should return the current time in seconds
     * since the application started or since a defined epoch.
     */
    virtual double getRunningTime() = 0;
    
    /**
     * @brief Retrieves the current system time
     *
     * This method should return the current system time in seconds since 
     * the unix epoch.
     */
    virtual double getSystemTime() = 0;

    /**
     * @brief Retrieves the delta time since the last call
     *
     * This method should return the time elapsed in seconds
     * since the last invocation of this method. It is typically
     * used for frame timing and animation updates.
     */
    virtual double getDeltaTime() = 0;

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
    virtual void consoleWrite(LogLevel logLevel, const std::string& message) = 0;

    /**
     * @brief Singleton method to get a platform-specific instance
     * 
     * Returns a unique pointer to a platform-specific singleton
     * implementation of the Platform interface. The concrete platform
     * type is determined at runtime based on the current operating system.
     * 
     * @return Platform* A pointer to the platform instance
     */
    static Platform* get();

};
