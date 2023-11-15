#ifndef PARRALLEL_COMPONENT_H
#define PARRALLEL_COMPONENT_H

#include "DefaultComponent.h"

class ParrallelComponent : public DefaultComponent {
    public:
        // Constructor with default arguments - Values are passed as arrays
        explicit ParrallelComponent(double resistors[] =  nullptr, double inductors[] = nullptr, double capacitors[] = nullptr);
        // Mutators that calculate member variables based on Parallel circuit laws
        void set_resistance(double resistors[]);
        void set_inductance(double inductors[]);
        void set_capacitance(double capacitors[]);
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