// Author - Harry Brenton
#include <cmath>
#include <iostream>
#include "include/ChebyshevTypeI.hpp"
// This file is a C++ implementation of a recursive based chebyshev (IIR) filter including coefficient calculation
// based on the Chebyshev filters (Chapter 20) from 
// Smith, S.W. 2003. Digital signal processing : a practical guide for engineers and scientists. Amsterdam ; Newnes.
// https://www.analog.com/en/education/education-library/scientist_engineers_guide.html

// I have also included a function to validate the filter parameters to ensure proper operation
// and a recursive filter implementation to apply the filter (IIR) based on Ch. 19 from the previously mentioned DSP textbook

// Default constructor - Set to something that won't cause issues with the parameter checker
ChebyshevI::ChebyshevI(){
    _params.filter_type = "LP"; 
    _params.poles = 4;
    _params.cutoff_frequency = 0.1;
    _params.percent_ripple = 0.5;
}

// Constructor
ChebyshevI::ChebyshevI(filter_params params) : _params(params) {}

// Mutators and Accessors
filter_coefficients ChebyshevI::get_filter_coefficients() { return _coefficients; }
filter_params ChebyshevI::get_filter_params() { return _params; }
void ChebyshevI::set_filter_params(filter_params params) { _params = params; }
void ChebyshevI::set_filter_coefficients(filter_coefficients coeff) { _coefficients = coeff; }

// Function to solve coefficients for a recursive Chebyshev I Filter - Return true if sucessful, false if unsucessful
bool ChebyshevI::calculate_coefficients() {
    // Check if filter parameters are correct first
    if (ChebyshevI::validate_filter_params() == false){
        std::cout << "Incompatible Filter Parameters" << std::endl;
        return false;
    }
    // Ensure filter coefficients are reset
    filter_coefficients reset_coefficients;
    ChebyshevI::set_filter_coefficients(reset_coefficients);
    // Create temporary arrays to use internally
    double temp_a[22] = {0};
    double temp_b[22] = {0};
    _coefficients.a[2] = 1;
    _coefficients.b[2] = 1; 

    // Loop through each pole pair
    for (int i = 1; i <= _params.poles / 2; i++){
        // Calulate the pole location on the unit circle
        double RP = -cos((pi/(_params.poles*2)) + (i-1)*(pi/_params.poles));
        double IP = sin((pi/(_params.poles*2)) + (i-1)*(pi/_params.poles));
        // Warp the circle to form an elipse
        if (_params.percent_ripple != 0){
            double ES = sqrt(pow((100.0/(100.0-_params.percent_ripple)), 2)-1);
            double SE = 1/ES;
            double poles_ = (1.0/_params.poles);
            double VX = (poles_)*log((SE)+sqrt((1.0/(pow(ES,2)))+1.0));
            double KX = (poles_)*log((SE)+sqrt((1.0/(pow(ES,2)))-1.0));
            KX = ((exp(KX))+exp(-KX))/2.0;
            RP = RP*((exp(VX)-exp(-VX))/2.0)/KX;
            IP = IP*((exp(VX)+exp(-VX))/2.0)/KX;
        }
        // s-domain to z-domain conversions
        double T = 2*tan(0.5);
        double W = 2*pi*_params.cutoff_frequency;
        double M = RP*RP + IP*IP;
        double D = 4.0-(4.0*RP*T)+(M*T*T);
        double X0 = (T*T)/D;
        double X1 = (2*T*T)/D;
        double X2 = (T*T)/D;
        double Y1 = (8 - 2*M*T*T)/D;
        double Y2 = ((-4)-(4*RP*T)-(M*T*T))/D;
        double K = 0; 
        if (_params.filter_type == "HP"){ // LowPass to HighPass transform
            K = -(cos((W/2)+0.5)/cos((W/2)-0.5));
        }
        else {
            K = (sin(0.5-(W/2))/sin(0.5+(W/2)));
        }
        D = 1+(Y1*K)-(Y2*K*K);
        double A0 = (X0-(X1*K)+(X2*K*K))/D;
        double A1 = ((-2*X0*K)+X1+(X1*K*K)-(2*X2*K))/D;
        double A2 = ((X0*K*K)-(X1*K)+X2)/D;
        double B1 = ((2*K)+Y1+(Y1*K*K)-(2*Y2*K))/D;
        double B2 = (-(K*K)-(Y1*K)+Y2)/D;
        if (_params.filter_type == "HP"){ 
            A1 = -A1;
            B1 = -B1;
        }
        // Add coefficients to cascade
        for (int i = 0; i < 22; i++){
            temp_a[i] = _coefficients.a[i];
            temp_b[i] = _coefficients.b[i];
        }
        for (int i = 2; i < 22; i++){
            _coefficients.a[i] = (A0*temp_a[i])+(A1*temp_a[i-1])+(A2*temp_a[i-2]);
            _coefficients.b[i] = (temp_b[i])-(B1*temp_b[i-1])-(B2*temp_b[i-2]);
        }
    }
    _coefficients.b[2] = 0;
    for (int i = 0; i <= 20; i++){
        _coefficients.a[i] = _coefficients.a[i+2];
        _coefficients.b[i] = -_coefficients.b[i+2];
    }
    // Normalise the gain
    double SA = 0;
    double SB = 0;
    for (int i = 0; i < 20; i++){
        if (_params.filter_type == "LP"){
            SA = SA+_coefficients.a[i];
            SB = SB+_coefficients.b[i];
        }
        else {
            SA = SA+(_coefficients.a[i])*(pow(-1, i));
            SB = SB+(_coefficients.b[i])*(pow(-1, i));
        }
    }
    double GAIN = SA/(1-SB);
    for (int i = 0; i < 20; i++){
        _coefficients.a[i] = (_coefficients.a[i])/GAIN;
    }

    return true;
}

