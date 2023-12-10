#ifndef SIGNAL_PROCESSING_HPP
#define SIGNAL_PROCESSING_HPP

#include <vector>
#include "ChebyshevTypeI.hpp"
#include "Instrument.hpp"

std::vector<double> downsample_signal(const std::vector<double> &signal, int factor, ChebyshevI anti_aliasing);

double harmonic_product_spectrum(const std::vector<double> &signal);

double tuning_correction(double fundamental_frequency, Instrument instrument);

#endif
