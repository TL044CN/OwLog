#include "catch2/catch_test_macros.hpp"

#include "StreamSink.hpp"
#include "Logger.hpp"

using namespace OwLog;

SCENARIO("Logging messages to a stream sink") {
    GIVEN("A StreamSink") {
        std::stringstream stream;
        auto sink = std::make_shared<StreamSink>(stream);

        AND_GIVEN("A Logger") {
            Logger logger(sink);

            WHEN("Logging a message") {
                logger.info("Hello, world!");

                THEN("The message should be written to the stream") {
                    REQUIRE(stream.str() == "[INFO] Hello, world!\n");
                }
            }

            WHEN("Logging a message with a format") {
                logger.info("Hello, {}!", "world");

                THEN("The message should be written to the stream") {
                    REQUIRE(stream.str() == "[INFO] Hello, world!\n");
                }
            }

            WHEN("Logging a message with multiple arguments") {
                logger.info("Hello, {}! The answer is {}", "world", 42);

                THEN("The message should be written to the stream") {
                    REQUIRE(stream.str() == "[INFO] Hello, world! The answer is 42\n");
                }
            }
        }
    }
}