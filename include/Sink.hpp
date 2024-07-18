/**
 * @file Sink.hpp
 * @author TL044CN
 * @brief Sink class header file
 * @version 0.1
 * @date 2024-07-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <string_view>

namespace OwLog {

/**
 * @brief Sink class for representing a logging sink
 * 
 */
class Sink {
public:
    Sink() = default;
    virtual ~Sink() = default;

    /**
     * @brief write a message to the sink
     * 
     * @param message the message
     */
    virtual void write(std::string_view message) = 0;
};

}