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

#endif