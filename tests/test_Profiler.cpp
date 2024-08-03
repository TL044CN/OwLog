#include "catch2/catch_test_macros.hpp"

#include "Profiler.hpp"

using namespace OwLog;

SCENARIO("Profiling function execution") {
    GIVEN("A Profiler") {
        Profiler profiler;

        WHEN("Profiling a function") {
            profiler.profileFunction("test", []() {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            });

            THEN("The profile data should be collected") {
                REQUIRE(profiler.getProfileData().size() == 1);
            }
        }

        WHEN("Profiling multiple functions") {
            profiler.profileFunction("test1", []() {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            });

            profiler.profileFunction("test2", []() {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            });

            THEN("The profile data should be collected") {
                REQUIRE(profiler.getProfileData().size() == 2);
            }
        }
    }
}