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
 * @ingroup Sinks
 * @brief StreamSink class
 * @details A sink that writes log messages to a stream
 */
class StreamSink : public Sink {
protected:
    std::ostream& mStream;      ///< The stream to write to

public:
    /**
     * @brief Construct a new StreamSink object
     * @param stream The stream to write to
     */
    explicit StreamSink(std::ostream& stream);

    /**
     * @brief Destroy the StreamSink object
     */
    virtual ~StreamSink() override = default;

    /**
     * @brief Flush the stream
     */
    void flush();

    void write(std::string_view message) override;
};

} // namespace OwLog