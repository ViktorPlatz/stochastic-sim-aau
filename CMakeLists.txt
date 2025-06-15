cmake_minimum_required(VERSION 3.28)
project(stochastic_sim_aau)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_definitions(_ENABLE_STD_COROUTINE)
endif()

find_package(Python3 3.12 COMPONENTS Interpreter Development NumPy REQUIRED)
message(STATUS "Python executable: '${Python3_EXECUTABLE}'")
message(STATUS "Python include directories: '${Python3_INCLUDE_DIRS}'")
message(STATUS "Python libraries: '${Python3_LIBRARIES}'")

include(cmake/benchmark.cmake)
include(cmake/doctest.cmake)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)
add_subdirectory(benchmark)