// =======================================================================
// Data types ver. 1.0
// easy tuning of the library
// -----------------------------------------------------------------------
//       MD: 04.12.2002
//       LE: 04.12.2002
// -----------------------------------------------------------------------
// Compiler: MS VC 6.0
// =======================================================================
// DataTypes.h: 
// =======================================================================
#ifndef _DATATYPES_H
#define _DATATYPES_H
// =======================================================================
// MAIN DATA TYPES
// =======================================================================
// uncomment this to use fix point implementations of functions (17.12.2002)
// (it will allow using of additional features)
#define SDRPDEMO_USEFIX
// =======================================================================
#include "FixNum.h"
#include "Complex.h"
// -----------------------------------------------------------------------
#pragma warning(disable:4786)	// long names (03.12.2002)
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
using namespace std::rel_ops;
// =======================================================================
#ifdef SDRPDEMO_USEFIX
typedef CFixNum				CFloat;
typedef CFixNum				CInt;
#else
typedef double				CFloat;
typedef int					CInt;
#endif
// =======================================================================
typedef CComplext<CFloat>	CComplex;
// =======================================================================
// vector classes (03.12.2002)
// -----------------------------------------------------------------------
typedef vector<unsigned int>	CVectorBool;	// (09.01.2003)
typedef vector<int>				CVectorInt;
typedef vector<CFloat>			CVectorFloat;
typedef vector<double>			CVectorDouble;	// (18.12.2002)
typedef vector<CComplex>		CVectorCmplx;
// =======================================================================
// DO NOT EDIT (valid only for Win32) (09.01.2003)
// =======================================================================
typedef int		int32;
typedef short	int16;
typedef char	int8;
// -----------------------------------------------------------------------
#endif
// =======================================================================
