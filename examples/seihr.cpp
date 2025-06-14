#include <iostream>
#include <PlotSimulation.hpp>

#include "SimulationResult.hpp"

#include "ExampleSimulations.hpp"
#include "Graph.hpp"
#include "Simulator.hpp"

int main() {
    auto seihr = stochastic::seihr(10000);
    stochastic::Graph::saveDotGraphToFile(seihr, "output/seihr_simulation.dot");
    auto simulation = stochastic::Simulator(seihr, 0);
    stochastic::SimulationResult result;

    std::cout << "Starting simulation with " << seihr.getSpecies().size() << " species and "
              << seihr.getReactions().size() << " reactions." << std::endl;

    for (auto timeseries : simulation.runSingle(1000)) {
        result.add(timeseries.first, timeseries.second);
    }

    //multiply the H species by 1000 to see results more clearly
    auto multiplyH = [](stochastic::timeSeries& ts) {ts.second.get(stochastic::Species("H")) *= 1000;};
    std::for_each(result.getTrajectory().begin(), result.getTrajectory().end(), multiplyH);

    std::cout << "Simulation completed. Plotting results." << std::endl;
    stochastic::plotSimulation(seihr, result, "output/seihr_simulation.png", "Stochastic Simulation of SEIHR Model");

}