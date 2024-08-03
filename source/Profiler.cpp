/**
 * @file Profiler.cpp
 * @author TL044CN
 * @brief Profiler class to collect data on function execution
 * @version 0.1
 * @date 2024-08-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Profiler.hpp"
#include "ProfileScope.hpp"

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

namespace OwLog {

void Profiler::writeToSink(Sink& sink) {
    std::lock_guard<std::mutex> lock(mMutex);

    for ( const auto& [name, data] : mProfileData ) {
        for ( const auto& profileData : data ) {
            auto threadId = std::hash<std::thread::id>{}(profileData.threadID);
            auto threadIdStr = std::to_string(threadId);
            auto timestamp = profileData.start.time_since_epoch().count();
            auto duration = (profileData.end - profileData.start).count();
            auto memoryUsageDiff = profileData.endMemoryUsage - profileData.startMemoryUsage;
            auto cpuUsageDiff = profileData.endCPUUsage - profileData.startCPUUsage;
            
            sink.write(std::format(
                "<ProfileData label=\"{}\" timestamp=\"{}\" duration=\"{}ns\" threadID=\"{}\">"
                "<MemoryUsage start=\"{}\" end=\"{}\" diff=\"{}\"/>"
                "<CPUUsage start=\"{}\" end=\"{}\" diff=\"{}\"/>"
                "</ProfileData>",
                profileData.name,
                timestamp,
                duration,
                threadIdStr,
                profileData.startMemoryUsage,
                profileData.endMemoryUsage,
                memoryUsageDiff,
                profileData.startCPUUsage,
                profileData.endCPUUsage,
                cpuUsageDiff
            ));

        }
    }
};

double percentile(const double min, const double max, const double val) {
    return (val - min) / (max - min);
}

ColorSink::Color getScoreColor(double score) {
    std::clamp(score, 0.0, 1.0);
    uint8_t red = 255 * score;
    uint8_t green = 255 * (1 - score);
    return { red, green, 0 };
}

void Profiler::writeToColorSink(ColorSink& sink) {
    std::lock_guard<std::mutex> lock(mMutex);

    struct { uint64_t max = 0; uint64_t min = 0; } CPUUsage;
    struct { uint64_t max = 0; uint64_t min = 0; } MemoryUsage;
    struct {
        std::chrono::duration<double> max = std::chrono::duration<double>::zero();
        std::chrono::duration<double> min = std::chrono::duration<double>::zero();
    } Duration;

    // find the maximum and minimum values for CPUUsage, MemoryUsage and Duration
    for ( const auto& [name, data] : mProfileData ) {
        for ( const auto& profileData : data ) {
            auto cpuUsageDiff = profileData.endCPUUsage - profileData.startCPUUsage;
            auto memoryUsageDiff = profileData.endMemoryUsage - profileData.startMemoryUsage;
            auto duration = profileData.end - profileData.start;

            CPUUsage.max = std::max(CPUUsage.max, cpuUsageDiff);
            CPUUsage.min = std::min(CPUUsage.min, cpuUsageDiff);

            MemoryUsage.max = std::max(MemoryUsage.max, memoryUsageDiff);
            MemoryUsage.min = std::min(MemoryUsage.min, memoryUsageDiff);

            if ( duration > Duration.max )
                Duration.max = duration;
            if ( duration < Duration.min )
                Duration.min = duration;
        }
    }

    // write colored profile data to sink
    for ( const auto& [name, data] : mProfileData ) {
        for ( const auto& profileData : data ) {
            auto previousBackground = sink.getBackgroundColor();

            sink.write(std::format(
                "<ProfileData label=\"{}\" timestamp=\"{}\" duration=\"",
                profileData.name,
                profileData.start.time_since_epoch().count()
            ));

            auto duration = profileData.end - profileData.start;
            sink.setBackgroundColor(getScoreColor(percentile(Duration.min.count(), Duration.max.count(), duration.count())));
            sink.write(std::to_string(duration.count()));
            sink.setBackgroundColor(previousBackground);

            auto threadId = std::hash<std::thread::id>{}(profileData.threadID);
            auto threadIdStr = std::to_string(threadId);
            sink.write(std::format(
                "\" threadID=\"{}\">"
                "<MemoryUsage start=\"{}\" end=\"{}\" diff=\"",
                threadIdStr,
                profileData.startMemoryUsage,
                profileData.endMemoryUsage
            ));
            auto memoryUsageDiff = profileData.endMemoryUsage - profileData.startMemoryUsage;
            sink.setBackgroundColor(getScoreColor(percentile(MemoryUsage.min, MemoryUsage.max, memoryUsageDiff)));
            sink.write(std::to_string(memoryUsageDiff));
            sink.setBackgroundColor(previousBackground);

            sink.write(std::format(
                "\"/>"
                "<CPUUsage start=\"{}\" end=\"{}\" diff=\"",
                profileData.startCPUUsage,
                profileData.endCPUUsage
            ));
            auto cpuUsageDiff = profileData.endCPUUsage - profileData.startCPUUsage;
            sink.setBackgroundColor(getScoreColor(percentile(CPUUsage.min, CPUUsage.max, cpuUsageDiff)));
            sink.write(std::to_string(cpuUsageDiff));
            sink.setBackgroundColor(previousBackground);
            sink.write("\"/></ProfileData>");

        }
    }
};


uint64_t Profiler::getCurrentMemoryUsage() {
    return 0;
}

uint64_t Profiler::getCurrentCPUUsage() {
    return 0;
}

void Profiler::addProfileData(ProfileData&& data) {
    std::lock_guard<std::mutex> lock(mMutex);
    mProfileData[data.name].push_back(data);
}

Profiler::ProfileScope Profiler::profileScope(std::string label) {
    return Profiler::ProfileScope(*this, label);
}

void Profiler::profileFunction(std::string label, std::function<void()> func) {
    auto scope = profileScope(label);
    func();
}

void Profiler::writeProfileData(Sink& sink) {
    if(auto* colorSink = dynamic_cast<ColorSink*>(&sink)) {
        writeToColorSink(*colorSink);
    } else {
        writeToSink(sink);
    }
};

} // namespace OwLog