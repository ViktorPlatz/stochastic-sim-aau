#include <doctest/doctest.h>

#include <filesystem>
#include <fstream>

#include "ExampleSimulations.hpp"
#include "PlotSimulation.hpp"
#include "Simulator.hpp"

using namespace stochastic;

TEST_CASE("plotSimulation generates a plot file") {
  auto vessel = seihr(100);
  Simulator sim(vessel);
  SimulationResult result;

  for (auto&& [t, state] : sim.runSingle(1)) {
    result.add(t, state);
  }

  const std::string filename = "test_output/test_plot.png";
  std::unordered_set<Species> excluded;

  CHECK_NOTHROW(
      plotSimulation(vessel, result, filename, "SEIHR Plot", excluded));
  CHECK(std::filesystem::exists(filename));

  std::filesystem::remove(filename);
}

TEST_CASE("plotSimulation throws on empty trajectory") {
  auto vessel = seihr(100);
  SimulationResult result;
  const std::string filename = "test_output/empty_plot.png";
  std::unordered_set<Species> excluded;

  CHECK_THROWS_AS(
      plotSimulation(vessel, result, filename, "Empty Plot", excluded),
      std::runtime_error);
}
