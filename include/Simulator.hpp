#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP
#include <memory>
#include <vector>
#include <random>
#include <generator>
#include "Reaction.hpp"
#include "Vessel.hpp"


namespace stochastic {

    using timeSeries = std::pair<double, SymbolTable<Species, double>>; // TODO: change to sharedptr
    using timeSeriesVector = std::vector<std::optional<timeSeries>>;
    class Simulator {
    private:
        Vessel vessel;
        std::random_device rd{};
        const unsigned int seed;
    public:
        Simulator(const Vessel& vessel, unsigned int seed = 0);
        std::generator<timeSeries> runSingle(double endTime);
        std::generator<timeSeriesVector> runSimulationsConcurrent(double endTime, int numSimulations);
        std::vector<timeSeries> runSingleNoGenerator(double endTime);
        std::vector<std::vector<timeSeries>> runSimulationsNoGenerator(double endTime, int numSimulations);
        double computeDelay(const Reaction& reaction, const SymbolTable<Species, double>& state);
        void react(const Reaction& reaction, SymbolTable<Species, double>& state);
    };

}

#endif
