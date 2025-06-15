set(SOURCES
        Vessel.cpp
        Species.cpp
        Reaction.cpp
        SimulationResult.cpp
        Simulator.cpp
        PartialReaction.cpp
        PlotSimulation.cpp
        SpeciesCombination.cpp
        Graph.cpp
        Utils.cpp
)

add_library(stochastic_lib STATIC ${SOURCES})
target_include_directories(stochastic_lib PRIVATE ${CMAKE_SOURCE_DIR}/include)