#include "Logger.hpp"

namespace OwLog {

Logger::~Logger() {}

void Logger::setFilterLevel(Level level) {
    mFilterLevel = level;
}

void Logger::setDefaultLevel(Level level) {
    mLevel = level;
}

void Logger::log(Level level, std::string_view message) {
    if ( mSink.expired() ) {
        return;
    }

    if ( static_cast<int>(level) < static_cast<int>(mFilterLevel) ) {
        return;
    }

    auto sink = mSink.lock();
    sink->write(std::format("[{}] {}\n", to_string(level), message));
}

void Logger::trace(std::string_view message) {
    log(Level::Trace, message);
}

void Logger::info(std::string_view message) {
    log(Level::Info, message);
}

void Logger::warn(std::string_view message) {
    log(Level::Warning, message);
}

void Logger::error(std::string_view message) {
    log(Level::Error, message);
}


std::string to_string(Logger::Level level) {
    switch ( level ) {
    case Logger::Level::Trace:
        return "TRACE";
    case Logger::Level::Info:
        return "INFO";
    case Logger::Level::Warning:
        return "WARNING";
    case Logger::Level::Error:
        return "ERROR";
    }
    return "UNKNOWN";
}

} // namespace OwLog