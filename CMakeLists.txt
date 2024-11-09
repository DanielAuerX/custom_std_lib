cmake_minimum_required(VERSION 3.10)

project(clib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_library(clib STATIC src/memory_alloc.cpp)

target_include_directories(clib PUBLIC include)


add_executable(run_tests test/test_main.cpp)
target_link_libraries(run_tests PRIVATE clib)

