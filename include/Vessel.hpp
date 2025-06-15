#ifndef VESSEL_HPP
#define VESSEL_HPP
#include <string>
#include <vector>

#include "Reaction.hpp"
#include "Species.hpp"
#include "SymbolTable.hpp"

namespace stochastic {
/* 3. Implement a generic symbol table to store and lookup objects of
 user-defined key and value types. Support
failure cases when a) the table does not contain a looked up symbol, b) the table already contains a symbol that
is being added. Demonstrate the usage of the symbol table with the reactants (names and initial counts).*/

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
