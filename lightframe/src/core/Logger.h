/**
 * @file Logger.h
 * @author Justin McKay
 * @brief [...add brief description...]
 * @date 2025-12-22
 */

#pragma once

#include "ObjectId.h"

#include <mutex>
#include <string>
#include <format>
#include <string_view>

enum class LogLevel : int {
    Fatal = 0,
    Error,
    Warning,
    Info,
    Debug,
    Trace
};

class Logger {
public:

    /**
     *
     * @brief Logs a pre-formatted message.
     *
     * @param level Log level.
     * @param message Preformatted message to log.
     */
    static void log(LogLevel level, const std::string& message);
    
    /**
     * @brief Logs a formatted message with compile-time format string validation.
     *
     * @tparam Args Parameter types for formatting
     * @param level Log level
     * @param fmt Format string (must be compile-time constant)
     * @param args Arguments to format into the string
     */
    template<typename... Args>
    static void log(LogLevel level, std::format_string<Args...> fmt, Args&&... args) {
        std::string formattedMsg = std::format(fmt, std::forward<Args>(args)...);
        log(level, formattedMsg);
    }
    
    /**
     * @brief Logs a formatted message with runtime format string.
     *
     * @tparam Args Parameter types for formatting
     * @param level Log level
     * @param fmt Runtime format string
     * @param args Arguments to format into the string
     */
    template<typename... Args>
    static void logRuntime(LogLevel level, std::string_view fmt, Args&&... args) {
        try {
            std::string formattedMsg = std::vformat(fmt, 
                std::make_format_args(std::forward<Args>(args)...));
            log(level, formattedMsg);
        } catch (const std::format_error& e) {
            log(
                LogLevel::Error, 
                std::format("Format error in log message: Message: '{}' - Error: {}", fmt, e.what()));
        }
    }
    
    /**
     * @brief Unified logging interface for compile-time format strings.
     * 
     * @tparam Args Parameter types for formatting
     * @param level Log level for the message
     * @param fmt Compile-time format string
     * @param args Arguments to format into the string
     */
    template<typename... Args>
    static void logUnified(LogLevel level, std::format_string<Args...> fmt, Args&&... args) {
        log(level, fmt, std::forward<Args>(args)...);
    }
    
    /**
     * @brief Unified logging interface for runtime format strings.
     * 
     * This overload handles any string-like type that is not a compile-time format string.
     * 
     * @tparam FormatType Type of the format string (must be convertible to string_view)
     * @tparam Args Parameter types for formatting
     * @param level Log level for the message
     * @param fmt Runtime format string
     * @param args Arguments to format into the string
     */
    template<typename FormatType, typename... Args>
    static void logUnified(LogLevel level, FormatType&& fmt, Args&&... args)
        requires (!std::convertible_to<FormatType, std::format_string<Args...>>) &&
                 (std::convertible_to<FormatType, std::string_view>) {
        logRuntime(level, std::string_view(fmt), std::forward<Args>(args)...);
    }

private:

    /**
     * @brief Generates a timestamp string for log entries.
     *
     * @return A string representing the current timestamp.
     */
    static std::string timestamp();

    /**
     * @brief Converts a LogLevel enum to its string representation.
     *
     * @param level The LogLevel to convert.
     * @return A string representing the LogLevel.
     */
    static const char* logLevelToString(LogLevel level);
};

#define LOG_TRACE(msg, ...) Logger::logUnified(LogLevel::Trace, msg __VA_OPT__(,) __VA_ARGS__)
#define LOG_DEBUG(msg, ...) Logger::logUnified(LogLevel::Debug, msg __VA_OPT__(,) __VA_ARGS__)
#define LOG_INFO(msg, ...) Logger::logUnified(LogLevel::Info, msg __VA_OPT__(,) __VA_ARGS__)
#define LOG_WARN(msg, ...) Logger::logUnified(LogLevel::Warning, msg __VA_OPT__(,) __VA_ARGS__)
#define LOG_ERROR(msg, ...) Logger::logUnified(LogLevel::Error, msg __VA_OPT__(,) __VA_ARGS__)
#define LOG_FATAL(msg, ...) Logger::logUnified(LogLevel::Fatal, msg __VA_OPT__(,) __VA_ARGS__)

namespace std {
    /**
     * @brief Formatter specialization for ObjectId to enable std::format support.
     */
    template<>
    struct formatter<ObjectId> : formatter<std::string> {
        /**
         * @brief Formats an ObjectId by converting it to its string representation.
         * 
         * @tparam FormatContext The format context type
         * @param id The ObjectId to format
         * @param ctx The format context
         * @return An iterator to the output
         */
        template<typename FormatContext>
        auto format(const ObjectId& id, FormatContext& ctx) const {
            return formatter<std::string>::format(id.toString(), ctx);
        }
    };
}