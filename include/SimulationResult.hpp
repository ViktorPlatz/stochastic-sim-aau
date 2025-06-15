#ifndef SIMULATIONRESULT_HPP
#define SIMULATIONRESULT_HPP

#include <memory>
#include <utility>
#include <vector>

#include "Species.hpp"
#include "SymbolTable.hpp"

namespace stochastic {

using TimeSeries =
    std::pair<double, std::shared_ptr<SymbolTable<Species, int>>>;

class SimulationResult {
 private:
  std::vector<TimeSeries> trajectory;

 public:
  void add(double time, const SymbolTable<Species, int>& state);
  std::vector<TimeSeries>& getTrajectory();
  std::vector<int> getSpeciesCounts(const Species& s) const;
  std::vector<double> getTimePoints() const;
  SymbolTable<Species, int> getFinalState() const;
};

}  // namespace stochastic

#endif
