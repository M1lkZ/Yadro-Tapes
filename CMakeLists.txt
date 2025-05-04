cmake_minimum_required(VERSION 3.14)
project(tape_sort)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tmp)

add_library(tape_lib STATIC
    src/file_tape.cpp
    src/tape_sorter.cpp
    src/config_loader.cpp
)
target_include_directories(tape_lib PUBLIC include)

add_executable(tape_sort src/main.cpp)
target_link_libraries(tape_sort PRIVATE tape_lib)

option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()