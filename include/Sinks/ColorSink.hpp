/**
 * @file ColorSink.hpp
 * @author TL044CN
 * @brief ColorSink class to write log messages with color
 * @version 0.1
 * @date 2024-08-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "Sink.hpp"
#include <cstdint>

namespace OwLog {

/**
 * @ingroup Sinks
 * @brief ColorSink class to write log messages with color
 * @details ColorSink class to write log messages with color
 */
class ColorSink : public Sink {
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
        bool operator==(const Color& other) const = default;

    };

    static const Color cDefaultTextColor;
    static const Color cDefaultBackgroundColor;

protected:
    Color mTextColor = cDefaultTextColor;
    Color mBackgroundColor = cDefaultBackgroundColor;

public:
    /**
     * @brief Construct a new ColorSink object
     * @param textColor The text color
     * @param backgroundColor The background color
     */
    ColorSink(const Color& textColor = cDefaultTextColor, const Color& backgroundColor = cDefaultBackgroundColor);

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
     * @brief Get the Text Color
     * @return Color The text color
     */
    Color getTextColor() const;

    /**
     * @brief Get the background color
     * @return Color The background color
     */
    Color getBackgroundColor() const;

};

} // namespace OwLog