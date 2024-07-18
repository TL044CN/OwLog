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

namespace OwLog {

/**
 * @brief Sink class
 */
class Sink {
public:
    virtual void write(std::string_view message) = 0;
};

} // namespace OwLog