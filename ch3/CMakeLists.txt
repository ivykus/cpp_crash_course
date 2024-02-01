cmake_minimum_required(VERSION 3.27)

project(ch2 CXX)

add_executable(3-2 3-2.cpp)

target_compile_options(3-2 
    PRIVATE
    -Wall -Wextra -Werror
)

target_compile_features(3-2
    PRIVATE
    cxx_std_20
)