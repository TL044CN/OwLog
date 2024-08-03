/**
 * @file Profiler.hpp
 * @author TL044CN
 * @brief Profiler class to collect data on function execution
 * @version 0.1
 * @date 2024-08-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <chrono>
#include <thread>
#include <string>
#include <mutex>
#include <map>
#include <vector>
#include <functional>

#include "Sink.hpp"
#include "Sinks/ColorSink.hpp"

namespace OwLog {

/**
 * @ingroup Profiler
 * @brief Profiler class to collect data on function execution
 * @details Profiler class to collect data on function execution including name, start and end time,
 *          thread ID, start and end memory usage, start and end CPU usage
 */
class Profiler {
    class ProfileScope;
private:

    /**
     * @brief Data collected on function execution
     * @details Data collected on function execution including name, start and end time,
     *          thread ID, start and end memory usage, start and end CPU usage
     */
    struct ProfileData {
        std::string name;
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        std::chrono::time_point<std::chrono::high_resolution_clock> end;
        std::thread::id threadID;
        uint64_t startMemoryUsage;
        uint64_t endMemoryUsage;
        uint64_t startCPUUsage;
        uint64_t endCPUUsage;
    };

    std::map<std::string, std::vector<ProfileData>> mProfileData;
    std::mutex mMutex;

public:
    /**
     * @brief Construct a new Profiler object
     * @details Construct a new Profiler object
     */
    Profiler() = default;

    /**
     * @brief Destroy the Profiler object
     * @details Destroy the Profiler object
     */
    ~Profiler() = default;

private:
    /**
     * @brief Write profile data to sink
     * @details Write profile data to sink
     * 
     * @param sink Sink to write data to
     */
    void writeToSink(Sink& sink);

    /**
     * @brief Write profile data to color sink
     * @details Write profile data to color sink
     * 
     * @param sink Sink to write data to
     */
    void writeToColorSink(ColorSink& sink);

protected:
    /**
     * @brief Get the Current Memory Usage
     * @details Get the Current Memory Usage
     * 
     * @return uint64_t Current memory usage
     */
    static uint64_t getCurrentMemoryUsage();

    /**
     * @brief Get the Current CPU Usage
     * @details Get the Current CPU Usage
     * 
     * @return uint64_t Current CPU usage
     */
    static uint64_t getCurrentCPUUsage();

    /**
     * @brief Add profile data
     * @details Add profile data
     * 
     * @param data Profile data
     */
    void addProfileData(ProfileData&& data);

public:

    /**
     * @brief Profile a Scope
     * 
     * @param label Label of the scope
     * @return ProfileScope 
     */
    ProfileScope profileScope(std::string label);

    /**
     * @brief Profile a function
     * @details Profile a function
     * 
     * @param label Label of the function
     * @param func Function to profile
     */
    void profileFunction(std::string label, std::function<void()> func);

    /**
     * @brief Write profile data
     * @details Write profile data to a sink.
     *          When the sink is a ColorSink, the data is written with colors.
     * 
     * @param sink Sink to write data to
     */
    void writeProfileData(Sink& sink);
};

} // namespace OwLog