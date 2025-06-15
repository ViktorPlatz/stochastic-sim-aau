#include "Reaction.hpp"
#include <iomanip>
namespace stochastic {

    Reaction operator >>=(const PartialReaction& pr, const SpeciesCombination& output) {
        Reaction r;
        r.input = pr.input;
        r.output = output;
        r.rateConstant = pr.rateConstant;
        return r;
    }

    bool Reaction::operator==(const Reaction& other) const {
        return input == other.input &&
               output == other.output &&
               rateConstant == other.rateConstant;
    }

    PartialReaction operator>>(const SpeciesCombination& input, double rateConstant) {
        PartialReaction pr;
        pr.input = input;
        pr.rateConstant = rateConstant;
        return pr;
    }

    const std::vector<Species>& Reaction::getInput() const {
        return input.getSpeciesList();
    }
    const std::vector<Species>& Reaction::getOutput() const {
        return output.getSpeciesList();
    }
    const double& Reaction::getRateConstant() const {
        return rateConstant;
    }

    std::ostream& operator<<(std::ostream& os, const Reaction& r) {
        os << r.input << " >> " << r.rateConstant << " >>= " << r.output;
        return os;
    }

}
