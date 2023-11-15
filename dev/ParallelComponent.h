#ifndef PARALLEL_COMPONENT_H
#define PARALLEL_COMPONENT_H

#include "DefaultComponent.h"

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