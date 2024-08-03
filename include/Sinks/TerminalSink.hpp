/**
 * @file TerminalSink.hpp
 * @author TL044CN
 * @brief TerminalSink class declaration
 * @version 0.1
 * @date 2024-07-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include "StreamSink.hpp"
#include "ColorSink.hpp"
#include <cstdint>

namespace OwLog {

/**
 * @ingroup Sinks
 * @brief TerminalSink class
 * @details A sink that writes log messages to the terminal
 */
class TerminalSink : public StreamSink, public ColorSink {
private:
    bool mUseColor = true;

public:
    /**
     * @brief Construct a new Terminal Sink object
     * @param textColor The text color
     * @param backgroundColor The background color
     */
    TerminalSink(const Color& textColor = cDefaultTextColor, const Color& backgroundColor = cDefaultBackgroundColor);

    /**
     * @brief Get weather color is used
     * @return bool True if color is used
     */
    bool useColor() const;

    /**
     * @brief Set weather color is used
     * @param useColor True if color is used
     */
    void useColor(bool useColor);

    /**
     * @brief Set the cursor position
     * @param x The x position
     * @param y The y position
     */
    virtual void setCursorPos(uint8_t x, uint8_t y);

    /**
     * @brief Clear the terminal screen
     */
    virtual void clearScreen();

    /**
     * @brief Clear the current line
     */
    virtual void clearLine();

    void write(std::string_view message) override;
};

} // namespace OwLog