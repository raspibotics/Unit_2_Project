#include "DefaultComponent.h"

// Constructor Definitions
DefaultComponent::DefaultComponent() : _component_id{"unnamed"} {}
DefaultComponent::DefaultComponent(std::string component_id) : _component_id{component_id} {}

// Mutator Definitions
void DefaultComponent::set_component_id(std::string component_id) {
    _component_id = component_id;
}
void DefaultComponent::set_component_current(double current) {
    _component_current = current;
}
void DefaultComponent::set_component_voltage(double voltage) { 
   _component_voltage = voltage; 
}

// Accessor Definitions
std::string DefaultComponent::get_component_id() {
    return _component_id;
}
double DefaultComponent::get_component_current() {
    return _component_current;
}
double DefaultComponent::get_component_voltage() {
    return _component_voltage;
}
