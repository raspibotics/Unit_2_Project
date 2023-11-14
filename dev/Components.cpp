#include "Components.h"

/* ---------------------------------------------------------------
Resistor class definitions
------------------------------------------------------------------ */ 
// Default constructor sets resistance to 100Ω
Resistor::Resistor() :  _R{100.0} {} 
Resistor::Resistor(double resistance) : _R{resistance} {}
// Mutator(s)
void Resistor::set_resistance(double resistance) { _R = resistance; }
// Acessor(s)
double Resistor::get_resistance() { return _R; }

/* ---------------------------------------------------------------
Inductor class definitions
------------------------------------------------------------------ */ 
// Default constructor sets inductance to 1mH
Inductor::Inductor() :  _L{0.001} {} 
Inductor::Inductor(double inductance) : _L{inductance} {}
// Mutator(s)
void Inductor::set_inductance(double inductance) { _L = inductance; }
// Acessor(s)
double Inductor::get_inductance() { return _L; }

/* ---------------------------------------------------------------
Capacitor class definitions
------------------------------------------------------------------ */ 
// Default constructor sets capacitance to 1uF
Capacitor::Capacitor() :  _C{0.000001} {} 
Capacitor::Capacitor(double capacitance) : _C{capacitance} {}
// Mutator(s)
void Capacitor::set_capacitance(double capacitance) { _C = capacitance; }
// Acessor(s)
double Capacitor::get_capacitance() { return _C; }

/* ---------------------------------------------------------------
Diode class definitions
------------------------------------------------------------------ */ 
// Default constructor sets forward voltage to 0.7V
Diode::Diode() :  _fv{0.7} {} 
Diode::Diode(double forward_voltage) : _fv{forward_voltage} {}
// Mutator(s)
void Diode::set_forward_voltage(double forward_voltage) { _fv = forward_voltage; }
// Acessor(s)
double Diode::get_forward_voltage() { return _fv; }