// =======================================================================
// VECTor CONVertions class ver. 1.0
// set of functions to convert vector data
// -----------------------------------------------------------------------
//       MD: 09.01.2003
//       LE: 09.01.2003
// -----------------------------------------------------------------------
// Compiler: MS VC 6.0
// =======================================================================
// VectConv.h: interface for the CVectConv class.
// =======================================================================
#if !defined(AFX_VECTCONV_H__2EB56F1D_4ABA_4697_BE35_C4752264B1CF__INCLUDED_)
#define AFX_VECTCONV_H__2EB56F1D_4ABA_4697_BE35_C4752264B1CF__INCLUDED_
// =======================================================================
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// =======================================================================
#include "DataTypes.h"
// =======================================================================
class CVectConv  
{
public:
static BOOL ConvertIntToVectBool(int nNumber, CVectorBool&x, int nBits);	// calculates bitmask of given int number and puts it into the given vector (09.01.2003)
	// -------------------------------------------------------------------
static BOOL ConvVectBoolToInt(CVectorBool&x, CVectorInt&y);					// converts vector of BOOL elements into vector of BYTES (only 8 bits are used) (09.01.2003)
static BOOL ConvVectIntToBool(CVectorInt&x, CVectorBool&y, int nBitsPI);	// converts vector of BYTES into vector of BOOL elements (09.01.2003)
	// -------------------------------------------------------------------
static BOOL ConvVectCmplxToFloat(CVectorCmplx&z, CVectorFloat&x, CVectorFloat&y);	// converts one complex data stream into two float data streams
static BOOL ConvVectFloatToCmplx(CVectorFloat&x, CVectorFloat&y, CVectorCmplx&z);	// converts two float data streams into one complex data stream
	// -------------------------------------------------------------------
static CVectorBool GetWindow(CVectorBool& x, int nBlockSize, int nBlockNum);		// returns a vector, which is a copy of window (16.01.2003)
// -------------------------------------------------------------------
static BOOL SetupFixPointInVector(CVectorCmplx&tVF, int nL, int nF);				// adjusts fix point position in a complex vector (17.12.2002)
static BOOL SetupFixPointInVector(CVectorFloat&tVF, int nL, int nF);				// adjusts fix point position in a float vector (17.12.2002)
static BOOL SetupFixPointInVector(CVectorCmplx&tVF, int pLens[3]);		// adjusts fix point position in a complex vector (19.12.2002)
static BOOL SetupFixPointInVector(CVectorFloat&tVF, int pLens[3]);		// adjusts fix point position in a float vector (19.12.2002)
	// -------------------------------------------------------------------
	CVectConv();
	virtual ~CVectConv();
};
// =======================================================================
#endif // !defined(AFX_VECTCONV_H__2EB56F1D_4ABA_4697_BE35_C4752264B1CF__INCLUDED_)
// =======================================================================
