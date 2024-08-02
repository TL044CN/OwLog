/**
 * @file SocketSink.cpp
 * @author TL044CN
 * @brief SocketSink class implementation
 * @version 0.1
 * @date 2024-08-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "Sinks/SocketSink.hpp"

namespace OwLog {

SocketSink::SocketSink(SocketSparrow::Socket&& socket)
    : mSocket(std::move(socket)) {}

SocketSink::~SocketSink() {}

void SocketSink::write(std::string_view message) {
    mSocket.send(std::string(message));
}

} // namespace OwLog