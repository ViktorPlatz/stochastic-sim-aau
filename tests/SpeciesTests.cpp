#include <doctest/doctest.h>
#include "Species.hpp"
#include <sstream>

using namespace stochastic;

TEST_CASE("Species constructors and getters") {
    Species s1("H");
    CHECK(s1.getName() == "H");

    Species s2("Infected");
    CHECK(s2.getName() == "Infected");
}

TEST_CASE("Species equality operator") {
    Species a("A");
    Species a2("A");
    Species b("B");

    CHECK(a == a2);
    CHECK_FALSE(a == b);
}

// 2. Provide pretty-printing of the reaction network in a) human readable format and b) network graph (e.g. Fig. 4).
TEST_CASE("Species print function") {
    Species s("TestSpecies");
    std::ostringstream oss;
    s.print(oss);
    CHECK(oss.str() == "Species: TestSpecies");
}

TEST_CASE("Species hash function") {
    Species a("A");
    Species a2("A");
    Species b("B");

    std::hash<Species> hasher;
    CHECK(hasher(a) == hasher(a2));
    CHECK(hasher(a) != hasher(b));
}
