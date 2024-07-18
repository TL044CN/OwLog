/**
 * @file Logger.cpp
 * @author TL044CN
 * @brief Logger class implementation
 * @version 0.1
 * @date 2024-07-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Logger.hpp"

namespace OwLog {

Logger::Logger(std::shared_ptr<Sink> sink)
    : mSink(sink) {}


void Logger::set_filter_level(LogLevel level) {
    mFilterLevel = level;
}

void Logger::set_default_level(LogLevel level) {
    mDefaultLevel = level;
}

void Logger::log(std::string_view message) {
    log(mDefaultLevel, message);
}

void Logger::log(LogLevel level, std::string_view message) {
    if (level < mFilterLevel) {
        return;
    }

    mSink->write(std::format("[{}] {}\n", to_string(level), message));
}

std::string to_string(Logger::LogLevel level) {
    switch (level) {
    case Logger::LogLevel::TRACE:
        return "TRACE";
    case Logger::LogLevel::DEBUG:
        return "DEBUG";
    case Logger::LogLevel::INFO:
        return "INFO";
    case Logger::LogLevel::WARN:
        return "WARN";
    case Logger::LogLevel::ERROR:
        return "ERROR";
    case Logger::LogLevel::FATAL:
        return "FATAL";
    default:
        return "UNKNOWN";
    }
}

} // namespace OwLog