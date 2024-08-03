/**
 * @file ColorSink.cpp
 * @author TL044CN
 * @brief ColorSink class implementation
 * @version 0.1
 * @date 2024-08-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Sinks/ColorSink.hpp"

namespace OwLog {

ColorSink::Color const ColorSink::cDefaultTextColor       = ColorSink::Color(255, 255, 255);
ColorSink::Color const ColorSink::cDefaultBackgroundColor = ColorSink::Color(0, 0, 0);

ColorSink::ColorSink(const Color& textColor, const Color& backgroundColor)
    : mTextColor(textColor), mBackgroundColor(backgroundColor) {}

void ColorSink::setTextColor(Color color) {
    mTextColor = color;
}

void ColorSink::setBackgroundColor(Color color) {
    mBackgroundColor = color;
}

void ColorSink::resetColors() {
    mTextColor = cDefaultTextColor;
    mBackgroundColor = cDefaultBackgroundColor;
}

ColorSink::Color ColorSink::getTextColor() const {
    return mTextColor;
}

ColorSink::Color ColorSink::getBackgroundColor() const {
    return mBackgroundColor;
}

} // namespace OwLog