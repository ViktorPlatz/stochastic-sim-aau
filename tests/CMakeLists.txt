function(add_stochastic_test test_name test_file)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE stochastic_lib doctest::doctest_with_main)
    target_include_directories(${test_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/stochastic_lib)
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

add_stochastic_test(ReactionTests ReactionTests.cpp)
add_stochastic_test(SpeciesTests SpeciesTests.cpp)