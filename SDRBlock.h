// =======================================================================
// SDRBlock ver. 1.0
// blocks of the connected primitives
// -----------------------------------------------------------------------
//       MD: 07.11.2002
//       LE: 11.11.2002
// -----------------------------------------------------------------------
// Compiler: MS VC 6.0
// =======================================================================
// SDRBlock.h: interface for the CSDRBlock class.
// =======================================================================
#if !defined(AFX_SDRBLOCK_H__F5210E31_75DE_4B08_AE56_726BDEE18816__INCLUDED_)
#define AFX_SDRBLOCK_H__F5210E31_75DE_4B08_AE56_726BDEE18816__INCLUDED_
// =======================================================================
#include "DataTypes.h"	// 04.12.2002
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// =======================================================================
#include "SDRPrims.h"
// =======================================================================
class CSDRBlock  
{
public:	
	BOOL DCOffRem			(CVectorFloat&In1, CVectorFloat&Out1);	// DC Offset Removal
	BOOL DCOffRem_Setup		(int n);								// setup: DC Offset Removal
	BOOL DCOffRem_SetupFP	(int nI1L, int nI1F, int nIL, int nIF, int nO1L, int nO1F);	// setup of fixed point: DC Offset Removal (17.12.2002)
	BOOL FreqPhaseCorr		(CVectorFloat&In1, CVectorFloat&In2, CFloat In3, CFloat In4, CVectorFloat&Out1, CVectorFloat&Out2);	// Frequency & Phase correction
	BOOL FreqPhaseCorr_Setup	(int n);							// setup: Frequency & Phase correction
	BOOL FreqPhaseCorr_SetupFP	(int nI1L, int nI1F, int nIL, int nIF, int nO1L, int nO1F);	// setup of fixed point: Frequency & Phase correction (17.12.2002)
	BOOL SampRateConvFIR	(CVectorFloat&In1, CVectorFloat&Out1, int& m);		// Sample rate conversion - FIR (step 1)
	BOOL SampRateConvIP		(CVectorFloat&In1, CVectorFloat&Out1, int& m);		// Sample rate conversion - INTPOL (step 2)
	BOOL SampRateConvDE		(CVectorFloat&In1, CVectorFloat&Out1, int& m);		// Sample rate conversion - DECIM (step 2)
	BOOL SampRateConvRATAD	(CVectorFloat&In1, CVectorFloat&Out1, int& m);		// Sample rate conversion - RATAD (step 2) (18.11.2002)
	BOOL SampRateConv_Setup	(CVectorFloat&h, int n, int l, int nFactorInterpN, int nFactorDecimM);	// setup: Sample rate conversion
	BOOL SampRateConv_SetupFP(int nI1L, int nI1F, int nIL, int nIF, int nO1L, int nO1F);			// setup: Sample rate conversion f.p. (18.12.2002)
	BOOL SigPowInd			(CVectorFloat&In1, CVectorFloat&In2, CFloat&Out1);	// Signal power indication
	BOOL SigPowInd_Setup	(int n);											// setup: Signal power indication
	BOOL SigPowInd_SetupFP(int nI1L, int nI1F, int nIL, int nIF, int nO1L, int nO1F); // setup: Signal power indication f.p. (18.12.2002)
	// -------------------------------------------------------------------
	// Test functions
	// -------------------------------------------------------------------
	BOOL TestGenerateSpectrum(double dR0, double dR1, double dStep, int nSize, CVectorCmplx& tS);	// generates noise in the range [r0; r1] with given step (19.11.2002)
	BOOL TestGenerateSpectrum(double dR0, double dR1, double dStep, int nSize, CVectorFloat &tSr , CVectorFloat &tSi); // pseudo-complex version (28.11.2002)
	BOOL TestGenerateSpectrum_SetupFP(int nI1L, int nI1F, int nIL, int nIF, int nO1L, int nO1F);	// TGS: f.p. setup (18.12.2002)
	// -------------------------------------------------------------------
	BOOL Setup(CFloat dSR);	// setups internal data ... Should be called FIRST (12.11.2002)
	// -------------------------------------------------------------------
	CSDRBlock();
	virtual ~CSDRBlock();
	// -------------------------------------------------------------------
private:	
	// -------------------------------------------------------------------	
	// -------------------------------------------------------------------
	int m_nDCOffRem_n;					// DCOffRem: input & output block size
	int m_nDCOffRem_FPI1[3];			// DCOffRem: input signal bit capacty (17.12.2002)
	int m_nDCOffRem_FPIM[3];			// DCOffRem: intermediate signal bit capacty (17.12.2002)
	int m_nDCOffRem_FPO1[3];			// DCOffRem: output signal bit capacty (17.12.2002)
	// -------------------------------------------------------------------
	int m_nFreqPhaseCorr_n;				// FreqPhaseCorr: input & output block size
	int m_nFreqPhaseCorr_FPI1[3];		// FreqPhaseCorr: input signal bit capacty (17.12.2002)
	int m_nFreqPhaseCorr_FPIM[3];		// FreqPhaseCorr: intermediate signal bit capacty (17.12.2002)
	int m_nFreqPhaseCorr_FPO1[3];		// FreqPhaseCorr: output signal bit capacty (17.12.2002)
	// -------------------------------------------------------------------
	int m_nSampRateConv_n;				// Sample Rate Conversion: input block size
	int m_nSampRateConv_l;				// Sample Rate Conversion: filter block size
	int m_nSampRateConv_m;				// Sample Rate Conversion: output block size
	CVectorFloat m_pSampRateConv_h;		// Sample Rate Conversion: filter coefficients
	int m_nSampRateConv_FPI1[3];		// Sample Rate Conversion: f.p. 18.12.2002
	int m_nSampRateConv_FPIM[3];
	int m_nSampRateConv_FPO1[3];
	// -------------------------------------------------------------------
	int m_nSigPowInd_n;					// SigPowInd: input block size
	int m_nSigPowInd_FPI1[3];			// SigPowInd: f.p. 18.12.2002
	int m_nSigPowInd_FPIM[3];
	int m_nSigPowInd_FPO1[3];
	// -------------------------------------------------------------------
	int m_nTGS_FPI1[3];					// TGS f.p. setup (18.12.2002)
	int m_nTGS_FPIM[3];
	int m_nTGS_FPO1[3];
	// -------------------------------------------------------------------
	int m_bInited;						// true, if class is inited (08.11.2002)
	CFloat m_dSR;						// sample rate (08.11.2002)
	int m_nFactorInterpN;				// interpolation factor (11.11.2002)
	int m_nFactorDecimM;				// decimation factor (11.11.2002)
	// -------------------------------------------------------------------
};
// =======================================================================
#endif // !defined(AFX_SDRBLOCK_H__F5210E31_75DE_4B08_AE56_726BDEE18816__INCLUDED_)
// =======================================================================