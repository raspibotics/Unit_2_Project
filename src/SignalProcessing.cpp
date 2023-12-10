#include "include/SignalProcessing.hpp"
#include "include/Config.hpp"
#include <iostream>
#include <algorithm>

// Function to downsample a signal 
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

// Function to perform harmonic product spectrum on a signal 
double harmonic_product_spectrum(std::vector<double> signal){
    double fundamental_frequency = 0;
    int downsample_cyles = 4; 
    // 2D vector to hold spectrums
    std::vector<std::vector<double>> spectrums;
    spectrums.push_back(signal);
    // Setup a anti-aliasing filter parameters
    filter_params filter_setup; 
    filter_setup.poles = 8;
    filter_setup.filter_type = "LP";
    filter_setup.percent_ripple = 0.5;
    // Create a filter object to pass to downsampler
    ChebyshevI anti_aliasing_filter(filter_setup);
    anti_aliasing_filter.calculate_coefficients();
    // Resample the signal at different rates 
    for (int n = 2; n <= downsample_cyles; n++){ 
        // Adjust the filter parameters to the correct nyquist frequency 
        filter_setup.cutoff_frequency = 0.5/n;
        anti_aliasing_filter.set_filter_params(filter_setup);
        anti_aliasing_filter.calculate_coefficients();
        // Downsample the signal and add the spectrum to the array
        std::vector<double> w_n = downsample_signal(signal, n, anti_aliasing_filter);
        spectrums.push_back(w_n);
    }
    // Print the contents of the 2D vector
    for (int i = 0; i < spectrums.size(); ++i) {
        for (int j = 0; j < spectrums[i].size(); ++j) {
            std::cout << spectrums[i][j] << " ";
        }
        std::cout << std::endl;
    }
    // Multiply each element in the vector together - only go up to the maximum index of the most downsampled spectrum
    std::vector<double> hps;
    for (int i = 0; i < spectrums[downsample_cyles-1].size(); i++){
        double element_product = 1; 
        for (int j = downsample_cyles - 1; j >= 0; j--){
            element_product *= spectrums[j][i];
        }
        hps.push_back(element_product);
    }
    // Find max element in hps vector
    auto max_iter = std::max_element(hps.begin(), hps.end());
    if (max_iter != hps.end()) {
        fundamental_frequency = *max_iter;
    }
    std::cout << "FUNDAMENTAL FREQUENCY:" << fundamental_frequency << std::endl;
    return fundamental_frequency;
}

// TODO - Need instrument class implementation from group members 
double tuning_correction(double fundamental_frequency, Instrument instrument){
    double correction_val = 0; 

    return correction_val;
}

#ifdef TEST_HPS
int main(){
    // Test signal
    std::vector<double> test_signal {100, 120, 132, 121, 98, 67, 78, 143, 121, 32, 43, 56, 70, 153, 175, 189, 113, 125, 454, 234, 265, 321, 45, 67, 78, 98, 53, 21, 10, 12, 47, 89};
    harmonic_product_spectrum(test_signal);

}
#endif // DEBUG
