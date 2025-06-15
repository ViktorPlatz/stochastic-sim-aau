#include <string>
#include "Vessel.hpp"


namespace stochastic {

    const Species Vessel::add(const std::string& name, int count) {
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

    const Species Vessel::environment() {
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

    const SymbolTable<Species, int> Vessel::getSymbolTable() const {
        return species;
    }

    double Vessel::estimateMaxTimesteps(double endTime) const {
        auto reactions = getReactions();
        if (reactions.empty()) return 1.0;

        double minDelay = std::numeric_limits<double>::infinity();

        for (const auto& r : reactions) {
            double propensity = r.getRateConstant();
            for (const auto& s : r.getInput()) {
                propensity *= 1.0;
            }
            if (propensity > 0.0) {
                double expectedDelay = 1.0 / propensity;
                minDelay = std::min(minDelay, expectedDelay);
            }
        }

        if (!std::isfinite(minDelay) || minDelay <= 0.0)
            return 1.0;

        return endTime / minDelay;
    }
}