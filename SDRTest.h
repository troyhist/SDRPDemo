// =======================================================================
// SDRTest ver. 1.0
// set of the test functions
// -----------------------------------------------------------------------
//       MD: 21.11.2002
//       LE: 21.11.2002
// -----------------------------------------------------------------------
// Compiler: MS VC 6.0
// =======================================================================
// SDRTest.h: interface for the CSDRTest class.
// =======================================================================
#if !defined(AFX_SDRTEST_H__6B3B9761_5C46_456C_912D_A26E3158209C__INCLUDED_)
#define AFX_SDRTEST_H__6B3B9761_5C46_456C_912D_A26E3158209C__INCLUDED_
// =======================================================================
#include "DataTypes.h"	// 04.12.2002
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// =======================================================================
class CSDRTest  
{
public:
	BOOL Test80211a();
	CVectorFloat DataILoadFromFile(char* sName);	// loads input data from given file and skips comment started from "*"
	CVectorFloat DataOLoadFromFile(char* sName, int nBD, int nBI, int nMaxD, int nMaxI);	// loads given block of the output referenced data from given file and skips comment started from "*"
	CVectorFloat FilterLoadFromFile(char* sName);	// loads filter coefficients from given file (21.11.2002)
	// -------------------------------------------------------------------
	BOOL TestChain();			// tests all Signal Processing Chains (11.11.2002)
	BOOL TestDCOffRem();		// checks DC offset removal function (07.11.2002)
	BOOL TestFreqPhaseCorr();	// tests Freq&Phase correction Chain (11.11.2002)
	BOOL TestRef();				// compares results of the RATAD block with referenced data (21.11.2002)
	BOOL TestSRCFIR();			// tests Sampling Rate Conversion chain - FIR (step 1)
	BOOL TestSRCIP2DE();		// tests Sampling Rate Conversion chain in two modes
	BOOL TestSRCIPandDE();		// tests Sampling Rate Conversion chain - INTPOL, DECIM (step 2)	
	BOOL TestSRCRATAD();		// tests Sampling Rate Conversion chain - RATAD (step 2)
	BOOL Setup();				// setups class
	// -------------------------------------------------------------------
	CSDRTest();
	virtual ~CSDRTest();
private:
	int SizePow2(int nSize);
};
// =======================================================================
#endif // !defined(AFX_SDRTEST_H__6B3B9761_5C46_456C_912D_A26E3158209C__INCLUDED_)
