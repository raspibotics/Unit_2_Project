#ifndef CHEBYSHEV_TYPE_I_H
#define CHEBYSHEV_TYPE_I_H

const double pi = 3.14159265358979323846;

// Data structure to control the filter characteristics
struct filter_params {
    double cutoff_frequency; // 0 - 0.5 (Nyquist frequency)
    int filter_type; // 0 for low_pass 1 for high_pass
    double percent_ripple; // 0 - 29% 
    int poles; 
};
// Data structure to hold the computed chebyshev transfer function coeffecients [a[], b[]]
struct filter_coefficients {
    double a[22];
    double b[22];
};

// Function Prototypes 
filter_coefficients chebyshevTypeI(filter_params params);
bool validate_filter_params(filter_params params);
void apply_filter(filter_coefficients coeff, double *frequencies);

class ChebyshevI {
    private:
        filter_coefficients _coefficients;
        filter_params _params;
    public: 
        ChebyshevI(); // Default constructor
        ChebyshevI(filter_coefficients params);
        // Filter methods
        filter_coefficients chebyshevTypeI(filter_params params);
        bool validate_filter_params(filter_params params);
        void apply_filter(filter_coefficients coeff, double *frequencies);
        // Mutators and Acessors
        filter_coefficients get_filter_coefficients();
        filter_params get_filter_params();
        void set_filter_params(filter_params params);
};

#endif // CHEBYSHEV_TYPE_I_H
