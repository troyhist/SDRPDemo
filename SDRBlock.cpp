// =======================================================================
// SDRBlock ver. 1.0
// blocks of of the connected primitives
// -----------------------------------------------------------------------
//       MD: 07.11.2002
//       LE: 07.11.2002
// -----------------------------------------------------------------------
// Compiler: MS VC 6.0
// =======================================================================
// SDRBlock.cpp: implementation of the CSDRBlock class.
// =======================================================================
#include "stdafx.h"
// -----------------------------------------------------------------------
#include "SDRBlock.h"
#include "VectConv.h"		// ConvVect... (09.01.2003)
// =======================================================================
// Construction/Destruction
// =======================================================================
CSDRBlock::CSDRBlock()
{
m_bInited=false;
// -----------------------------------------------------------------------
m_nDCOffRem_n=CSDRP_ERROR;
m_nDCOffRem_FPI1[0]=CSDRP_ERROR;	m_nDCOffRem_FPI1[2]=CSDRP_ERROR;	// DCOffRem: input signal bit capacty (17.12.2002)
m_nDCOffRem_FPIM[0]=CSDRP_ERROR;	m_nDCOffRem_FPIM[2]=CSDRP_ERROR;		// DCOffRem: intermediate signal bit capacty (17.12.2002)
m_nDCOffRem_FPO1[0]=CSDRP_ERROR;	m_nDCOffRem_FPO1[2]=CSDRP_ERROR;	// DCOffRem: output signal bit capacty (17.12.2002)
// -----------------------------------------------------------------------
m_nFreqPhaseCorr_n=CSDRP_ERROR;
m_nFreqPhaseCorr_FPI1[0]=CSDRP_ERROR;	m_nFreqPhaseCorr_FPI1[2]=CSDRP_ERROR;	// FreqPhaseCorr: input signal bit capacty (17.12.2002)
m_nFreqPhaseCorr_FPIM[0]=CSDRP_ERROR;	m_nFreqPhaseCorr_FPIM[2]=CSDRP_ERROR;	// FreqPhaseCorr: intermediate signal bit capacty (17.12.2002)
m_nFreqPhaseCorr_FPO1[0]=CSDRP_ERROR;	m_nFreqPhaseCorr_FPO1[2]=CSDRP_ERROR;	// FreqPhaseCorr: output signal bit capacty (17.12.2002)
// -----------------------------------------------------------------------
m_nSampRateConv_n=CSDRP_ERROR;	// Sample Rate Conversion: input block size
m_nSampRateConv_l=CSDRP_ERROR;	// Sample Rate Conversion: filter block size
m_nSampRateConv_m=CSDRP_ERROR;	// Sample Rate Conversion: output block size
m_nSampRateConv_FPI1[0]=CSDRP_ERROR;	m_nSampRateConv_FPI1[2]=CSDRP_ERROR;	// Sample Rate Conversion: f.p. 18.12.2002
m_nSampRateConv_FPIM[0]=CSDRP_ERROR;	m_nSampRateConv_FPIM[2]=CSDRP_ERROR;
m_nSampRateConv_FPO1[0]=CSDRP_ERROR;	m_nSampRateConv_FPO1[2]=CSDRP_ERROR;
// -----------------------------------------------------------------------
m_nSigPowInd_n=CSDRP_ERROR;
m_nSigPowInd_FPI1[0]=CSDRP_ERROR;	m_nSigPowInd_FPI1[2]=CSDRP_ERROR;	// SPI: f.p. 18.12.2002
m_nSigPowInd_FPIM[0]=CSDRP_ERROR;	m_nSigPowInd_FPIM[2]=CSDRP_ERROR;
m_nSigPowInd_FPO1[0]=CSDRP_ERROR;	m_nSigPowInd_FPO1[2]=CSDRP_ERROR;
// -----------------------------------------------------------------------
m_nTGS_FPI1[0]=CSDRP_ERROR;	m_nTGS_FPI1[2]=CSDRP_ERROR;	// TestGenerateSpectrum: 18.12.2002
m_nTGS_FPIM[0]=CSDRP_ERROR;	m_nTGS_FPIM[2]=CSDRP_ERROR;
m_nTGS_FPO1[0]=CSDRP_ERROR;	m_nTGS_FPO1[2]=CSDRP_ERROR;
// -----------------------------------------------------------------------
m_nFactorInterpN=1;				// interpolation factor (11.11.2002)
m_nFactorDecimM=1;				// decimation factor (11.11.2002)
}
// =======================================================================
CSDRBlock::~CSDRBlock()
{

}
// =======================================================================
BOOL CSDRBlock::Setup(CFloat dSR)
{
// -----------------------------------------------------------------------
// Description: setups internal data ... Should be called FIRST
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 12.11.2002
//          LE: 28.11.2002
// -----------------------------------------------------------------------
if(m_bInited)
	{
	}
// -----------------------------------------------------------------------
#ifdef SDRPDEMO_USEFIX
m_dSR.SetupFrom(dSR);
#endif
m_dSR=dSR;
// -----------------------------------------------------------------------
m_bInited=true;
return(true);
}
// =======================================================================
// Block functions
// =======================================================================
BOOL CSDRBlock::DCOffRem(CVectorFloat&In1, CVectorFloat&Out1)
{
// -----------------------------------------------------------------------
// Description: DC Offset Removal
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 07.11.2002
//          LE: 17.11.2002
// -----------------------------------------------------------------------
printf("CSDRBlock::DCOffRem(...) - started: ");
// -----------------------------------------------------------------------
if (!m_bInited) return(false);
int n=m_nDCOffRem_n; if (n==CSDRP_ERROR) return (false);
// -----------------------------------------------------------------------
CFloat dVMean;
CSDRPrims tP;	// primitive
// -----------------------------------------------------------------------
tP.Setup(m_dSR);		// setups the primitive class
tP.VMEAN_Setup(n);		tP.CWD2_Setup(n);
// -----------------------------------------------------------------------
// fixed point setup (17.11.2002)
tP.VMEAN_SetupFP(m_nDCOffRem_FPIM[0], m_nDCOffRem_FPIM[2],
				 m_nDCOffRem_FPO1[0], m_nDCOffRem_FPO1[2]);
tP.CWD2_SetupFP	(m_nDCOffRem_FPIM[0], m_nDCOffRem_FPIM[2],
				 m_nDCOffRem_FPO1[0], m_nDCOffRem_FPO1[2]);
// -----------------------------------------------------------------------
tP.VMEAN(In1, dVMean);	tP.CWD2(In1, dVMean, Out1);
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRBlock::DCOffRem_Setup(int n)	{ 
	if (!m_bInited) return(false); m_nDCOffRem_n=n; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRBlock::DCOffRem_SetupFP(int nI1L, int nI1F, int nIL, int nIF, int nO1L, int nO1F) {
	if (!m_bInited) return(false);
	m_nDCOffRem_FPI1[0]=nI1L;	m_nDCOffRem_FPI1[2]=nI1F;
	m_nDCOffRem_FPIM[0]=nIL;		m_nDCOffRem_FPIM[2]=nIF;
	m_nDCOffRem_FPO1[0]=nO1L;	m_nDCOffRem_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRBlock::FreqPhaseCorr	(CVectorFloat&In1, CVectorFloat&In2, 
								 CFloat In3, CFloat In4, CVectorFloat&Out1, 
								 CVectorFloat&Out2)
{
// -----------------------------------------------------------------------
// Description: Frequency & Phase correction
//   Parametrs: In1		- I (re)
//				In2		- Q (im)
//				In3		- f (frequency)
//				In4		- phi (phase)
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 07.11.2002
//          LE: 17.12.2002
// -----------------------------------------------------------------------
printf("CSDRBlock::FreqPhaseCorr(...) - started: ");
// -----------------------------------------------------------------------
if (!m_bInited) return(false);
int n=m_nFreqPhaseCorr_n; if (n==CSDRP_ERROR) return (false);
// -----------------------------------------------------------------------
CSDRPrims tP;			// primitive
CVectorCmplx tSin(n);	// generated sinus table
CVectorCmplx tIQ(n);	// I,Q as a complex number
CVectorCmplx tFPQ(n);	// corrected complex data stream
// -----------------------------------------------------------------------
tP.Setup(m_dSR);		// setups the primitive class
tP.SINGEN_Setup(n, 1);	// '1' - dummy-number, really - capacity in bits
tP.CWP_Setup(n, n);		// size of the 1st and the 2nd vectors (should be equal)
// -----------------------------------------------------------------------
// fixed point setup: 17.12.2002
tP.CWP_SetupFP(m_nFreqPhaseCorr_FPIM[0], m_nFreqPhaseCorr_FPIM[2], 
			   m_nFreqPhaseCorr_FPIM[0], m_nFreqPhaseCorr_FPIM[2]);	// intm
tP.SINGEN_SetupFP(m_nFreqPhaseCorr_FPIM[0], m_nFreqPhaseCorr_FPIM[2],
				  m_nFreqPhaseCorr_FPIM[0], m_nFreqPhaseCorr_FPIM[2]);	// intm
CVectConv::SetupFixPointInVector(tIQ, m_nFreqPhaseCorr_FPIM[0], m_nFreqPhaseCorr_FPIM[2]);		// intm
CVectConv::SetupFixPointInVector(Out1, m_nFreqPhaseCorr_FPO1[0], m_nFreqPhaseCorr_FPO1[2]);		// outp
CVectConv::SetupFixPointInVector(Out2, m_nFreqPhaseCorr_FPO1[0], m_nFreqPhaseCorr_FPO1[2]);		// outp
// -----------------------------------------------------------------------
CVectConv::ConvVectFloatToCmplx(In1, In2, tIQ);		// converts to complex data stream
tP.SINGEN(In3, In4, tSin);					// generates sinus
tP.CWP(tIQ, tSin, tFPQ);					// generates corrected data stream
CVectConv::ConvVectCmplxToFloat(tFPQ,Out1,Out2);	// convertes to float data stream
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRBlock::FreqPhaseCorr_Setup	(int n)	{
	if (!m_bInited) return(false); m_nFreqPhaseCorr_n=n; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRBlock::FreqPhaseCorr_SetupFP(int nI1L, int nI1F, int nIL, int nIF, int nO1L, int nO1F) {
	if (!m_bInited) return(false);
	m_nFreqPhaseCorr_FPI1[0]=nI1L;	m_nFreqPhaseCorr_FPI1[2]=nI1F;
	m_nFreqPhaseCorr_FPIM[0]=nIL;	m_nFreqPhaseCorr_FPIM[2]=nIF;
	m_nFreqPhaseCorr_FPO1[0]=nO1L;	m_nFreqPhaseCorr_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRBlock::SampRateConvFIR (CVectorFloat&In1, CVectorFloat&Out1, int& m)
{
// -----------------------------------------------------------------------
// Description: Sample rate conversion - FIR (step 1)
//   Parametrs: m	- here will be placed a size of the output vector
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 11.11.2002
//          LE: 11.11.2002
// -----------------------------------------------------------------------
printf("CSDRBlock::SampRateConvFIR(...) - started: ");
// -----------------------------------------------------------------------
if (!m_bInited) return(false);
int n=m_nSampRateConv_n, l=m_nSampRateConv_l;
if (n==CSDRP_ERROR || l==CSDRP_ERROR) return (false);
// -----------------------------------------------------------------------
CSDRPrims tP;			// primitive
CVectorFloat h=m_pSampRateConv_h;
Out1=CVectorFloat(n);	// comment this line in case of RATAD
// -----------------------------------------------------------------------
tP.Setup(m_dSR);		// setups the primitive class
tP.FIR_Setup(h, n, l);
tP.FIR_SetupFP (m_nSampRateConv_FPIM[0], m_nSampRateConv_FPIM[2],
				m_nSampRateConv_FPO1[0], m_nSampRateConv_FPO1[2]);
// -----------------------------------------------------------------------
m=n;
tP.FIR(In1, Out1);
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRBlock::SampRateConvDE (CVectorFloat&In1, CVectorFloat&Out1, int& m)
{
// -----------------------------------------------------------------------
//          MD: 11.11.2002
//          LE: 14.11.2002, 18.12.2002
// -----------------------------------------------------------------------
printf("CSDRBlock::SampRateConvDE(...) - started: ");
// -----------------------------------------------------------------------
if (!m_bInited) return(false);
int n=m_nSampRateConv_n, l=m_nSampRateConv_l;
if (n==CSDRP_ERROR || l==CSDRP_ERROR) return (false);
// -----------------------------------------------------------------------
CSDRPrims tP;			// primitive
CVectorFloat h=m_pSampRateConv_h;
// -----------------------------------------------------------------------
tP.Setup(m_dSR);		// setups the primitive class
tP.DECIM_Setup(h, n, m_nFactorDecimM, l);
tP.DECIM_SetupFP(m_nSampRateConv_FPIM[0], m_nSampRateConv_FPIM[2],
				 m_nSampRateConv_FPO1[0], m_nSampRateConv_FPO1[2]);
m=tP.DECIM_OutpVectLen();
tP.DECIM(In1, Out1);
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRBlock::SampRateConvIP (CVectorFloat&In1, CVectorFloat&Out1, int& m)
{
// -----------------------------------------------------------------------
//          MD: 11.11.2002
//          LE: 14.11.2002, 18.12.2002
// -----------------------------------------------------------------------
printf("CSDRBlock::SampRateConvIP(...) - started: ");
// -----------------------------------------------------------------------
if (!m_bInited) return(false);
int n=m_nSampRateConv_n, l=m_nSampRateConv_l;
if (n==CSDRP_ERROR || l==CSDRP_ERROR) return (false);
// -----------------------------------------------------------------------
CSDRPrims tP;			// primitive
CVectorFloat h=m_pSampRateConv_h;
// -----------------------------------------------------------------------
tP.Setup(m_dSR);
tP.INTPOL_Setup(h, n, m_nFactorInterpN, l);
tP.INTPOL_SetupFP(m_nSampRateConv_FPIM[0], m_nSampRateConv_FPIM[2], 
				  m_nSampRateConv_FPO1[0], m_nSampRateConv_FPO1[2]);
m=tP.INTPOL_OutpVectLen();
tP.INTPOL(In1, Out1);
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRBlock::SampRateConvRATAD (CVectorFloat&In1, CVectorFloat&Out1, int& m)
{
// -----------------------------------------------------------------------
// Description: Sample rate conversion - RATAD (step 2)
//          MD: 11.11.2002
//          LE: 18.11.2002, 18.12.2002
// -----------------------------------------------------------------------
printf("CSDRBlock::SampRateConvRATAD(...) - started: ");
// -----------------------------------------------------------------------
if (!m_bInited) return(false);
int n=m_nSampRateConv_n, l=m_nSampRateConv_l;
if (n==CSDRP_ERROR || l==CSDRP_ERROR) return (false);
// -----------------------------------------------------------------------
CSDRPrims tP;			// primitive
CVectorFloat h=m_pSampRateConv_h;
// -----------------------------------------------------------------------
tP.Setup(m_dSR);		// setups the primitive class
tP.RATAD_Setup(h, n, m_nFactorDecimM, m_nFactorInterpN, l);
tP.RATAD_SetupFP(m_nSampRateConv_FPIM[0], m_nSampRateConv_FPIM[2],
				 m_nSampRateConv_FPO1[0], m_nSampRateConv_FPO1[2]);
// -----------------------------------------------------------------------
m=tP.RATAD_OutpVectLen();
tP.RATAD(In1, Out1);
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRBlock::SampRateConv_Setup (CVectorFloat&h, int n, int l, 
									int nFactorInterpN, int nFactorDecimM) {
	if (!m_bInited) return(false); m_pSampRateConv_h=h; 
	m_nSampRateConv_n=n; m_nSampRateConv_l=l; 
	m_nFactorInterpN=nFactorInterpN;	
	m_nFactorDecimM=nFactorDecimM;	return(true); }
// -----------------------------------------------------------------------
BOOL CSDRBlock::SampRateConv_SetupFP(int nI1L, int nI1F, int nIL, int nIF, int nO1L, int nO1F) {
	if (!m_bInited) return(false);
	m_nSampRateConv_FPI1[0]=nI1L;	m_nSampRateConv_FPI1[2]=nI1F;
	m_nSampRateConv_FPIM[0]=nIL;		m_nSampRateConv_FPIM[2]=nIF;
	m_nSampRateConv_FPO1[0]=nO1L;	m_nSampRateConv_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRBlock::SigPowInd (CVectorFloat&In1, CVectorFloat&In2, CFloat&Out1)
{
// -----------------------------------------------------------------------
// Description: Signal power indication
//   Parametrs: In1		- I
//				In2		- Q
//				Out1	- power value
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 08.11.2002
//          LE: 08.11.2002
// -----------------------------------------------------------------------
printf("CSDRBlock::SigPowInd(...) - started: ");
// -----------------------------------------------------------------------
if (!m_bInited) return(false);
int n=m_nSigPowInd_n; if (n==CSDRP_ERROR) return (false);
// -----------------------------------------------------------------------
CSDRPrims tP;			// primitive
CVectorCmplx tIQ(n);	// I,Q as a complex number
// -----------------------------------------------------------------------
tP.Setup(m_dSR);		// setups the primitive class
tP.VSQRMEAN_Setup(n);	// size of the input vector
// -----------------------------------------------------------------------
// f.p. setup: 18.12.2002
CVectConv::SetupFixPointInVector(tIQ, m_nSigPowInd_FPIM[0], m_nSigPowInd_FPIM[2]);
tP.VSQRMEAN_SetupFP(m_nSigPowInd_FPIM[0], m_nSigPowInd_FPIM[2], m_nSigPowInd_FPO1[0], m_nSigPowInd_FPO1[2]);
// -----------------------------------------------------------------------
CVectConv::ConvVectFloatToCmplx(In1, In2, tIQ);	// converts to complex data stream
tP.VSQRMEAN(tIQ, Out1);
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRBlock::SigPowInd_Setup	(int n) {
	if (!m_bInited) return(false); m_nSigPowInd_n=n; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRBlock::SigPowInd_SetupFP(int nI1L, int nI1F, int nIL, int nIF, int nO1L, int nO1F) {
	if (!m_bInited) return(false);
	m_nSigPowInd_FPI1[0]=nI1L;	m_nSigPowInd_FPI1[2]=nI1F;
	m_nSigPowInd_FPIM[0]=nIL;	m_nSigPowInd_FPIM[2]=nIF;
	m_nSigPowInd_FPO1[0]=nO1L;	m_nSigPowInd_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
// Test functions
// =======================================================================
BOOL CSDRBlock::TestGenerateSpectrum(double dR0, double dR1, double dStep, int nSize, CVectorCmplx& tS)
{
// -----------------------------------------------------------------------
// Description: generates sinusoudical noise in the range [r0; r1] with given step
//   Parametrs: ...
//      Return: ...
// -----------------------------------------------------------------------
//          MD: 19.11.2002
//          LE: 05.12.2002, 18.12.2002
// -----------------------------------------------------------------------
printf("CSDRBlock::TestGenerateSpectrum(...) - started: ");
// -----------------------------------------------------------------------
CVectorCmplx tST(nSize);			// intermediate sinus signals
CSDRPrims tP;						// primitive
// -----------------------------------------------------------------------
int n;
double dn, f, phi;
// -----------------------------------------------------------------------
#ifdef SDRPDEMO_USEFIX
CVectConv::SetupFixPointInVector(tS, m_nTGS_FPO1);	// OUTPUT
CVectConv::SetupFixPointInVector(tST, m_nTGS_FPIM);
tP.SINGEN_SetupFP	(m_nTGS_FPIM[0], m_nTGS_FPIM[2], m_nTGS_FPIM[0], m_nTGS_FPIM[2]);
tP.CWS_SetupFP		(m_nTGS_FPIM[0], m_nTGS_FPIM[2], m_nTGS_FPIM[0], m_nTGS_FPIM[2]);
#endif
// -----------------------------------------------------------------------
tP.Setup(m_dSR);
tP.SINGEN_Setup(nSize, 1);	// '1' - dummy-number, really - capacity in bits
tP.CWS_Setup(nSize, nSize);	// CW sum
// -----------------------------------------------------------------------
dn=(dR1-dR0)*(1.0/dStep);
//int n=(int)dn+1;					// sometimes precision error occurs here
n=(int)dn;
f=dR0;
phi=0;
// -----------------------------------------------------------------------
tP.SINGEN(f*(double)m_dSR, phi, tS);
// -----------------------------------------------------------------------
printf("n=%d, nSize=%d : .", n, nSize);
// -----------------------------------------------------------------------
for (int i=1; i<=n; i++)
	{
	f=f+dStep;
	tP.SINGEN(f*(double)m_dSR, phi, tST);
	tP.CWS(tS, tST, tS);
	printf(".");
	}
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CSDRBlock::TestGenerateSpectrum(double dR0, double dR1, double dStep, int nSize, CVectorFloat &tSr , CVectorFloat &tSi)	{
// -----------------------------------------------------------------------
//          MD: 28.11.2002
//          LE: 18.12.2002
// -----------------------------------------------------------------------
	CSDRPrims tP;
	CVectorCmplx tS(nSize);
	CVectConv::SetupFixPointInVector(tSr, m_nTGS_FPO1[0], m_nTGS_FPO1[2]);
	CVectConv::SetupFixPointInVector(tSi, m_nTGS_FPO1[0], m_nTGS_FPO1[2]);
	TestGenerateSpectrum(dR0, dR1, dStep, nSize, tS);
	CVectConv::ConvVectCmplxToFloat(tS, tSr, tSi);
	return(true);
	// -------------------------------------------------------------------
	}
// =======================================================================
BOOL CSDRBlock::TestGenerateSpectrum_SetupFP(int nI1L, int nI1F, int nIL, int nIF, int nO1L, int nO1F) {
	if (!m_bInited) return(false);
	m_nTGS_FPI1[0]=nI1L;	m_nTGS_FPI1[2]=nI1F;
	m_nTGS_FPIM[0]=nIL;		m_nTGS_FPIM[2]=nIF;
	m_nTGS_FPO1[0]=nO1L;	m_nTGS_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
