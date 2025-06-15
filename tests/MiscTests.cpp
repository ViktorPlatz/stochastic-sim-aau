#include <doctest/doctest.h>

#include <ExampleSimulations.hpp>
#include <iostream>
#include <ostream>

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
  auto state = vessel.getSymbolTable();

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
    std::cout << "Delay " << i << ": " << delays1[i] << " vs " << delays2[i]
              << std::endl;
    if (std::isinf(delays1[i]) || std::isinf(delays2[i])) {
      REQUIRE(std::isinf(delays1[i]) == std::isinf(delays2[i]));
    } else {
      REQUIRE(std::abs(delays1[i] - delays2[i]) < 1e-6);
    }
  }
}

TEST_CASE("Vessel estimates max timesteps correctly") {
  Species A("A");

  Reaction r = A >> 2.0 >>= A;

  Vessel v;
  v.add("A", 1.0);
  v.add(r);

  double endTime = 10.0;
  double estimatedSteps = v.estimateMaxTimesteps(endTime);
  std::cout << "Estimated steps: " << estimatedSteps << std::endl;

  CHECK(estimatedSteps == doctest::Approx(20.0).epsilon(0.001));

  int numRuns = 100;
  double totalSteps = 0.0;

  for (int i = 0; i < numRuns; ++i) {
    Simulator simulator(v, i + 1);
    auto results = simulator.runSingleNoGenerator(endTime);
    totalSteps += results.size();
  }

  double avgSteps = totalSteps / numRuns;
  std::cout << "Average actual steps: " << avgSteps << std::endl;

  // Allow 15% tolerance due to randomness
  CHECK(avgSteps == doctest::Approx(estimatedSteps).epsilon(0.15));
}