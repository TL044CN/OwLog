#include "catch2/catch_test_macros.hpp"

#include "MockingBird.hpp"

#define private public
#include "Sinks/FileStreamSink.hpp"
#include "Sinks/TerminalSink.hpp"
#undef private

#include <sstream>
#include <iostream>

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
        }
    }

}