#include "ParrallelComponent.h"

ParrallelComponent::ParrallelComponent(double resistors[], double inductors[], double capacitors[]) {
    // Calculate and set resistance
    ParrallelComponent::set_resistance(resistors);
    // Calculate and set inductance
    ParrallelComponent::set_inductance(inductors);
    // Calculate and set Capacitance
    ParrallelComponent::set_capacitance(capacitors);
}

void ParrallelComponent::set_resistance(double resistors[]){
    // Loop through array of resistors and combine into one "resistor"
    double combined_resistance = 0;
    for (size_t i = 0; i < 20; i++)
    {
        /* code */
    }
    
    _R = combined_resistance;
}

void ParrallelComponent::set_inductance(double inductors[]){
    // Loop through array of inductors and combine into one "inductor"
    double combined_inductance = 0;
    for (size_t i = 0; i < 20; i++)
    {
        /* code */
    }
    
    _R = combined_inductance;
}

void ParrallelComponent::set_capacitance(double capacitors[]){
    // Loop through array of capacitors and combine into one "capacitor"
    double combined_capacitance = 0;
    for (size_t i = 0; i < 20; i++)
    {
        /* code */
    }
    
    _R = combined_capacitance;
}