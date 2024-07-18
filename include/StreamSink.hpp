/**
 * @file StreamSink.hpp
 * @author TL044CN
 * @brief StremaSink class header file
 * @version 0.1
 * @date 2024-07-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include "Sink.hpp"
#include <iostream>

namespace OwLog {

    /**
     * @brief StreamSink class for representing a logging sink that writes to a stream
     */
    class StreamSink : public Sink {
    private:
        std::ostream& mStream;  ///< the stream to write to

    public:
        /**
         * @brief Construct a new StreamSink object
         * 
         * @param stream the stream to write to
         */
        StreamSink(std::ostream& stream);

        /**
         * @brief Destroy the StreamSink object
         * 
         */
        virtual ~StreamSink() = default;

    protected:
        /**
         * @brief write a message to the sink
         * 
         * @param message the message
         */
        void write(std::string_view message) override;
    };
}