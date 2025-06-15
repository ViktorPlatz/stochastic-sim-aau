#include <doctest/doctest.h>
#include <ostream>
#include <sstream>
#include "StochasticLib.hpp"

using namespace stochastic;

// 2. Provide pretty-printing of the reaction network in a) human readable
// format and b) network graph (e.g. Fig. 4).
TEST_CASE("Pretty print format of Reaction") {
  SpeciesCombination input = Species("A") + Species("B");
  SpeciesCombination output = Species("C");
  Reaction r = (input >> 0.01) >>= output;

  std::ostringstream oss;
  oss << r;

  CHECK(oss.str() == "A + B >> 0.01 >>= C");
}

TEST_CASE("Constructing a Reaction using >> and >>=") {
  Species a("A"), b("B"), c("C");
  SpeciesCombination input = a + b;
  SpeciesCombination output = c;
  double rate = 0.05;

  Reaction r = (input >> rate) >>= output;

  CHECK(r.getRateConstant() == doctest::Approx(rate));
  CHECK(r.getInput() == std::vector{a, b});
  CHECK(r.getOutput() == std::vector{c});
}

TEST_CASE("Reaction equality operator") {
  SpeciesCombination input = Species("X") + Species("Y");
  SpeciesCombination output = Species("Z");

  Reaction r1 = (input >> 0.1) >>= output;
  Reaction r2 = (input >> 0.1) >>= output;
  Reaction r3 = (Species("A") + Species("B") >> 0.1) >>= Species("Z");

  CHECK(r1 == r2);
  CHECK_FALSE(r1 == r3);
}

TEST_CASE("Getter methods of Reaction") {
  Species a("A"), b("B"), c("C");
  SpeciesCombination input = a + b;
  SpeciesCombination output = c;
  double rate = 0.2;

  Reaction r = (input >> rate) >>= output;

  CHECK(r.getInput() == std::vector<Species>{a, b});
  CHECK(r.getOutput() == std::vector<Species>{c});
  CHECK(r.getRateConstant() == doctest::Approx(rate));
}
