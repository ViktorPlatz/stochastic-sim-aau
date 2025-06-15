#ifndef PLOTSIMULATION_HPP
#define PLOTSIMULATION_HPP
#define WITHOUT_NUMPY

#include <unordered_set>

#include "Vessel.hpp"
#include "SimulationResult.hpp"
namespace stochastic {
    // 6. Display simulation trajectories of how the amounts change. External tools/libraries can be used to visualize
    void plotSimulation(Vessel& vessel, SimulationResult& simulationResult, const std::string& filename, const std::string& title, const std::unordered_set<Species>& excludedSpecies = {});
}


#endif
