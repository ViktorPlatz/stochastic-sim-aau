#include <iostream>
#include "StochasticLib.hpp"

#define END_TIME 100
#define N 10'000
//5. Demonstrate the application of the library on the three examples (shown in Fig. 1, 2, 3).
int main() {
  auto seihr = stochastic::Seihr(N);
  stochastic::Graph::saveDotGraphToFile(seihr, "output/seihr_simulation.dot");
  auto simulation = stochastic::Simulator(seihr, 1);
  stochastic::SimulationResult result;

  std::cout << "Starting simulation with " << seihr.getSpecies().size()
            << " species and " << seihr.getReactions().size() << " reactions."
            << std::endl;

  for (auto timeseries : simulation.runSingle(END_TIME)) {
    result.add(timeseries.first, *timeseries.second);
  }

  // Multiply the H species by 1000 to see results more clearly
  auto multiplyH = [](stochastic::TimeSeries& ts) {
    ts.second->get(stochastic::Species("H")) *= 1000;
  };
  std::for_each(result.getTrajectory().begin(), result.getTrajectory().end(),
                multiplyH);

  std::cout << "Simulation completed. Plotting results." << std::endl;
  stochastic::plotSimulation(seihr, result, "output/seihr_simulation.png",
                             "Stochastic Simulation of SEIHR Model");
}