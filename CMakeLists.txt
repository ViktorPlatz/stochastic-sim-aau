cmake_minimum_required(VERSION 3.30)
project(stochastic_sim_aau)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)