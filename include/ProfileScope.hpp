/**
 * @file ProfileScope.hpp
 * @author TL044CN
 * @brief ProfileScope class to collect data on a scope
 * @version 0.1
 * @date 2024-08-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include "Profiler.hpp"

namespace OwLog {

/**
 * @ingroup Profiler
 * @brief ProfileScope class to collect data on a scope
 * @details ProfileScope class to collect data on a scope including name, start and end time,
 *          thread ID, start and end memory usage, start and end CPU usage
 */
class Profiler::ProfileScope {
private:
    Profiler& mProfiler;
    std::string mLabel;
    std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime;
    std::thread::id mThreadID;
    uint64_t mStartMemoryUsage;
    uint64_t mStartCPUTime;

public:
    /**
     * @brief Construct a new Profile Scope object
     * @details Construct a new Profile Scope object
     * 
     * @param profiler Profiler object
     * @param label Label of the scope
     */
    ProfileScope(Profiler& profiler, std::string& label);

    /**
     * @brief Destroy the Profile Scope object
     * @details Destroy the Profile Scope object
     */
    ~ProfileScope();
};

};