#ifndef CHEBYSHEV_TYPE_I_HPP
#define CHEBYSHEV_TYPE_I_HPP

#include <string>
#include <vector>
#include "Config.hpp"

const double pi = 3.14159265358979323846;

// Data structure to control the filter characteristics
struct filter_params {
    double cutoff_frequency; // 0 - 0.5 (Nyquist frequency)
    std::string filter_type; // "LP" for low_pass "HP" for high_pass
    double percent_ripple; // 0 - 29% 
    int poles; 
};
// Data structure to hold the computed chebyshev transfer function coeffecients [a[], b[]]
struct filter_coefficients {
    double a[22] = {0};
    double b[22] = {0};
};
class ChebyshevI {
    private:
        filter_coefficients _coefficients;
        filter_params _params;
        void set_filter_coefficients(filter_coefficients coeff);
    public: 
        ChebyshevI(); // Default constructor
        ChebyshevI(filter_params params);
        // Filter methods
        bool calculate_coefficients();
        bool validate_filter_params();
        std::vector<double> apply_filter(const std::vector<double> &samples);
        // Mutators and Acessors
        filter_coefficients get_filter_coefficients();
        filter_params get_filter_params();
        void set_filter_params(filter_params params);
};

#endif // CHEBYSHEV_TYPE_I_HPP

