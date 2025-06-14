
#ifndef PARTIALREACTION_HPP
#define PARTIALREACTION_HPP
#include "Species.hpp"
#include "SpeciesCombination.hpp"
#include "Reaction.hpp"

namespace stochastic {

    class Reaction; //TODO: fix this circular dependency

    class PartialReaction {
        SpeciesCombination input;
        double rateConstant;
        public:
        friend PartialReaction operator>>(const SpeciesCombination& input, double rateConstant);
        friend Reaction operator>>=(const PartialReaction& pr, const SpeciesCombination& output);
    };

}
#endif
