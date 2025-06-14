#ifndef VESSEL_HPP
#define VESSEL_HPP
#include <string>
#include <vector>
#include "SymbolTable.hpp"
#include "Reaction.hpp"
#include "Species.hpp"

namespace stochastic {

    class Vessel {
        std::vector<Reaction> reactions; // TODO: change data structure
        SymbolTable<Species, double> species;
        public:
        const Species add(const std::string& name, double count);
        void add(const Reaction& reaction);
        const Species environment();
        const std::vector<Reaction> getReactions() const;
        const std::vector<Species> getSpecies() const;
        const SymbolTable<Species, double> getSpeciesWithValues() const; // TODO: Fix these functions
        std::vector<std::string> getSpeciesNames() const;
    };

}

#endif
