#ifndef SIGNAL_PROCESSING_HPP
#define SIGNAL_PROCESSING_HPP

#include <vector>
#include "ChebyshevTypeI.hpp"
#include "Instrument.hpp"

std::vector<double> downsample_signal(std::vector<double> signal, int factor, ChebyshevI anti_aliasing);

double harmonic_product_spectrum(std::vector<double> signal);

double tuning_correction(double fundamental_frequency, Instrument instrument);

#endif
