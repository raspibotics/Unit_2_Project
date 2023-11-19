#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "DefaultComponent.h"

class Resistor : public DefaultComponent {
    public:
        // Default Constructor
        Resistor();
        // Non-default Constructor(s)
        Resistor(double resistance);
        // Mutators
        void set_resistance(double resistance);
        // Accessors
        double get_resistance();
    private:
        // Member Variables
        double _R; // Resistance in Ohms (Ω)
};

class Inductor : public DefaultComponent {
    public:
        // Default Constructor
        Inductor();
        // Non-default Constructor(s)
        Inductor(double inductance);
        // Mutators
        void set_inductance(double inductance);
        // Accessors
        double get_inductance();
    private:
        // Member Variables
        double _L; // Inductance in Henries (H)
};

class Capacitor : public DefaultComponent {
    public:
        // Default Constructor
        Capacitor();
        // Non-default Constructor(s)
        Capacitor(double capacitance);
        // Mutators
        void set_capacitance(double capacitance);
        // Accessors
        double get_capacitance();
    private:
        // Member Variables
        double _C; // Capacitance in Farads (F)

};

class Diode : public DefaultComponent {
    public:
        // Default Constructor
        Diode();
        // Non-default Constructor(s)
        Diode(double forward_voltage);
        // Mutators
        void set_forward_voltage(double forward_voltage);
        // Accessors
        double get_forward_voltage();
    private:
        // Member Variables
        double _fv; // Forward Voltage in Volts (V)
};


class ParallelComponent : public DefaultComponent {
    public:
        // Constructor with default arguments - Values are passed as arrays
        explicit ParallelComponent(size_t sr = 0, double *resistors =  nullptr, 
        size_t sl = 0, double *inductors = nullptr, 
        size_t s = 0, double *capacitors = nullptr);
        // Mutators that calculate member variables based on Parallel circuit laws
        void set_resistance(size_t sr, double *resistors);
        void set_inductance(size_t sl, double *inductors);
        void set_capacitance(size_t sc, double *capacitors);
        // Accessors that return total R, L, C in parallel
        double get_resistance();
        double get_inductance();
        double get_capacitance();
    private:
        double _R; // Resistance in Ohms (Ω)
        double _L; // Inductance in Henries (H)
        double _C; // Capacitance in Farads (F) 

};

#endif