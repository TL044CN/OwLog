#include "catch2/catch_test_macros.hpp"

#include "MockingBird.hpp"

#define private public
#include "Sinks/FileStreamSink.hpp"
#include "Sinks/TerminalSink.hpp"
#undef private

#include <sstream>
#include <iostream>
#include <memory>

using namespace OwLog;
using namespace MockingBird;

template<typename... Args>
using MockFunc = MockingController::MockingFunction<Args...>;


SCENARIO("Logging messages to a file stream sink") {
    GIVEN("A FileStreamSink") {
        auto sink = std::make_shared<FileStreamSink>("test.log");

        WHEN("Writing a message") {
            sink->write("Hello, world!\n");
            sink->flush();

            THEN("The message should be written to the file") {
                REQUIRE(sink->good());
                AND_THEN("The file should contain the message") {
                    std::ifstream file("test.log");
                    std::string line;
                    std::getline(file, line);
                    REQUIRE(line == "Hello, world!");
                }
            }
        }
    }

    GIVEN("A TerminalSink") {
        std::stringstream stream;

        AND_GIVEN("the cout stream is redirected") {
            std::streambuf* coutBuf = std::cout.rdbuf();
            std::cout.rdbuf(stream.rdbuf());

            auto sink = std::make_shared<TerminalSink>();

            WHEN("Writing a message") {
                sink->write("Hello, world!");
                sink->flush();

                THEN("The message should be written to the stream") {
                    REQUIRE(stream.str() == "\033[38;2;255;255;255m\033[48;2;0;0;0mHello, world!\033[0m");
                }

                std::cout.rdbuf(coutBuf);
            }

            WHEN("Setting the Text Color") {
                sink->setTextColor({255, 0, 0});

                AND_WHEN("Writing a message") {
                    sink->write("Hello, world!");
                    sink->flush();

                    THEN("The text color should be set") {
                        REQUIRE(stream.str() == "\033[38;2;255;0;0m\033[48;2;0;0;0mHello, world!\033[0m");
                    }
                }

                AND_WHEN("Setting the Background Color") {
                    sink->setBackgroundColor({255, 0, 0});

                    AND_WHEN("Writing a message") {
                        sink->write("Hello, world!");
                        sink->flush();

                        THEN("The background color and foreground color should be set") {
                            REQUIRE(stream.str() == "\033[38;2;255;0;0m\033[48;2;255;0;0mHello, world!\033[0m");
                        }
                    }
                }
            }

            AND_GIVEN("The colors were set") {
                sink->setTextColor({255, 0, 0});
                sink->setBackgroundColor({0, 255, 0});

                WHEN("Resetting the colors") {
                    sink->resetColors();

                    THEN("The colors should be reset to the default colors") {
                        REQUIRE(sink->mTextColor == TerminalSink::cDefaultTextColor);
                        REQUIRE(sink->mBackgroundColor == TerminalSink::cDefaultBackgroundColor);
                        AND_THEN("The colors should be written to the stream") {
                            REQUIRE(stream.str() == "\033[38;2;255;0;0m\033[48;2;0;255;0m");
                        }
                    }

                }
            }

            WHEN("Setting the Background Color") {
                sink->setBackgroundColor({255, 0, 0});

                AND_WHEN("Writing a message") {
                    sink->write("Hello, world!");
                    sink->flush();

                    THEN("The background color should be set") {
                        REQUIRE(stream.str() == "\033[38;2;255;255;255m\033[48;2;255;0;0mHello, world!\033[0m");
                    }
                }
            }

            WHEN("The Terminal is cleared") {
                sink->clearScreen();

                THEN("The terminal should be cleared") {
                    REQUIRE(stream.str() == "\033[2J\033[1;1H");
                }
            }

            WHEN("The position of the Cursor is set"){
                sink->setCursorPos(1, 1);

                THEN("The cursor should be moved to the specified position"){
                    REQUIRE(stream.str() == "\033[1;1H");
                }
            }

            WHEN("The line is cleared"){
                sink->clearLine();

                THEN("The line should be cleared"){
                    REQUIRE(stream.str() == "\033[K");
                }
            }

            THEN("The color should be enabled"){
                REQUIRE(sink->useColor());                
            }

            WHEN("The color output is disabled") {
                sink->useColor(false);

                THEN("The color should be disabled") {
                    REQUIRE_FALSE(sink->useColor());
                }

                AND_WHEN("Writing a message") {
                    sink->write("Hello, world!");
                    sink->flush();

                    THEN("The message should be written to the stream without color") {
                        REQUIRE(stream.str() == "Hello, world!");
                    }
                }
            }

        }
    }

    GIVEN("A Stream Sink") {
        std::stringstream stream;
        auto sink = std::make_shared<StreamSink>(stream);

        WHEN("Writing a message") {
            sink->write("Hello, world!");
            sink->flush();

            THEN("The message should be written to the stream") {
                REQUIRE(stream.str() == "Hello, world!");
            }
        }
    }

}