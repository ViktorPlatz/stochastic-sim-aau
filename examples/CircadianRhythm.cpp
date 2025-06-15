#include <PlotSimulation.hpp>
#include <iostream>

#include "ExampleSimulations.hpp"
#include "Graph.hpp"
#include "SimulationResult.hpp"
#include "Simulator.hpp"

int main() {
  auto circadian_rhythm = stochastic::circadian_rhythm();
  stochastic::Graph::saveDotGraphToFile(circadian_rhythm,
                                        "output/circadian_simulation.dot");

  auto simulation = stochastic::Simulator(circadian_rhythm, 0);
  stochastic::SimulationResult result;

  std::cout << "Starting simulation with "
            << circadian_rhythm.getSpecies().size() << " species and "
            << circadian_rhythm.getReactions().size() << " reactions."
            << std::endl;

  for (auto timeseries : simulation.runSingle(48.0)) {
    result.add(timeseries.first, *timeseries.second);
  }

  std::unordered_set<stochastic::Species> exclude = {
      circadian_rhythm.environment()};

  std::cout << "Simulation completed. Plotting results." << std::endl;
  plotSimulation(circadian_rhythm, result, "output/circadian_simulation.png",
                 "Stochastic Simulation of Circadian Rhythm Model", exclude);
}
