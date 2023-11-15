#ifndef SOURCES_H
#define SOURCES_H

#include "DefaultComponent.h"
// Read why needs to inhertial a virtual DefaultComponent!
class DC_VoltageSource : public virtual DefaultComponent {
    public:
        // Default Constructor
        DC_VoltageSource();
        // Non-default Constructor(s)
        DC_VoltageSource(std::string component_id, double amplitude, double impedence);
        // Mutators
        void set_amplitude(double amplitude);
        void set_impedence(double impedence);
        // Accessors
        double get_amplitude();
        double get_impedence();
    private:
        // Member Variables
        double _V; // Source Amplitude
        double _Z; // Source Impedence
};

class AC_VoltageSource : public DC_VoltageSource {
    public:
        // Default Constructor
        AC_VoltageSource();
        // Non-default Constructor(s)
        AC_VoltageSource(std::string component_id, double amplitude, double impedence, double frequency, double phase);
        // Mutators
        void set_frequency(double frequency);
        void set_phase(double phase);
        // Accessors
        double get_frequency(); 
        double get_phase();
    private:
        // Member Variables
        double _f; // Source frequency in Hertz (Hz) -- Probably need to use complex types here
        double _p; // Phase shift in Radians (rad)
};


#endif
