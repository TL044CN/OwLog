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

#include <sstream>

#if __cpp_lib_stacktrace < 202011L
#if __linux__
#define __custom_stacktrace__
#include <execinfo.h>
#include <cxxabi.h>
#include <dlfcn.h>
#endif
#endif
namespace OwLog {

#if defined(__custom_stacktrace__)
std::string getStackTrace(uint8_t indent) {
    void* callstack[128];
    int frames = backtrace(callstack, 128);
    char** strs = backtrace_symbols(callstack, frames);
    std::stringstream stream;
    std::string indentStr(indent, ' ');

    for ( int i = 0; i < frames; ++i ) {
        Dl_info info;
        if(dladdr(callstack[i], &info) && info.dli_sname) {
            int status;
            char* demangled = abi::__cxa_demangle(info.dli_sname, nullptr, 0, &status);
            stream << indentStr << (status == 0 ? demangled : info.dli_sname) << '\n';
//            stream << indentStr << " + " << (char*)callstack[i] - (char*)info.dli_saddr << '\n';
            free(demangled);
        } else {
            stream << indentStr << strs[i] << '\n';
        }
    }
    free(strs);
    return stream.str();

}
#endif


Logger::Logger(std::shared_ptr<Sink> sink)
    : mSink(sink) {}


std::string Logger::stack_trace(uint8_t indent) const {

    std::stringstream stream;

#if __cpp_lib_stacktrace >= 202011L
    std::string indentStr(indent, ' ');
    for ( const auto& trace : std::stacktrace::current() ) {
        stream << indentStr << trace << '\n';
    }
#elif defined(__custom_stacktrace__)
    stream << getStackTrace(indent);
#else
    stream << "Stack trace not available\n";
#endif


    return stream.str();
}


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
    if ( level < mFilterLevel ) {
        return;
    }

    if ( level == LogLevel::TRACE || level == LogLevel::FATAL ) {
        mSink->write(std::format(
            "[{}] {}\n"
            "====STACKTRACE===>\n"
            "{}"
            "<===STACKTRACE====\n",
            to_string(level), message, stack_trace(1)));
    } else
        mSink->write(std::format("[{}] {}\n", to_string(level), message));
}

std::string to_string(Logger::LogLevel level) {
    switch ( level ) {
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