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
#include <cstdint>

namespace OwLog {

/**
 * @ingroup Sinks
 * @brief TerminalSink class
 * @details A sink that writes log messages to the terminal
 */
class TerminalSink : public StreamSink {
public:

    /**
     * @brief Color struct
     * @details A struct that holds color values
     */
    struct Color {
        uint8_t red;      ///< Red color value
        uint8_t green;    ///< Green color value
        uint8_t blue;     ///< Blue color value

        /**
         * @brief Construct a new Color object
         * @param red The red color value
         * @param green The green color value
         * @param blue The blue color value
         */
        Color(uint8_t red, uint8_t green, uint8_t blue)
            : red(red), green(green), blue(blue) {}

        /**
         * @brief Construct a new Color object
         */
        Color()
            : red(0), green(0), blue(0) {};

        /**
         * @brief Compare two colors
         * 
         * @param other The other color
         * @return true the colors match
         * @return false the colors dont match
         */
        bool operator ==(const Color& other) const = default;

    };

private:
    static const Color cDefaultTextColor;
    static const Color cDefaultBackgroundColor;

    Color mTextColor = cDefaultTextColor;
    Color mBackgroundColor = cDefaultBackgroundColor;

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
     * @brief Set the text color
     * @param color The color
     */
    void setTextColor(Color color);

    /**
     * @brief Set the background color
     * @param color The color
     */
    void setBackgroundColor(Color color);

    /**
     * @brief Reset the colors to the default
     */
    void resetColors();

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