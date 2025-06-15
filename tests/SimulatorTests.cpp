#include <doctest/doctest.h>

#include <set>

#include "ExampleSimulations.hpp"
#include "Simulator.hpp"

using namespace stochastic;

constexpr double END_TIME = 5.0;

TEST_CASE("Simulator::runSingle generates valid trajectory") {
  Simulator sim(seihr(100), 42);
  auto gen = sim.runSingle(END_TIME);

  int steps = 0;
  double lastTime = -1;

  for (auto&& [time, state] : gen) {
    CHECK(time >= lastTime);
    lastTime = time;
    steps++;
  }

  CHECK(steps > 1);
}

TEST_CASE("Simulator::runSingleNoGenerator returns full trajectory") {
  Simulator sim(seihr(100), 42);
  auto result = sim.runSingleNoGenerator(END_TIME);

  CHECK_FALSE(result.empty());
  CHECK(result.front().first == doctest::Approx(0.0));
  CHECK(result.back().first <=
        END_TIME + 1);  // We add 1 because some reactions may take longer than
                        // the end time
}

TEST_CASE(
    "Simulator::runSimulationsConcurrent yields results for multiple sims") {
  int numSim = 3;
  Simulator sim(seihr(100), 42);
  auto gen = sim.runSimulationsConcurrent(END_TIME, numSim);

  int timesteps = 0;
  for (auto&& timestep : gen) {
    CHECK(timestep.size() == static_cast<size_t>(numSim));
    timesteps++;
  }

  CHECK(timesteps > 0);
}

TEST_CASE(
    "Simulator::runSimulationsNoGenerator returns multiple trajectories") {
  int numSim = 3;
  Simulator sim(seihr(100), 42);
  auto results = sim.runSimulationsNoGenerator(END_TIME, numSim);

  CHECK(results.size() == static_cast<size_t>(numSim));
  for (const auto& trajectory : results) {
    CHECK_FALSE(trajectory.empty());
  }
}

TEST_CASE("Simulator::computeDelay returns non-negative value") {
  Vessel v;
  auto S = v.add("S", 100);
  v.add(((S >> 1.0) >>= Species("B")));

  Simulator sim(v, 123);
  auto r = v.getReactions().front();
  auto state = v.getSymbolTable();

  double delay = sim.computeDelay(r, state);
  CHECK(delay >= 0.0);
}

TEST_CASE("Simulator::react updates species state correctly") {
  Vessel v;
  auto A = v.add("A", 10);
  auto B = v.add("B", 5);
  v.add((A >> 1.0) >>= B);

  Simulator sim(v);
  auto r = v.getReactions().front();
  auto state = v.getSymbolTable();

  double beforeA = state.get(A);
  double beforeB = state.get(B);

  sim.react(r, state);

  CHECK(state.get(A) == doctest::Approx(beforeA - 1));
  CHECK(state.get(B) == doctest::Approx(beforeB + 1));
}