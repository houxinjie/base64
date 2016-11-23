cmake_minimum_required (VERSION 2.6)
project (base64 C)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic -Wall")
endif()

add_library(base64 base64.c)
add_executable(base64_test test.c)
target_link_libraries(base64_test base64)
