/**
 * @file TerminalSink.cpp
 * @author TL044CN
 * @brief TerminalSink class implementation
 * @version 0.1
 * @date 2024-07-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Sinks/TerminalSink.hpp"
#include <iostream>

namespace OwLog {

TerminalSink::TerminalSink(const Color& textColor, const Color& backgroundColor)
    : StreamSink(std::cout), ColorSink(textColor, backgroundColor) {}


bool TerminalSink::useColor() const {
    return mUseColor;
}

void TerminalSink::useColor(bool useColor) {
    mUseColor = useColor;
}

void TerminalSink::setCursorPos(uint8_t x, uint8_t y) {
    std::cout << "\033[" << static_cast<int>(y) << ";" << static_cast<int>(x) << "H";
    flush();
}

void TerminalSink::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
    flush();
}

void TerminalSink::clearLine() {
    std::cout << "\033[K";
    flush();
}

void TerminalSink::write(std::string_view message) {
    if (mUseColor) {
        std::cout << "\033[38;2;" << static_cast<int>(mTextColor.red) << ";" << static_cast<int>(mTextColor.green) << ";" << static_cast<int>(mTextColor.blue) << "m";
        std::cout << "\033[48;2;" << static_cast<int>(mBackgroundColor.red) << ";" << static_cast<int>(mBackgroundColor.green) << ";" << static_cast<int>(mBackgroundColor.blue) << "m";
    }
    std::cout << message;
    if (mUseColor) {
        std::cout << "\033[0m";
    }
}

} // namespace OwLog