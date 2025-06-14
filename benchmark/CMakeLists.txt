add_executable(bench bench.cpp)

target_link_libraries(bench
        PRIVATE
        stochastic_lib
        benchmark::benchmark_main
)

target_include_directories(bench PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

