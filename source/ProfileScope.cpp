/**
 * @file ProfileScope.cpp
 * @author TL044CN
 * @brief ProfileScope class to collect data on a scope
 * @version 0.1
 * @date 2024-08-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "ProfileScope.hpp"

namespace OwLog {

Profiler::ProfileScope::ProfileScope(Profiler& profiler, std::string& label)
    : mProfiler(profiler), mLabel(label), mThreadID(std::this_thread::get_id()) {
    mStartTime = std::chrono::high_resolution_clock::now();
    mStartMemoryUsage = Profiler::getCurrentMemoryUsage();
    mStartCPUTime = Profiler::getCurrentCPUUsage();
}

Profiler::ProfileScope::~ProfileScope() {
    auto endTime = std::chrono::high_resolution_clock::now();
    uint64_t endMemoryUsage = Profiler::getCurrentMemoryUsage();
    uint64_t endCPUUsage = Profiler::getCurrentCPUUsage();

    Profiler::ProfileData data = {
        mLabel,
        mStartTime,
        endTime,
        mThreadID,
        mStartMemoryUsage,
        endMemoryUsage,
        mStartCPUTime,
        endCPUUsage
    };

    mProfiler.addProfileData(std::move(data));
}

};