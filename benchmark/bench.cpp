#include <iostream>
#include <SimulationResult.hpp>
#include <benchmark/benchmark.h>
#include "Simulator.hpp"
#include "ExampleSimulations.hpp"

#define END_TIME 100

namespace stochastic {
    class SimulationResult;
}

static void bench_single_simulation(benchmark::State& state) {
    auto n = state.range(0);

    for (auto _ : state) {

        auto vessel = stochastic::seihr(n);
        stochastic::Simulator simulation(vessel);

        auto gen = simulation.runSingle(END_TIME);
        for (auto&& step : gen) {
            benchmark::DoNotOptimize(step);
        }
    }
}

static void bench_concurrent_simulations(benchmark::State& state) {
    auto n = state.range(0);
    auto numSimulations = state.range(1);

    for (auto _ : state) {

        auto vessel = stochastic::seihr(n);
        stochastic::Simulator simulation(vessel);
        std::vector<stochastic::SimulationResult> simResults(numSimulations);

        for (const auto &timestepGroup : simulation.runSimulationsConcurrent(END_TIME, numSimulations)) {
            for (std::size_t i = 0; i < timestepGroup.size(); ++i) {
                if (timestepGroup[i].has_value()) {
                    benchmark::DoNotOptimize(*timestepGroup[i]);
                    simResults[i].add(timestepGroup[i]->first, timestepGroup[i]->second);
                }
            }
        }

        benchmark::ClobberMemory();
    }
}

static void bench_no_generator_simulations(benchmark::State& state) {
    auto n = state.range(0);
    auto numSimulations = state.range(1);

    for (auto _ : state) {
        auto vessel = stochastic::seihr(n);
        stochastic::Simulator simulation(vessel);
        auto allResults = simulation.runSimulationsNoGenerator(END_TIME, numSimulations);
        benchmark::DoNotOptimize(allResults);
        benchmark::ClobberMemory();
    }
}

static void bench_no_generator_single_simulation(benchmark::State& state) {
    auto n = state.range(0);

    for (auto _ : state) {
        auto vessel = stochastic::seihr(n);
        stochastic::Simulator simulation(vessel);
        auto result = simulation.runSingleNoGenerator(END_TIME);
        benchmark::DoNotOptimize(result);
        benchmark::ClobberMemory();
    }
}

BENCHMARK(bench_single_simulation)
    ->Arg(10'000)
    ->Unit(benchmark::kMillisecond)
    ->Name("Single Simulation");

BENCHMARK(bench_concurrent_simulations)
    ->Args({10'000, 5})
    ->Unit(benchmark::kMillisecond)
    ->Name("Concurrent Simulations");

BENCHMARK(bench_no_generator_simulations)
    ->Args({10'000, 100})
    ->Unit(benchmark::kMillisecond)
    ->Name("Fast Concurrent Simulations");

BENCHMARK(bench_no_generator_single_simulation)
    ->Arg(10'000)
    ->Unit(benchmark::kMillisecond)
    ->Name("Fast Single Simulation");

