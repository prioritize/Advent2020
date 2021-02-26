cmake_minimum_required(VERSION 3.19)

# Set the variable "This to `Advent2020`""
set(This Example)


project(${This} C CXX)

# Set the standards for C and C++
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Tell CMake that we'll be using Unit Tests
enable_testing()
# Include Google Test
add_subdirectory(include/googletest)

set(Headers
    include/Day14.hpp
)
set(Sources
    src/Day14.cc
)

set(CMAKE_CXX_FLAGS "-g -Wall")
add_library(${This} STATIC ${Sources} ${Headers})


# Add tests to the project
add_subdirectory(test)
# include_directories(googletest/include)
# add_executable(mytests mytests.cc)
# add_executable(Day14 Day14.cc)

# target_link_libraries(mytests PRIVATE gtest)
# target_link_libraries(Day14 PRIVATE gtest)
