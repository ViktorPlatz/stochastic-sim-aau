#include <iostream>
#include <PlotSimulation.hpp>

#include "SimulationResult.hpp"
#include "ExampleSimulations.hpp"
#include "Graph.hpp"
#include "Simulator.hpp"

#include <vector>
#include <unordered_map>
#include <unordered_set>

#define END_TIME 48.0
#define NUM_SIMULATIONS 15

int main() {
    auto circadian_rhythm = stochastic::circadian_rhythm();
    stochastic::Graph::saveDotGraphToFile(circadian_rhythm, "output/circadian_simulation.dot");

    std::cout << "Starting " << NUM_SIMULATIONS << " simulations with "
              << circadian_rhythm.getSpecies().size() << " species and "
              << circadian_rhythm.getReactions().size() << " reactions." << std::endl;

    stochastic::Simulator simulation(circadian_rhythm, 0);
    auto simConcurrent = simulation.runSimulationsConcurrent(END_TIME, NUM_SIMULATIONS);

    std::vector<stochastic::SimulationResult> simResults(NUM_SIMULATIONS);

    for (const auto& timestepGroup : simConcurrent) {
        for (std::size_t i = 0; i < timestepGroup.size(); ++i) {
            if (timestepGroup[i].has_value()) {
                const auto& [time, state] = *timestepGroup[i];
                simResults[i].add(time, state);
            }
        }
    }

    std::unordered_map<std::string, double> avgCounts;

    for (const auto& species : circadian_rhythm.getSpecies()) {
        double total = 0.0;
        for (const auto& result : simResults) {
            total += result.getFinalState().get(species);
        }
        avgCounts[species.getName()] = total / NUM_SIMULATIONS;
    }

    std::cout << "\nAverage species counts at t = " << END_TIME << " (" << NUM_SIMULATIONS
              << " runs):\n";
    for (const auto& [name, avg] : avgCounts) {
        std::cout << "  " << name << ": " << avg << '\n';
    }

    return 0;
}
