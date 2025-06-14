#include "Simulator.hpp"
#include "TSQueue.hpp"
#include <random>
#include <generator>
#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>

namespace stochastic {


    Simulator::Simulator(const Vessel& vessel, unsigned int seed)
        : vessel(vessel), seed(seed) {}

    double Simulator::computeDelay(const Reaction& reaction, const SymbolTable<Species, double>& state) {
    	thread_local std::mt19937 gen{seed == 0 ? rd() : seed};

  		std::vector<double> values;
    	values.reserve(reaction.getInput().size());

        for (const auto& species : reaction.getInput()) {
            values.push_back(state.get(species));
        }

        double product = std::accumulate(values.begin(), values.end(), 1.0, std::multiplies<double>());

        std::exponential_distribution<double> dist(reaction.getRateConstant() * product);
        return dist(gen);
	}

    void Simulator::react(const Reaction& reaction, SymbolTable<Species, double>& state){
        if (std::any_of(reaction.getInput().begin(), reaction.getInput().end(),
                    [&state](const Species& s) { return state.get(s) < 1.0; })) {
            return;
        }

        for (const auto& species : reaction.getInput()) {
            state.get(species) -= 1;
        }
        for (const auto& species : reaction.getOutput()) {
            state.get(species) += 1;
        }
    }

    std::generator<timeSeries> Simulator::runSingle(double endTime) {

        auto reactions = vessel.getReactions();

        if (reactions.empty()) {
            throw std::runtime_error("No reactions defined in the vessel.");
        }

        auto currentTime = 0.0;

        SymbolTable<Species, double> state = vessel.getSpeciesWithValues();

        co_yield std::make_pair(currentTime, state);

        while (currentTime <= endTime) {
            std::vector<double> delays;
            delays.reserve(reactions.size());

            for (const auto& r : reactions) {
                delays.push_back(computeDelay(r, state));
            }

            auto minDelayIt = std::min_element(delays.begin(), delays.end());

            auto i = std::distance(delays.begin(), minDelayIt);
            currentTime += *minDelayIt;

            react(reactions[i], state);
            co_yield std::make_pair(currentTime, state);
        }
    }

    std::vector<timeSeries> Simulator::runSingleNoGenerator(double endTime) {
        std::vector<timeSeries> result;

        auto reactions = vessel.getReactions();

        if (reactions.empty()) {
            throw std::runtime_error("No reactions defined in the vessel.");
        }

        auto currentTime = 0.0;

        SymbolTable<Species, double> state = vessel.getSpeciesWithValues();

        result.emplace_back(currentTime, state);

        while (currentTime <= endTime) {
            std::vector<double> delays;
            delays.reserve(reactions.size());

            for (const auto& r : reactions) {
                delays.push_back(computeDelay(r, state));
            }

            auto minDelayIt = std::min_element(delays.begin(), delays.end());

            auto i = std::distance(delays.begin(), minDelayIt);
            currentTime += *minDelayIt;

            react(reactions[i], state);
            result.emplace_back(currentTime, state);
        }

        return result;
    }

    std::generator<timeSeriesVector> Simulator::runSimulationsConcurrent(double endTime, int numSimulations) {
        using Queue = TSQueue<std::optional<timeSeries>>;
        std::vector<std::shared_ptr<Queue>> queues(numSimulations);
        std::vector<bool> done(numSimulations, false);

        auto simulationJob = [this, endTime](std::shared_ptr<Queue> q) {
            for (auto&& step : runSingle(endTime)) {
                q->push(step);
            }
            q->push(std::nullopt);
        };

        std::vector<std::jthread> workers;
        for (int i = 0; i < numSimulations; ++i) {
            queues[i] = std::make_shared<Queue>();
            workers.emplace_back(simulationJob, queues[i]);
        }

        while (true) {
            bool all_finished = true;
            timeSeriesVector timestep(numSimulations);

            for (int i = 0; i < numSimulations; ++i) {
                if (done[i]) continue;

                auto val = queues[i]->pop();
                if (val) {
                    timestep[i] = *val;
                    all_finished = false;
                } else {
                    done[i] = true;
                }
            }

            if (std::any_of(timestep.begin(), timestep.end(), [](const auto& v) { return v.has_value(); }))
                co_yield timestep;

            if (all_finished) break;
        }
    }

    std::vector<std::vector<timeSeries>> Simulator::runSimulationsNoGenerator(double endTime, int numSimulations) {
        std::vector<std::vector<timeSeries>> results(numSimulations);

        auto job = [this, endTime]() {
            std::vector<timeSeries> result;
            for (auto&& step : runSingle(endTime)) {
                result.push_back(step);
            }
            return result;
        };

        std::vector<std::future<std::vector<timeSeries>>> futures;
        futures.reserve(numSimulations);

        for (int i = 0; i < numSimulations; ++i) {
            futures.push_back(std::async(std::launch::async, job));
        }

        for (int i = 0; i < numSimulations; ++i) {
            results[i] = futures[i].get();
        }

        return results;
    }



}