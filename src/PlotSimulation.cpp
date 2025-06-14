#include "PlotSimulation.hpp"

#include <unordered_set>
#include "matplotlibcpp.h"


namespace plt = matplotlibcpp;

namespace stochastic {

    void plotSimulation(Vessel& vessel, SimulationResult& simulationResult, const std::string& filename, const std::string& title, const std::unordered_set<Species>& excludedSpecies) {
        plt::clf(); // Clear the current figure to avoid overlapping plots
        auto& trajectory = simulationResult.getTrajectory();
        if (trajectory.empty()) {
            throw std::runtime_error("Cannot plot an empty trajectory.");
        }

        std::vector<double> timePoints = simulationResult.getTimePoints();

        auto speciesMap = vessel.getSpeciesWithValues();

        for (const auto& species : vessel.getSpecies()) {
            std::vector<double> values = simulationResult.getSpeciesCounts(species);

            if (excludedSpecies.count(species.getName()) > 0) {
                continue;
            }

            plt::named_plot(species.getName(), timePoints, values);
        }

        plt::title(title);
        plt::xlabel("Time");
        plt::ylabel("Quantity");
        plt::legend({{"loc", "upper right"}});
        plt::title(title);
        plt::tight_layout();
        plt::save(filename);
        //plt::show();
    }

}
