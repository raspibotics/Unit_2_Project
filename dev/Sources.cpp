#include "Sources.h"

/* ---------------------------------------------------------------
DC_VoltageSource class definitions
------------------------------------------------------------------ */ 
// Default constructor sets amplitude to 5.00V and impedence to 25Ω
DC_VoltageSource::DC_VoltageSource() : _V{5.00}, _Z{25} {}
DC_VoltageSource::DC_VoltageSource(double amplitude, double impedence) : _V{amplitude}, _Z{impedence} {}
// Mutator(s)
void DC_VoltageSource::set_amplitude(double amplitude) { _V = amplitude; }
void DC_VoltageSource::set_impedence(double impedence) { _Z = impedence; }
// Acessor(s)
double DC_VoltageSource::get_amplitude() { return _V; }
double DC_VoltageSource::get_impedence() { return _Z; } 

/* ---------------------------------------------------------------
AC_VoltageSource class definitions
------------------------------------------------------------------ */ 
// Default constructor sets frequency to 50Hz and phase to 0rad
AC_VoltageSource::AC_VoltageSource() : DC_VoltageSource(), _f{50.0}, _p{0.0} {}
AC_VoltageSource::AC_VoltageSource(double amplitude, double impedence, double frequency, double phase) : DC_VoltageSource{amplitude, impedence}, _f{frequency}, _p{phase} {}
// Mutator(s)
void AC_VoltageSource::set_frequency(double frequency) { _f = frequency; }
void AC_VoltageSource::set_phase(double phase) { _p = phase; }
// Acessor(s)
double AC_VoltageSource::get_frequency() { return _f; }
double AC_VoltageSource::get_phase() { return _p; } 