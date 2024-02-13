cmake_minimum_required(VERSION 3.24)

project(
    CPP-CRASH_COURSE_CH-10
    VERSION 1.0
    LANGUAGES CXX
)
add_executable(autobrake "")

target_sources(autobrake
    PRIVATE
        "autobrake.cpp"
        "main.cpp"
)

target_compile_options(autobrake
    PRIVATE
     -Wall -Wextra -Werror
)

target_compile_features(autobrake
    PRIVATE
    cxx_std_20
)

add_subdirectory(test)
