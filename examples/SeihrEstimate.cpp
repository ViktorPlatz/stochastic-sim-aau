#include <iostream>
#include "StochasticLib.hpp"

#define NDK 5'882'763
#define NNJ 589'755

double compute_peak_hospitalized(int population, double end_time,
                                 unsigned int seed = 0) {
  auto seihr_model = stochastic::Seihr(population);
  auto simulator = stochastic::Simulator(seihr_model, seed);
  const auto H = stochastic::Species("H");

  double peakH = 0;
  for (const auto& [t, state] : simulator.runSingle(end_time)) {
    peakH = std::max(peakH, static_cast<double>(state->get(H)));
  }
  return peakH;
}

int main() {
  constexpr double end_time = 100;

  double peak_ndk = compute_peak_hospitalized(NDK, end_time);
  std::cout << "NDK peak hospitalized: " << peak_ndk << '\n';

  double peak_nnj = compute_peak_hospitalized(NNJ, end_time);
  std::cout << "NNJ peak hospitalized: " << peak_nnj << '\n';

  return 0;
}
