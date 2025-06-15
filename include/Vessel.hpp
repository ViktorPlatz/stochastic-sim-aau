#ifndef VESSEL_HPP
#define VESSEL_HPP
#include <string>
#include <vector>

#include "Reaction.hpp"
#include "Species.hpp"
#include "SymbolTable.hpp"

namespace stochastic {

class Vessel {
  std::vector<Reaction> reactions;
  SymbolTable<Species, int> species;

 public:
  const Species add(const std::string& name, int count);
  void add(const Reaction& reaction);
  const Species environment();
  const std::vector<Reaction> getReactions() const;
  const std::vector<Species> getSpecies() const;
  const SymbolTable<Species, int> getSymbolTable() const;
  std::vector<std::string> getSpeciesNames() const;
  double estimateMaxTimesteps(double endTime) const;
};

}  // namespace stochastic

#endif
