#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

#include "PlotSimulation.hpp"
#include "SimulationResult.hpp"
#include "ExampleSimulations.hpp"
#include "Graph.hpp"
#include "Simulator.hpp"

#define END_TIME 24
#define NUM_SIMULATIONS 5
#define N 10000

int main() {
    auto seihr = stochastic::seihr(N);
    stochastic::Graph::saveDotGraphToFile(seihr, "output/seihr_simulation.dot");

    std::cout << "Starting " << NUM_SIMULATIONS << " simulations with "
              << seihr.getSpecies().size() << " species, "
              << seihr.getReactions().size() << " reactions, "
              << "population size N = " << N << ", "
              << "and end time = " << END_TIME << "." << std::endl;

    stochastic::Simulator simulation(seihr);
    auto allResults = simulation.runSimulationsNoGenerator(END_TIME, NUM_SIMULATIONS);

    std::vector<stochastic::SimulationResult> simResults(NUM_SIMULATIONS);
    std::vector<double> h_values;
    stochastic::Species h_species = stochastic::Species{"H"};

    for (std::size_t i = 0; i < allResults.size(); ++i) {
        for (const auto& [time, state] : allResults[i]) {
            simResults[i].add(time, state);
            h_values.push_back(state.get(h_species));
        }
    }

    auto h_average = std::accumulate(h_values.begin(), h_values.end(), 0.0) / h_values.size();
    std::cout << "Average H value: " << h_average << '\n';

    std::unordered_map<std::string, double> avgCounts;

    for (const auto &species : seihr.getSpecies()) {
        double total = 0.0;
        for (const auto &result : simResults) {
            total += result.getFinalState().get(species);
        }
        avgCounts[species.getName()] = total / NUM_SIMULATIONS;
    }

    std::cout << "\nAverage species counts at t = " << END_TIME << " (" << NUM_SIMULATIONS
              << " runs):\n";

    for (const auto &[name, avg] : avgCounts) {
        std::cout << "  " << name << ": " << avg << '\n';
    }

    return 0;
}
