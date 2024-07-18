/**
 * @file Logger.hpp
 * @author TL044CN
 * @brief Logger class declaration
 * @version 0.1
 * @date 2024-07-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "Sink.hpp"
#include <memory>
#include <format>

namespace OwLog {

/**
 * @brief Logger class
 */
class Logger {
public:
    /**
     * @brief Log levels
     */
    enum class LogLevel {
        TRACE,      ///< Trace level
        DEBUG,      ///< Debug level
        INFO,       ///< Info level
        WARN,       ///< Warning level
        ERROR,      ///< Error level
        FATAL       ///< Fatal level
    };

private:
    std::shared_ptr<Sink> mSink;

    LogLevel mFilterLevel = LogLevel::INFO;
    LogLevel mDefaultLevel = LogLevel::INFO;

public:
    explicit Logger(std::shared_ptr<Sink> sink);

public:

    /**
     * @brief Set the filter level
     * @details Log messages with a level less than the filter level will be ignored
     * @param level The filter level
     */
    void set_filter_level(LogLevel level);

    /**
     * @brief Set the default level
     * @details Log messages without a level will use the default level
     * @param level The default level
     */
    void set_default_level(LogLevel level);

    /**
     * @brief Log a message
     *
     * @param message The message to log
     */
    void log(std::string_view message);

    /**
     * @brief Log a message
     *
     * @param level The log level
     * @param message The message to log
     */
    void log(LogLevel level, std::string_view message);

    /**
     * @brief Log a message with a format
     *
     * @tparam Args The argument types
     * @param level The log level
     * @param format The format string
     * @param args The arguments
     */
    template <typename... Args>
    void log(LogLevel level, std::string_view format, const Args&... args) {
        std::string message = std::vformat(std::forward<std::string_view>(format), std::make_format_args(args...));
        log(level, message);
    }

    /**
     * @brief Log a message
     *
     * @tparam Args The argument types
     * @param format The format string
     * @param args The arguments
     */
    template <typename... Args>
    void log(std::string_view format, const Args&... args) {
        log(mDefaultLevel, format, args...);
    }

};

/**
 * @brief Convert a LogLevel to a string
 *
 * @param level The LogLevel to convert
 * @return std::string The string representation of the LogLevel
 */
std::string to_string(Logger::LogLevel level);

} // namespace OwLog