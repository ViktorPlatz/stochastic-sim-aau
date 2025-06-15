#ifndef SIMULATIONRESULT_HPP
#define SIMULATIONRESULT_HPP

#include <memory>
#include <vector>
#include <utility>
#include "Species.hpp"
#include "SymbolTable.hpp"

namespace stochastic {

    using timeSeries = std::pair<double, std::shared_ptr<SymbolTable<Species, double>>>;

    class SimulationResult {
    private:
        std::vector<timeSeries> trajectory;

    public:
        void add(double time, const SymbolTable<Species, double>& state);
        std::vector<timeSeries>& getTrajectory();
        std::vector<double> getSpeciesCounts(const Species& s) const;
        std::vector<double> getTimePoints() const;
        SymbolTable<Species, double> getFinalState() const;
    };

}

#endif
