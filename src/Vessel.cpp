#include <string>
#include "Vessel.hpp"


namespace stochastic {

    const Species Vessel::add(const std::string& name, double count) {
        Species _species{name};
        species.add(_species, count);
        return _species;
    }

    void Vessel::add(const Reaction& reaction) {
        for (const auto& r : this->reactions) {
            if (r == reaction) {
                throw std::runtime_error("Reaction already exists in vessel");
            }
        }
        reactions.push_back(reaction);
    }

    const Species Vessel::environment() { // TODO: Check if this is correct
        Species env{"env"};
        if (!species.contains(env)) {
            species.add(env, 0);
        }
        return env;
    }

    const std::vector<Reaction> Vessel::getReactions() const {
        return reactions;
    }

    const std::vector<Species> Vessel::getSpecies() const {
        return species.getAllKeys();
    }

    std::vector<std::string> Vessel::getSpeciesNames() const {
        std::vector<std::string> names;
        for (const auto& s : species.getAllKeys()) {
            names.push_back(s.getName());
        }
        return names;
    }

    const SymbolTable<Species, double> Vessel::getSpeciesWithValues() const {
        return species;
    }
}