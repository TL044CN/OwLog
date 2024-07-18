/**
 * @file Logger.hpp
 * @author TL044CN
 * @brief Logger class header file
 * @version 0.1
 * @date 2024-07-18
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include "Sink.hpp"

#include <memory>
#include <string_view>
#include <format>

namespace OwLog {

/**
 * @brief Logger class
 *
 */
class Logger {
public:
    enum class Level {
        Trace = 0b000,
        Info = 0b001,
        Warning = 0b010,
        Error = 0b100
    };

private:
    std::weak_ptr<Sink> mSink;
    Level mFilterLevel = Level::Info;
    Level mLevel = Level::Info;

public:
    Logger(std::weak_ptr<Sink> outputSink): mSink(outputSink) {};
    ~Logger();

    /**
     * @brief Set the filter level
     *
     * @param level the level
     */
    void setFilterLevel(Level level);

    /**
     * @brief Set the default level
     *
     * @param level the level
     */
    void setDefaultLevel(Level level);

private:
    void log(Level level, std::string_view message);

public:
    /**
     * @brief Log a message
     *
     * @tparam Args the type of the arguments
     * @param format the format of the message
     * @param args the arguments
     */
    template<typename... Args>
    void trace(std::string_view format, Args&&... args) {
        std::string message = std::vformat(std::forward<std::string_view>(format), std::make_format_args(args...));
        trace(message);
    }

    /**
     * @brief Log a message
     *
     * @tparam Args the type of the arguments
     * @param format the format of the message
     * @param args the arguments
     */
    void trace(std::string_view message);

    /**
     * @brief Log a message
     *
     * @tparam Args the type of the arguments
     * @param format the format of the message
     * @param args the arguments
     */
    template<typename... Args>
    void info(std::string_view format, Args&&... args) {
        std::string message = std::vformat(std::forward<std::string_view>(format), std::make_format_args(args...));
        info(message);
    }

    /**
     * @brief Log a message
     *
     * @param message the message
     */
    void info(std::string_view message);

    /**
     * @brief Log a warning message
     *
     * @tparam Args the type of the arguments
     * @param format the format of the message
     * @param args the arguments
     */
    template<typename... Args>
    void warn(std::string_view format, Args&&... args) {
        std::string message = std::vformat(std::forward<std::string_view>(format), std::make_format_args(args...));
        warn(message);
    }

    /**
     * @brief Log a warning message
     *
     * @param message the message
     */
    void warn(std::string_view message);

    /**
     * @brief Log an error message
     *
     * @tparam Args the type of the arguments
     * @param format the format of the message
     * @param args the arguments
     */
    template<typename... Args>
    void error(std::string_view format, Args&&... args) {
        std::string message = std::vformat(std::forward<std::string_view>(format), std::make_format_args(args...));
        error(message);
    }

    /**
     * @brief Log an error message
     *
     * @param message the message
     */
    void error(std::string_view message);

};

/**
 * @brief Convert a level to a string
 *
 * @param level the level
 * @return std::string the string
 */
std::string to_string(Logger::Level level);

}
