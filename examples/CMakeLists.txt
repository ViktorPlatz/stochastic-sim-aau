function(add_custom_executable target source)
    add_executable(${target} ${source})
    target_link_libraries(${target} PRIVATE stochastic_lib)
    target_include_directories(${target} PUBLIC ${CMAKE_SOURCE_DIR}/include)
endfunction()

target_link_libraries(stochastic_lib Python3::NumPy)

add_custom_executable(seihr seihr.cpp)
add_custom_executable(seihrEstimate seihrEstimate.cpp)
add_custom_executable(seihrThreaded seihrThreaded.cpp)
add_custom_executable(seihrFast seihrFast.cpp)

add_custom_executable(CircadianRhythm CircadianRhythm.cpp)
add_custom_executable(CircadianRhythmThreaded CircadianRhythmThreaded.cpp)

add_custom_executable(ABCExample ABCExample.cpp)



