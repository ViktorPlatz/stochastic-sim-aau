#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP
#include <generator>
#include <memory>
#include <random>
#include <vector>

#include "Reaction.hpp"
#include "Vessel.hpp"

namespace stochastic {

using TimeSeries =
    std::pair<double, std::shared_ptr<SymbolTable<Species, int>>>;
using TimeSeriesVector = std::vector<std::optional<TimeSeries>>;
class Simulator {
 private:
  Vessel vessel;
  std::random_device rd{};
  const unsigned int seed;

 public:
  Simulator(Vessel& vessel, unsigned int seed = 0);
  std::generator<TimeSeries> runSingle(double endTime);
  std::generator<TimeSeriesVector> runSimulationsConcurrent(double endTime,
                                                            int numSimulations);
  std::vector<std::vector<TimeSeries>> runSimulationsNoGenerator(
      double endTime, int numSimulations);
  double computeDelay(const Reaction& reaction,
                      const SymbolTable<Species, int>& state,
                      std::mt19937& gen);
  void react(const Reaction& reaction, SymbolTable<Species, int>& state);
};

}  // namespace stochastic

#endif
