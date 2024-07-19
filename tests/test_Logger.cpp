#include "catch2/catch_test_macros.hpp"

#include "StreamSink.hpp"
#include "Logger.hpp"

using namespace OwLog;

#include <iostream>

SCENARIO("Logging messages to a stream sink") {
    GIVEN("A StreamSink") {
        std::stringstream stream;
        auto sink = std::make_shared<StreamSink>(stream);

    AND_GIVEN("A Logger") {
        Logger logger(sink);

        WHEN("Logging a message") {
            logger.log(Logger::LogLevel::INFO, "Hello, world!");

            THEN("The message should be written to the stream") {
                REQUIRE(stream.str() == "[INFO] Hello, world!\n");
            }
            AND_WHEN("Logging a message without a level") {
                logger.log("Hello, world!");

                THEN("The message should be written to the stream") {
                    REQUIRE(stream.str() == "[INFO] Hello, world!\n[INFO] Hello, world!\n");
                }
            }
        }

        WHEN("Logging multiple messages") {
            logger.log(Logger::LogLevel::INFO, "Hello, world!");
            logger.log(Logger::LogLevel::INFO, "Goodbye, world!");

            THEN("The messages should be written to the stream") {
                REQUIRE(stream.str() == "[INFO] Hello, world!\n[INFO] Goodbye, world!\n");
            }
        }

        WHEN("Logging a message with a format") {
            logger.log(Logger::LogLevel::INFO, "Hello, {}!", "world");

            THEN("The message should be written to the stream") {
                REQUIRE(stream.str() == "[INFO] Hello, world!\n");
            }
        }

        WHEN("Logging a message with multiple arguments") {
            logger.log(Logger::LogLevel::INFO, "Hello, {}! The answer is {}", "world", 42);

            THEN("The message should be written to the stream") {
                REQUIRE(stream.str() == "[INFO] Hello, world! The answer is 42\n");
            }
        }

        WHEN("Setting a filter level") {
            logger.set_filter_level(Logger::LogLevel::WARN);
        AND_WHEN("Logging a message at the WARN level") {
            logger.log(Logger::LogLevel::WARN, "This message should be at the WARN level");

            THEN("The message should be written to the stream") {
                REQUIRE(stream.str() == "[WARN] This message should be at the WARN level\n");
            }
        }
        AND_WHEN("Logging a message at the INFO level") {
            logger.log(Logger::LogLevel::INFO, "This message should be at the INFO level");

            THEN("The message should not be written to the stream") {
                REQUIRE(stream.str() == "");
            }
        }}

        WHEN("Setting a default level") {
            logger.set_default_level(Logger::LogLevel::WARN);
            logger.log("This message should be at the WARN level");

            THEN("The message should be written to the stream") {
                REQUIRE(stream.str() == "[WARN] This message should be at the WARN level\n");
            }
        }

        WHEN("Logging a message at the TRACE level") {
            logger.set_filter_level(Logger::LogLevel::TRACE);
            logger.log(Logger::LogLevel::TRACE, "This message should be at the TRACE level");

            THEN("The message should include a stack trace") {
                auto currentContent = stream.str();
                REQUIRE(currentContent.find("====STACKTRACE===>") != std::string::npos);
            }
        }

        WHEN("Logging a message at the FATAL level") {
            logger.log(Logger::LogLevel::FATAL, "This message should be at the FATAL level");

            THEN("The message should include a stack trace") {
                auto currentContent = stream.str();
                REQUIRE(currentContent.find("====STACKTRACE===>") != std::string::npos);
            }
        }
    }}
}