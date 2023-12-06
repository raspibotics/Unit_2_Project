#include "include/SignalProcessing.hpp"


// Low pass filter used for downsampling algorithim
filter_params intialise_filter(){
    // Parameters to use in the filter
    filter_params params; 
    params.poles = 6;
    params.filter_type = "LP";
    params.cutoff_frequency = 0.4;
    params.percent_ripple = 0.5;
    return params;
}
// TODO - figure out how to intialise this filter
ChebyshevI anti_aliasing();

std::vector<double> downsample_signal(std::vector<double> signal, int factor, ChebyshevI anti_aliasing){
    std::vector<double> filtered_signal;
    std::vector<double> downsampled; 
    // Apply antialising filter to signal
    filtered_signal = anti_aliasing.apply_filter(signal);
    for (int i = 0; i < filtered_signal.size(); i+=factor){
        downsampled.push_back(filtered_signal[i]);
    }
    return downsampled;
}

double harmonic_product_spectrum(std::vector<double> signal){
    
}