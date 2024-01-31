add_library(calclib
        "calculator.h"
        "calculator.cpp"
)

target_include_directories(calclib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(calculator main.cpp)


target_link_libraries(calculator
    calclib
)
