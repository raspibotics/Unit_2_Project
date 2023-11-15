#include "ParallelComponent.h"


/* ---------------------------------------------------------------
ParallelComponent class definitions
------------------------------------------------------------------ */ 
ParallelComponent::ParallelComponent(size_t sr, double *resistors, size_t sl, double *inductors, size_t sc, double *capacitors) {
    // Calculate and set resistance
    ParallelComponent::set_resistance(sr, resistors);
    // Calculate and set inductance
    ParallelComponent::set_inductance(sl, inductors);
    // Calculate and set Capacitance
    ParallelComponent::set_capacitance(sc, capacitors);
}

// set_resistance() takes size of array and pointer to array of resistor values
void ParallelComponent::set_resistance(size_t sr, double *resistors){
    // Loop through array of resistors and combine into one "resistor"
    double combined_resistance = 0;
    for (size_t i = 0; i < sr; i++) {
        combined_resistance += 1 / *resistors+i;
    }
    _R = 1/combined_resistance; // Total resistance in parallel
}
// set_inductance() takes size of array and pointer to array of inductor values
void ParallelComponent::set_inductance(size_t sl, double *inductors){
    // Loop through array of inductors and combine into one "inductor"
    double combined_inductance = 0;
    for (size_t i = 0; i < sl; i++) {
        combined_inductance += 1 / *inductors+i;
    }
    _L = 1/combined_inductance; // Total inductance in parallel
}
// set_capacitance() takes size of array and pointer to array of capacitor values
void ParallelComponent::set_capacitance(size_t sc, double *capacitors){
    // Loop through array of capacitors and combine into one "capacitor"
    double combined_capacitance = 0;
    for (size_t i = 0; i < sc; i++) {
        combined_capacitance += *capacitors+i;
    }
    _C = combined_capacitance; // Total capacitance in parallel
}

double ParallelComponent::get_resistance() { return _R; }
double ParallelComponent::get_inductance() { return _L; }
double ParallelComponent::get_capacitance() { return _C; }
