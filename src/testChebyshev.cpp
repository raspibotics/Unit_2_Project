#include "../src/include/ChebyshevTypeI.hpp"
#include <iostream>
#include <string>
#include <chrono>

#ifdef TEST_CHEBYSHEV
void test_chebyshev_filter_coefficients(){
    // Working with std::vector for ease during testing
    std::vector<int> test_poles = {2, 2, 2, 4, 4, 4, 6, 6};
    std::vector<std::string> test_filter_types = {"LP", "HP"};
    std::vector<double> test_cutoff_frequencies = {0.10, 0.40, 0.01, 0.25, 0.05, 0.15, 0.45, 0.025};
    // Unfortunately only test data for 0.5% ripple is provided by DSP textbook (Ch. 20) 
    double test_percent_ripple = 0.5;
    // Correct table of coefficients from Book
    std::vector<std::vector<double>> correct_coeff_a {{6.372802E-02, 1.274560E-01, 6.372802E-02}, {6.372801E-02, -1.274560E-01, 6.372801E-02}, {8.663387E-04, 1.732678E-03, 8.663387E-04},
                                                    {7.015302E-02, -2.806121E-01, 4.209182E-01, -2.806121E-01, 7.015302E-02}, {2.141509E-04, 8.566037E-04, 1.284906E-03, 8.566037E-04, 2.141509E-04}, {2.340973E-01, -9.363892E-01, 1.404584E+00, -9.363892E-01, 2.340973E-01},
                                                    {4.760635E-01, 2.856381E+00, 7.140952E+00, 9.521270E+00, 7.140952E+00, 2.856381E+00, 4.760635E-01}, {6.912863E-01, -4.147718E+00, 1.036929E+01, -1.382573E+01,  1.036929E+01, -4.147718E+00, 6.912863E-01}}; 
    std::vector<std::vector<double>> correct_coeff_b {{0, 1.194365E+00, -4.492774e-01}, {0, -1.194365E+00, -4.492774E-01}, {0, 1.919129E+00, -9.225943E-01},
                                                    {0, -4.541478E-01, -7.417535E-01, -2.361221E-01, -7.096475E-02}, {0, 3.425455E+00, -4.479272E+00,  2.643718E+00, -5.933269E-01}, {0, 1.263672E+00, -1.080487E+00, 3.276296E-01, -7.376791E-02},
                                                    {0, -4.522403E+00, -8.676844E+00, -9.007512E+00, -5.328429E+00, -1.702543E+00, -2.303303E-01}, {0, 5.261399E+00, -1.157800E+01, 1.363599E+01, -9.063840E+00, 3.223738E+00,  -4.793541E-01}};

     
    // Create a filter object to test 
    filter_params test_params;
    filter_coefficients results;
    ChebyshevI test_filter; 
    test_params.percent_ripple = test_percent_ripple;
    bool ret;
    double error; // Calculate error between test cases and provided
    double error_thresh = 0.0001; // should be 0 but set to avoid single-double precision comparison failures
    // Generate filter parameters to pass to filter object
    std::cout << "###################### CHEBYSHEV COEFFICIENT TEST CASES ########################" << std::endl;
    for (int i = 0; i < test_poles.size(); i++){ 
        bool test_result = true;
        // Construct filter paramters for each test case
        test_params.poles = test_poles[i];
        test_params.cutoff_frequency = test_cutoff_frequencies[i];
        // Switch between LP and HP each loop
        if (i%2 == 0){test_params.filter_type = test_filter_types[0];} 
        else {test_params.filter_type = test_filter_types[1];}
        // Pass parameters to filter
        test_filter.set_filter_params(test_params);
        // Calculate filter coefficients
        ret = test_filter.calculate_coefficients();
        results = test_filter.get_filter_coefficients();
        if (!ret) {test_result = false;}
        // Loop through correct cases and compare
        for (int j = 0; j < correct_coeff_a[i].size(); j++){
            error = 0;
            // Add the errors, if they are correct they should be well below threshold
            error += abs(results.a[j] - correct_coeff_a[i][j]);
            error += abs(results.b[j] - correct_coeff_b[i][j]);
            if (error >= error_thresh){
                test_result = false;
                break;
            }
        }
        // Print results to console
        if (test_result == true){std::cout << "[PASS] ";}
        else {std::cout << "[FAIL] ";}
        std::cout << "{Poles: " << test_params.poles << ", ";
        std::cout << "Cutoff Freq: " << test_params.cutoff_frequency << ", ";
        std::cout << "Filter Type: " << test_params.filter_type << ", ";
        std::cout << "Percent Ripple: " << test_params.percent_ripple << "}" << std::endl;
    }
}

int main(){
    // Time the test functions
    auto start = std::chrono::high_resolution_clock::now();
    test_chebyshev_filter_coefficients();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time Taken: " << duration.count() << " Microseconds" << std::endl; 
}

#endif