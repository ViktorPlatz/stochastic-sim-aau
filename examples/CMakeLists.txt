function(add_simulation_executable target source)
    add_executable(${target} ${source})
    target_link_libraries(${target} PRIVATE stochastic_lib)
    target_include_directories(${target} PRIVATE ${CMAKE_SOURCE_DIR}/include)
endfunction()

target_link_libraries(stochastic_lib PRIVATE Python3::NumPy)

set(EXECUTABLES
        seihr
        seihrEstimate
        seihrThreaded
        seihrFast
        CircadianRhythm
        CircadianRhythmThreaded
        ABCExample
)

foreach(exec ${EXECUTABLES})
    add_simulation_executable(${exec} ${exec}.cpp)
endforeach()