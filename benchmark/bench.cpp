#include <benchmark/benchmark.h>

#include <SimulationResult.hpp>
#include <iostream>

#include "ExampleSimulations.hpp"
#include "Simulator.hpp"

#define END_TIME 100

static void bench_single_simulation(benchmark::State& state) {
  auto n = state.range(0);
  auto numSimulations = state.range(1);

  for (auto _ : state) {
    for (int i = 0; i < numSimulations; ++i) {
      auto vessel = stochastic::seihr(n);
      stochastic::Simulator simulation(vessel, 1);

      auto gen = simulation.runSingle(END_TIME);
      for (auto&& step : gen) {
        benchmark::DoNotOptimize(step);
      }
    }
  }
}

static void bench_concurrent_simulations(benchmark::State& state) {
  auto n = state.range(0);
  auto numSimulations = state.range(1);

  auto vessel = stochastic::seihr(n);
  stochastic::Simulator simulation(vessel, 1);
  std::vector<stochastic::SimulationResult> simResults(numSimulations);

  for (auto _ : state) {
    for (const auto& timestepGroup :
         simulation.runSimulationsConcurrent(END_TIME, numSimulations)) {
      for (std::size_t i = 0; i < timestepGroup.size(); ++i) {
        if (timestepGroup[i].has_value()) {
          benchmark::DoNotOptimize(timestepGroup[i]);
          simResults[i].add(timestepGroup[i]->first, *timestepGroup[i]->second);
        }
      }
    }
    benchmark::ClobberMemory();
  }
}

static void bench_no_generator_simulations(benchmark::State& state) {
  auto n = state.range(0);
  auto numSimulations = state.range(1);

  auto vessel = stochastic::seihr(n);
  stochastic::Simulator simulation(vessel, 1);

  for (auto _ : state) {
    auto allResults =
        simulation.runSimulationsNoGenerator(END_TIME, numSimulations);
    benchmark::DoNotOptimize(allResults);
    benchmark::ClobberMemory();
  }
}

BENCHMARK(bench_single_simulation)
    ->Args({10'000, 100})
    ->Unit(benchmark::kMillisecond)
    ->Name("Single Simulation");

BENCHMARK(bench_concurrent_simulations)
    ->Args({10'000, 100})
    ->Unit(benchmark::kMillisecond)
    ->Name("Concurrent Simulations (Generator)");

BENCHMARK(bench_no_generator_simulations)
    ->Args({10'000, 100})
    ->Unit(benchmark::kMillisecond)
    ->Name("Fast Concurrent Simulations");
