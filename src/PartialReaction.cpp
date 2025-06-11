#include "PartialReaction.hpp"

namespace stochastic {

    PartialReaction operator>>(const SpeciesCombination& input, double rateConstant) {
        PartialReaction pr;
        pr.input = input;
        pr.rateConstant = rateConstant;
        return pr;
    }


}