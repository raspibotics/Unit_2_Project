#ifndef SIGNAL_PROCESSING_H
#define SIGNAL_PROCESSING_H

#include <vector>
#include "ChebyshevTypeI.hpp"

std::vector<double> downsample_signal(std::vector<double> signal, int factor, ChebyshevI anti_aliasing);

double harmonic_product_spectrum(std::vector<double> signal);

double tuning_correction(std::vector<double> instrument_tuning_frequencies);

#endif
