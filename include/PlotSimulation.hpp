#ifndef PLOTSIMULATION_HPP
#define PLOTSIMULATION_HPP
#define WITHOUT_NUMPY

#include <unordered_set>

#include "Vessel.hpp"
#include "SimulationResult.hpp"
namespace stochastic {

    void plotSimulation(Vessel& vessel, SimulationResult& simulationResult, const std::string& filename, const std::string& title, const std::unordered_set<Species>& excludedSpecies = {});
}


#endif
