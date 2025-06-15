function(add_stochastic_test test_name test_file)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} PRIVATE stochastic_lib doctest::doctest_with_main)
    target_include_directories(${test_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include/stochastic_lib)
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

set(TEST_SOURCES
        ReactionTests.cpp
        SpeciesTests.cpp
        GraphTests.cpp
        PlotSimulationTests.cpp
        SimulatorTests.cpp
        SymbolTableTests.cpp
        MiscTests.cpp
)

foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_stochastic_test(${test_name} ${test_src})
endforeach()