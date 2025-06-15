#include <doctest/doctest.h>
#include "StochasticLib.hpp"

using namespace stochastic;

constexpr double END_TIME = 5.0;

TEST_CASE("Simulator::runSingle generates valid trajectory") {
  auto vessel = Seihr(100);
  Simulator sim(vessel, 42);
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

TEST_CASE(
    "Simulator::runSimulationsConcurrent yields results for multiple sims") {
  auto vessel = Seihr(100);
  int numSim = 3;
  Simulator sim(vessel, 42);
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
  auto vessel = Seihr(100);
  int numSim = 3;
  Simulator sim(vessel, 42);
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
  auto gen = std::mt19937{123};

  double delay = sim.computeDelay(r, state, gen);
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