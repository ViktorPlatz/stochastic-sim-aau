
#ifndef PARTIALREACTION_HPP
#define PARTIALREACTION_HPP
#include "SpeciesCombination.hpp"

namespace stochastic {

    class Reaction;

    class PartialReaction {
        SpeciesCombination input;
        double rateConstant;
        public:
        //1. The library should overload operators to support the reaction rule typesetting directly in C++ code.
        friend PartialReaction operator>>(const SpeciesCombination& input, double rateConstant);
        friend Reaction operator>>=(const PartialReaction& pr, const SpeciesCombination& output);
    };

}
#endif
