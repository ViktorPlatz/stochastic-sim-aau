#include <ExampleSimulations.hpp>
#include <iostream>
#include <ostream>
#include <doctest/doctest.h>
#include "Simulator.hpp"

using namespace stochastic;

TEST_CASE("Delayed computation methods produce equivalent results") {
    Vessel vessel = stochastic::abc(50, 50, 50);
    Species x = vessel.add("X", 100);
    Species y = vessel.add("Y", 100);
    Species z = vessel.add("Z", 100);
    vessel.add(x + y >> 0.01 >>= z);

    Simulator simulator(vessel, 1);

    auto reactions = vessel.getReactions();
    auto state = vessel.getSpeciesWithValues();

    std::mt19937 gen1{1};
    std::mt19937 gen2{1};

    // Method 1: push_back
    std::vector<double> delays1;
    delays1.reserve(reactions.size());
    for (const auto& r : reactions) {
        delays1.push_back(simulator.computeDelay(r, state, gen1));
    }

    // Method 2: pre-allocated and indexed assignment
    std::vector<double> delays2(reactions.size());
    for (size_t i = 0; i < reactions.size(); ++i) {
        delays2[i] = simulator.computeDelay(reactions[i], state, gen2);
    }

    REQUIRE(delays1.size() == delays2.size());
    for (size_t i = 0; i < delays1.size(); ++i) {
        std::cout << "Delay " << i << ": " << delays1[i] << " vs " << delays2[i] << std::endl;
        if (std::isinf(delays1[i]) || std::isinf(delays2[i])) {
            REQUIRE(std::isinf(delays1[i]) == std::isinf(delays2[i]));
        } else {
            REQUIRE(std::abs(delays1[i] - delays2[i]) < 1e-6);
        }
    }
}