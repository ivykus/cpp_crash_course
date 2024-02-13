
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(autobrake-test "")

target_compile_features(autobrake-test PUBLIC cxx_std_20)

target_sources(autobrake-test
    PRIVATE
        "test_auto_brake.cpp"
        "../autobrake.h"
        "../autobrake.cpp"
)

target_link_libraries(autobrake-test 
    GTest::gtest_main 
)

include(GoogleTest)
gtest_discover_tests(autobrake-test)
