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
#if __has_include(<format>)
    #include <format>
    using std::format;
    using std::vformat;
    using std::make_format_args;
#else
    #include <fmt/core.h>
    using fmt::format;
    using fmt::vformat;
    using fmt::make_format_args;
#endif

#if __has_include(<stacktrace>) && __cpp_lib_stacktrace >= 202011L
#include <stacktrace>
#endif

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

private:
    /**
     * @brief Get the stack trace
     * @return std::string The stack trace
     */
    std::string stack_trace(uint8_t indent = 0) const;

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
        std::string message = vformat(std::forward<std::string_view>(format), make_format_args(args...));
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
constexpr const char* to_string(Logger::LogLevel level);

} // namespace OwLog