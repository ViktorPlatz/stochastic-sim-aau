#include "Reaction.hpp"

namespace stochastic {

    Reaction operator >>=(const PartialReaction& pr, const SpeciesCombination& output) {
        Reaction r;
        r.input = pr.input;
        r.output = output;
        r.rateConstant = pr.rateConstant;
        return r;
    }

}