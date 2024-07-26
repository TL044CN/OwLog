/**
 * @file Sink.hpp
 * @author TL044CN
 * @brief Sink class declaration
 * @version 0.1
 * @date 2024-07-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <string_view>

/**
 * @defgroup Sinks
 * @brief Sinks module
 * @details This module contains all sink classes
 */

namespace OwLog {

/**
 * @ingroup Sinks
 * @brief Sink base class
 * @details Sink class is a base class for all sinks
 */
class Sink {
public:
    /**
     * @brief Write a message to the sink
     * @param message Message to write
     */
    virtual void write(std::string_view message) = 0;
};

} // namespace OwLog