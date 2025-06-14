add_executable(ReactionTests ReactionTests.cpp)
target_link_libraries(ReactionTests PRIVATE stochastic_lib doctest::doctest_with_main)
target_include_directories(ReactionTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/stochastic_lib)
add_test(NAME ReactionTests COMMAND ReactionTests)