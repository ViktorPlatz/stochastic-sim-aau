#include <vector>
#include <utility>
#include "Species.hpp"
#include "SymbolTable.hpp"
#include "SimulationResult.hpp"

namespace stochastic {

    void SimulationResult::add(double time, const SymbolTable<Species, int>& state) {
        trajectory.emplace_back(time, std::make_shared<SymbolTable<Species, int>>(state));
    }

    std::vector<TimeSeries>& SimulationResult::getTrajectory() {
        return trajectory;
    }

    std::vector<int> SimulationResult::getSpeciesCounts(const Species& s) const {
        std::vector<int> values;
        values.reserve(trajectory.size());
        for (const auto& [_, state] : trajectory) {
            values.push_back(state->get(s));
        }
        return values;
    }

    std::vector<double> SimulationResult::getTimePoints() const {
        std::vector<double> times;
        times.reserve(trajectory.size());
        for (const auto& [t, _] : trajectory) {
            times.push_back(t);
        }
        return times;
    }

    SymbolTable<Species, int> SimulationResult::getFinalState() const {
        if (trajectory.empty()) {
            throw std::runtime_error("No trajectory data available.");
        }
        return *trajectory.back().second;
    }

}
