/**
 * @file SocketSink.hpp
 * @author TL044CN
 * @brief SocketSink class definition
 * @version 0.1
 * @date 2024-08-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include "Sink.hpp"
#include "Socket.hpp"

namespace OwLog {

/**
 * @brief SocketSink class
 * @ingroup Sinks
 * @details This class is used to write log messages to a network socket
 */
class SocketSink : public Sink {
private:
    SocketSparrow::Socket mSocket;

public:
    /**
     * @brief Construct a new SocketSink object
     * 
     * @param socket 
     */
    SocketSink(SocketSparrow::Socket&& socket);

    /**
     * @brief Destroy the SocketSink object
     */
    ~SocketSink();

    /**
     * @brief Write message to socket
     * 
     * @param message 
     */
    void write(std::string_view message) override;
};

} // namespace OwLog