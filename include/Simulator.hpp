#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP
#include <generator>
#include <memory>
#include <random>
#include <vector>

#include "Reaction.hpp"
#include "Vessel.hpp"

namespace stochastic {
// 4. Implement the stochastic simulation (Alg. 1) of the system using the reaction rules.
using TimeSeries = std::pair<double, std::shared_ptr<SymbolTable<Species, int>>>;
using TimeSeriesVector = std::vector<std::optional<TimeSeries>>;
class Simulator {
 private:
  Vessel vessel;
  std::random_device rd{};
  const unsigned int seed;

 public:
  Simulator(Vessel& vessel, unsigned int seed = 0);
  /*7. Implement a generic support for (any) user-supplied state observer function object or provide a lazy trajectory
  generation interface (coroutine). The observer itself should be part by the user/test program and not part of
  the library. To demonstrate the generic support, estimate the peak of hospitalized agents in Covid-19 example
  without storing an entire trajectory. Record the peak hospitalization values for population sizes of NNJ and NDK.*/
  std::generator<TimeSeries> runSingle(double endTime);
  std::generator<TimeSeriesVector> runSimulationsConcurrent(double endTime,
                                                            int numSimulations);
  /*8. Implement support for multiple CPU cores by parallelizing the computation of several simulations at the same
time. Estimate the likely (average) value of the hospitalized peak over 100 simulations.*/
  std::vector<std::vector<TimeSeries>> runSimulationsNoGenerator(
      double endTime, int numSimulations);
  double computeDelay(const Reaction& reaction,
                      const SymbolTable<Species, int>& state,
                      std::mt19937& gen);
  void react(const Reaction& reaction, SymbolTable<Species, int>& state);
};

}  // namespace stochastic

#endif
