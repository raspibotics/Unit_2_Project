#ifndef SOURCES_H
#define SOURCES_H

#include "DefaultComponent.h"

class DC_VoltageSource : public DefaultComponent {
    public:
        // Default Constructor
        // Non-default Constructor(s)
        // Mutators
        // Accessors
    private:
        // Member Variables
        double _V; // Source Amplitude
        double _Z; // Source Impedence
};

class AC_VoltageSource : public DC_VoltageSource {
    public:
        // Default Constructor
        // Non-default Constructor(s)
        // Mutators
        // Accessors
    private:
        // Member Variables
        double _f; // Source frequency in Hertz (Hz) -- Probably need to use complex types here
        double _p; // Phase shift in Radians (rad)
};


#endif
