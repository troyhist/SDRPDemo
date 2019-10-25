// =======================================================================
// FilterCoeff ver. 1.0
// arrays of predefined FIR filters' coefficients
// -----------------------------------------------------------------------
//       MD: 12.11.2002
//       LE: 12.11.2002
// -----------------------------------------------------------------------
// Compiler: MS VC 6.0
// =======================================================================
// FilterCoeff.h
// =======================================================================
#include "DataTypes.h"	// Vector Cmplx, Float, Int
// =======================================================================
#ifndef FILTER_COEFF_H_
#define FILTER_COEFF_H_
// =======================================================================
// BP Filters
// -----------------------------------------------------------------------
CVectorFloat GetFilterBP1020();	// Filter: coeff. BP Band [0.10; 0.20] Transition bandwidth = 0.045 SA=40 dB
CVectorFloat GetFilterBP2030();	// Filter: coeff. BP Band [0.20; 0.30] Transition bandwidth = 0.045 SA=40 dB
CVectorFloat GetFilterBP3040();	// Filter: coeff. BP Band [0.30; 0.40] Transition bandwidth = 0.045 SA=40 dB
// -----------------------------------------------------------------------
// BS Filters
// -----------------------------------------------------------------------
CVectorFloat GetFilterBS1020();	// Filter: coeff. BS Band [0.10; 0.20] Transition bandwidth = 0.04 SA=40 dB
CVectorFloat GetFilterBS2030();	// Filter: coeff. BS Band [0.20; 0.30] Transition bandwidth = 0.04 SA=40 dB
CVectorFloat GetFilterBS3040();	// Filter: coeff. BS Band [0.30; 0.40] Transition bandwidth = 0.04 SA=40 dB
// -----------------------------------------------------------------------
// HP Filters
// -----------------------------------------------------------------------
CVectorFloat GetFilterHP10();	// Filter: coeff. HP Band [0.10; 0.50] Transition bandwidth = 0.045 SA=40 dB
CVectorFloat GetFilterHP20();	// Filter: coeff. HP Band [0.20; 0.50] Transition bandwidth = 0.045 SA=40 dB
CVectorFloat GetFilterHP30();	// Filter: coeff. HP Band [0.30; 0.50] Transition bandwidth = 0.045 SA=40 dB
CVectorFloat GetFilterHP40();	// Filter: coeff. HP Band [0.40; 0.50] Transition bandwidth = 0.045 SA=40 dB
// -----------------------------------------------------------------------
// LP Filters
// -----------------------------------------------------------------------
CVectorFloat GetFilterLP05();	// Filter: coeff. LP Band [0; 0.05] Transition bandwidth = 0.05	SA=40 dB
CVectorFloat GetFilterLP10();	// Filter: coeff. LP Band [0; 0.10] Transition bandwidth = 0.05	SA=40 dB
CVectorFloat GetFilterLP15();	// Filter: coeff. LP Band [0; 0.15] Transition bandwidth = 0.05	SA=40 dB
CVectorFloat GetFilterLP20();	// Filter: coeff. LP Band [0; 0.20] Transition bandwidth = 0.05	SA=40 dB
CVectorFloat GetFilterLP25();	// Filter: coeff. LP Band [0; 0.25] Transition bandwidth = 0.05	SA=40 dB
CVectorFloat GetFilterLP25X();	// Filter: coeff. LP Band [0; 0.25] Transition bandwidth = 0.01	SA=95 dB
CVectorFloat GetFilterLP30();	// Filter: coeff. LP Band [0; 0.30] Transition bandwidth = 0.05 SA=40 dB
CVectorFloat GetFilterLP35();	// Filter: coeff. LP Band [0; 0.35] Transition bandwidth = 0.01
CVectorFloat GetFilterLP40();	// Filter: coeff. LP Band [0; 0.40] Transition bandwidth = 0.01
CVectorFloat GetFilterLPSuper();// Filter: coeff. LP Band [0; 0.49] Transition bandwidth = 0.009 SA=40 dB
CVectorFloat GetTestC0();		// test filter
// =======================================================================
#endif	// FILTER_COEFF_H_