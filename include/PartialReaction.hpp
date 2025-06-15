
#ifndef PARTIALREACTION_HPP
#define PARTIALREACTION_HPP
#include "SpeciesCombination.hpp"

namespace stochastic {

    class Reaction;

    class PartialReaction {
        SpeciesCombination input;
        double rateConstant;
        public:
        friend PartialReaction operator>>(const SpeciesCombination& input, double rateConstant);
        friend Reaction operator>>=(const PartialReaction& pr, const SpeciesCombination& output);
    };

}
#endif
