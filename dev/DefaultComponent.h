#ifndef DEFAULT_COMPONENT_H
#define DEFAULT_COMPONENT_H

#include <string>

// The default component class that all components inherit from
class DefaultComponent {
    public: 
        // Default Constructor
        DefaultComponent();
        // Mutators
        void set_component_id(std::string);
        void set_component_voltage(double voltage);
        void set_component_current(double current);
        // Accessors
        std::string get_component_id();
        double get_component_voltage();
        double get_component_current();
    private:
        std::string _component_id; // Name of the component
        double _component_current; // Current through the component in Amps (A)
        double _component_voltage; // Voltage across the component in Volts (V)
};

#endif