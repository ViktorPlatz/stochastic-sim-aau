#ifndef REACTION_HPP
#define REACTION_HPP
#include "Species.hpp"
#include "SpeciesCombination.hpp"
#include "PartialReaction.hpp"

namespace stochastic {

    class Reaction {
        SpeciesCombination input;
        SpeciesCombination output;
        double rateConstant;
    public:
        friend Reaction operator>>=(const PartialReaction& pr, const SpeciesCombination& output);
    };

    Reaction operator >>=(const PartialReaction& pr, const SpeciesCombination& output);

}

#endif
