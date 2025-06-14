#ifndef REACTION_HPP
#define REACTION_HPP
#include "Species.hpp"
#include "SpeciesCombination.hpp"
#include "PartialReaction.hpp"

namespace stochastic {

    class PartialReaction; //TODO: fix this circular dependency

    class Reaction {
        SpeciesCombination input;
        SpeciesCombination output;
        double rateConstant;
    public:
        friend Reaction operator>>=(const PartialReaction& pr, const SpeciesCombination& output);
        bool operator==(const Reaction& other) const;
        const std::vector<Species>& getInput() const;
        const std::vector<Species>& getOutput() const;
        const double& getRateConstant() const;

        friend std::ostream& operator<<(std::ostream& os, const Reaction& r);
    };

    Reaction operator >>=(const PartialReaction& pr, const SpeciesCombination& output);
    PartialReaction operator>>(const SpeciesCombination& input, double rateConstant);
}

#endif
