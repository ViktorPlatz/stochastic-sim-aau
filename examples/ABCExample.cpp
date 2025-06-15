#include <iostream>
#include <PlotSimulation.hpp>

#include "SimulationResult.hpp"
#include "ExampleSimulations.hpp"
#include "Graph.hpp"
#include "Simulator.hpp"

struct abc_val
{
    int a;
    int b;
    int c;
};

int main()

{
    std::vector<abc_val> abc_values = {{100, 0, 1}, {100, 0, 2}, {50, 50, 1}};

    for (int i = 0; i < abc_values.size(); i++) {
        const auto& e = abc_values[i];
        auto vessel = stochastic::abc(e.a, e.b, e.c);
        stochastic::Simulator sim{vessel, 0};
        std::string num = std::to_string(i + 1);
        std::cout << "=== Running ABC Simulation " << num << " ===" << std::endl;

        stochastic::SimulationResult result;
        for (auto timeseries : sim.runSingle(2000)) {
            result.add(timeseries.first, *timeseries.second);
        }

        std::string fileNum = std::to_string(i + 1);
        std::string imgFilename = "output/abc" + fileNum + ".png";
        std::string dotFilename = "output/abc" + fileNum + ".dot";

        stochastic::plotSimulation(vessel, result, imgFilename, "ABC Simulation " + fileNum);
        stochastic::Graph::saveDotGraphToFile(vessel, dotFilename);
    }


    return 0;
}
