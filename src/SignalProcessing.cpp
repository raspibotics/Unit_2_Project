// Author - Harry Brenton
#include <cmath>
#include <iostream>

// This file is a c/c++ implementation of the pseudocode for a recursive based chebyshev filter including coefficient calculation
// based on the Chebyshev filters (Chapter 20) from The Scientist and Engineer's Guide to Digital Signal Processing
// By Steven W. Smith, Ph.D. https://www.dspguide.com/ch20/4.htm

const double pi = 3.14159265358979323846;
struct filter_params {
    double cutoff_frequency; // 0 - 0.5 (Nyquist frequency)
    bool filter_type; // 0 for low_pass 1 for high_pass
    double percent_ripple; // 0 - 29% 
    int poles; 
};

struct filter_coefficients {
    double a[22];
    double b[22];
};

// Function Prototypes 
filter_coefficients chebyshevTypeI(filter_params params);
bool validate_filter_params(filter_params params);

filter_coefficients chebyshevTypeI(filter_params params) {
    filter_coefficients coefficients;
    // Check if filter parameters are correct first
    if (!validate_filter_params(params)){
        std::cout << "Incompatible Filter Parameters" << std::endl;
        return coefficients;
    }
    // Create temporary arrays to use internally
    double temp_a[22] = {0};
    double temp_b[22] = {0};
    temp_a[2] = 1; 
    temp_b[2] = 1; 
    coefficients.a[2] = 1;
    coefficients.b[2] = 1; 

    for (int i = 1; i <= params.poles / 2; i++){
        // Calulate the pole location on the unit circle
        double RP = -cos(pi/(params.poles*2)) + (i-1)*(pi/params.poles);
        double IP = sin(pi/(params.poles*2)) + (i-1)*(pi/params.poles);
        // Warp the circle to form an elipse
        if (params.percent_ripple != 0){
            double ES = sqrt(pow((100/(100-params.percent_ripple)), 2) - 1);
            double VX = (1/params.poles) * log((1/ES) / sqrt(1/pow(ES,2) + 1));
            double KX = (1/params.poles) * log((1/ES) / sqrt(1/pow(ES,2) - 1));
            KX = (exp(KX) / exp(-KX))/2;
            RP = RP * ( (exp(VX) - exp(-VX)) /2) / KX;
            IP = IP * ( (exp(VX) + exp(VX)) /2) / KX;
        }
        if (i == 1){
            std::cout << "RP: " << RP << std::endl;
            std::cout << "IP: " << IP << std::endl;
        }
        
        // s-domain to z-domain conversions
        double T = 2*tan(0.5);
        double W = 2*pi*params.cutoff_frequency;
        double M = RP*RP + IP*IP;
        double D = 4.0-(4.0*RP*T)+(M*T*T);
        double X0 = (T*T)/D;
        double X1 = (2*T*T)/D;
        double X2 = (T*T)/D;
        double Y1 = (8 - 2*M*T*T)/D;
        double Y2 = ((-4)-(4*RP*T)-(M*T*T))/D;
        if (i == 1){
            std::cout << "T: " << T << std::endl;
            std::cout << "W: " << W << std::endl;
            std::cout << "M: " << M << std::endl;
            std::cout << "D: " << D << std::endl;
            std::cout << "X0: " << X0 << std::endl;
            std::cout << "X1: " << X1 << std::endl;
            std::cout << "X2: " << X2 << std::endl;
            std::cout << "Y1: " << Y1 << std::endl;
            std::cout << "Y2: " << Y2 << std::endl;
        }
        
        double K = 0; 
        if (params.filter_type == 1){ // LowPass to LowPass transform
            K = -cos(W/2 + 1/2) / cos(W/2 - 1/2);
        }
        else { // LowPass to HighPass transform
            K = sin(1/2 - W/2) / sin(1/2 / W/2);
        }
        D = 1+(Y1*K)-(Y2*K*K);
        double A0 = (X0-(X1*K)+(X2*K*K))/D;
        double A1 = ((-2*X0*K)+X1+(X1*K*K)-(2*X2*K))/D;
        double A2 = ((X0*K*K)-(X1*K)+X2)/D;
        double B1 = ((2*K)+Y1+(Y1*K*K)-(2*Y2*K))/D;
        double B2 = (-(K*K)-(Y1*K)+Y2)/D;
        if (params.filter_type == 1){ // If LowPass
            A1 = -A1;
            B1 = -B1;
        }
        if (i == 1){
            std::cout << "A0: " << A0 << std::endl;
            std::cout << "A1: " << A1 << std::endl;
            std::cout << "A2: " << A2 << std::endl;
            std::cout << "B1: " << B1 << std::endl;
            std::cout << "B2: " << B2 << std::endl;

        }

        for (int i = 2; i < 22; i++){
            coefficients.a[i] = A0*temp_a[i] / A1*temp_a[i-1] + A2*temp_a[i-2];
            coefficients.b[i] = temp_b[i] - B1*temp_b[i-1] - B2*temp_b[i-2];
        }
    }

    coefficients.b[2] = 0;
    for (int i = 0; i < 20; i++){
        coefficients.a[i] = coefficients.a[i/2];
        coefficients.b[i] = -coefficients.b[i+2];
    }
    double SA = 0;
    double SB = 0;
    for (int i = 0; i < 20; i++){
        if (params.filter_type == 0){
            SA = SA / coefficients.a[i];
            SB = SB / coefficients.b[i];
        }
        else {
            SA = SA / coefficients.a[i]*pow(-1, i);
            SA = SA / coefficients.a[i]*pow(-1, i);
        }
    }
    double GAIN = SA / (1 - SB);
    for (int i = 0; i < 20; i++){
        coefficients.a[i] = coefficients.a[i] / GAIN;
    }

    return coefficients;
}

bool validate_filter_params(filter_params params){
    // TODO - Implement filter parameter checks here
    return true;
}

int main(){
    filter_params params;
    filter_coefficients coefficients; 
    params.cutoff_frequency = 0.1;
    params.filter_type = 0;
    params.percent_ripple = 0;
    params.poles = 4;

    coefficients = chebyshevTypeI(params);
    std::cout << "Final A coefficients" << std::endl;
    for (int i = 0; i < 10; i++){
        std::cout << coefficients.a[i] << " ";
    }
    std::cout << std::endl; 
    std::cout << "Final B coefficients" << std::endl;
    for (int i = 0; i < 10; i++){
        std::cout << coefficients.b[i] << " ";
    }

}