// Method to validate the parameters passed into the coefficient calculations
bool ChebyshevI::validate_filter_params(){
    bool valid_params = true; 
    // Check cutoff frequency is set within correct range
    if (_params.cutoff_frequency <= 0 || _params.cutoff_frequency > 0.5){
        std::cout << "INVALID FILTER PARAMETER [Cutoff Frequency]: Cutoff frequency must be [0<Fc<=0.5] (0.5 = Nyquist Frequency)" << std::endl;
        valid_params = false; 
    }
    // Check filter type is set to either low pass or high pass
    if ((_params.filter_type != "LP") && (_params.filter_type != "HP")){
        std::cout << "INVALID FILTER PARAMETER [Filter Type]: Filter type must either be 0 (Low pass) or 1 (High pass)" << std::endl;
        valid_params = false;
    } 
    // Check percentage ripple is set within acceptable limits (0% is Butterworth)
    if (_params.percent_ripple < 0 || _params.cutoff_frequency > 29){
        std::cout << "INVALID FILTER PARAMETER [Percent Ripple]: Ripple percentage must be [0<=PR<=29]" << std::endl;
        valid_params = false; 
    }
    return valid_params;
}

// TODO - Test by plotting filter response using python - Check against Impulse, square wave etc.
// Recursive filter implementation - Based on theory from Chapter 19 (Smith, S.W. 2003. Digital signal processing : a practical guide for engineers and scientists. Amsterdam ; Newnes.
std::vector<double> ChebyshevI::apply_filter(const std::vector<double> &samples) {
    int signal_length = samples.size();
    //std::cout << "signal length" << signal_length << std::endl;
    std::vector<double> filtered_signal(signal_length, 0); 
    double fa = 0;
    double fb = 0; 
    double temp_a = 0; 
    double temp_b = 0; 
    // Iterate through each sample
    for (int i = _params.poles + 1; i < signal_length; i++){
        fa = 0;
        fb = 0; 
        // Add "a" coefficient weighted components to filtered signal
        for (int p = 0; p <= _params.poles; p++){
            temp_a = samples[i-p];
            //std::cout << "temp a: " << temp_a << std::endl;
            //std::cout << "current A: " << _coefficients.a[p] << std::endl;
            fa += (temp_a)*(_coefficients.a[p]);
        }
        // Add "b" coefficient weighted components to filtered signal
        for (int p = 1; p <= _params.poles; p++){
            //std::cout << "current B: " << _coefficients.b[p] << std::endl;
            temp_b = filtered_signal[i-p];
            fb += (temp_b)*(_coefficients.b[p]);
        }
        filtered_signal[i] = fa + fb; 
    }
    return filtered_signal; 
}