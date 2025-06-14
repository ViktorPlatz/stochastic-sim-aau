#include <ostream>
#include <doctest/doctest.h>
#include <sstream>
#include "Reaction.hpp"


using namespace stochastic;

// 2. Provide pretty-printing of the reaction network in a) human readable format and b) network graph (e.g. Fig. 4).
TEST_CASE("Pretty print format of Reaction") {
    SpeciesCombination input = Species("A") + Species("B");
    SpeciesCombination output = Species("C");
    Reaction r = (input >> 0.01) >>= output;

    std::ostringstream oss;
    oss << r;

    CHECK(oss.str() == "A + B >> 0.01 >>= C");
}
