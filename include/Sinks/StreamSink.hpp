/**
 * @file StreamSink.hpp
 * @author TL044CN
 * @brief StreamSink class declaration
 * @version 0.1
 * @date 2024-07-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include "../Sink.hpp"
#include <ostream>

namespace OwLog {

/**
 * @brief StreamSink class
 */
class StreamSink : public Sink {
private:
    std::ostream& mStream;

public:
    explicit StreamSink(std::ostream& stream);

    void write(std::string_view message) override;
};

} // namespace OwLog