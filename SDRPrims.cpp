// =======================================================================
// SDRPrims ver. 1.0
// impementation: int, Complex
// -----------------------------------------------------------------------
// Compiler: MS VC 6.0
// =======================================================================
// SDRPrims.cpp: implementation of the CSDRPrims class.
// =======================================================================
#include "stdafx.h"
#include <math.h>			// atan
#include <crtdbg.h>			// _ASSERT (17.12.2002)
#include "SDRPrims.h"
#include "VectConv.h"		// ConvVect... (09.01.2003)
#include "_DEBUG.h"			// _DEBUG_TRACEVAR (17.01.2003)
// =======================================================================
const double M_PI=3.1415926535897932384626433832795;
// =======================================================================
// Construction/Destruction
// =======================================================================
CSDRPrims::CSDRPrims()
{
// -----------------------------------------------------------------------
// Description: the constructor - resets all internal setup data
//   Parametrs: ...
//      Return: <none>
// -----------------------------------------------------------------------
//          MD: 07.11.2002
//          LE: 19.12.2002
// -----------------------------------------------------------------------
m_bInited=false;			// true, if class is inited (08.11.2002)
//m_dSR=CSDRP_ERROR;
// -----------------------------------------------------------------------
m_nDOTP2_n1=CSDRP_ERROR;		m_nDOTP2_n2=CSDRP_ERROR;		// init data for DOTP (f.3.2)
m_nDOTP2_FPIM[0]=CSDRP_ERROR;	m_nDOTP2_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nDOTP2_FPO1[0]=CSDRP_ERROR;	m_nDOTP2_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)

m_nACFPNT_n=CSDRP_ERROR;		m_nACFPNT_s=CSDRP_ERROR;		// init data for ACFPNT	(f.3.5)
m_nACFPNT_FPIM[0]=CSDRP_ERROR;	m_nACFPNT_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nACFPNT_FPO1[0]=CSDRP_ERROR;	m_nACFPNT_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)


m_nFIR_n=CSDRP_ERROR;			m_nFIR_l=CSDRP_ERROR;			// init data for FIR (f.3.8)
m_nFIR_FPIM[0]=CSDRP_ERROR;		m_nFIR_FPIM[2]=CSDRP_ERROR;		// init data for ... (19.12.2002)
m_nFIR_FPO1[0]=CSDRP_ERROR;		m_nFIR_FPO1[2]=CSDRP_ERROR;		// init data for ... (19.12.2002)

m_nFIRSE_n=CSDRP_ERROR;			m_nFIRSE_l=CSDRP_ERROR;			// init data for FIRSE (f.3.9)
m_nFIRSE_FPIM[0]=CSDRP_ERROR;	m_nFIRSE_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nFIRSE_FPO1[0]=CSDRP_ERROR;	m_nFIRSE_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)

m_nFIRSO_n=CSDRP_ERROR;			m_nFIRSO_l=CSDRP_ERROR;			// init data for FIRSE (f.3.10)
m_nFIRSO_FPIM[0]=CSDRP_ERROR;	m_nFIRSO_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nFIRSO_FPO1[0]=CSDRP_ERROR;	m_nFIRSO_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)

m_nRSMPL_n=CSDRP_ERROR;			//m_nRSMPL_ratio=CSDRP_ERROR;		// init data for RSMPL (f.3.11)
m_nRSMPL_FPIM[0]=CSDRP_ERROR;	m_nRSMPL_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nRSMPL_FPO1[0]=CSDRP_ERROR;	m_nRSMPL_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
// -----------------------------------------------------------------------
m_nINTPOL_n=CSDRP_ERROR;	m_nINTPOL_l=CSDRP_ERROR;	// init data for INTPOL (f.3.12)
m_nINTPOL_N=CSDRP_ERROR;								// init data for INTPOL (f.3.12)
m_nINTPOL_FPIM[0]=CSDRP_ERROR;	m_nINTPOL_FPIM[2]=CSDRP_ERROR;	// init data for INTPOL f.p. (18.12.2002)
m_nINTPOL_FPO1[0]=CSDRP_ERROR;	m_nINTPOL_FPO1[2]=CSDRP_ERROR;
// -----------------------------------------------------------------------
m_nDECIM_n=CSDRP_ERROR;		m_nDECIM_l=CSDRP_ERROR;		// init data for DECIM (f.3.13)
m_nDECIM_L=CSDRP_ERROR;									// init data for DECIM (f.3.13)
m_nDECIM_FPIM[0]=CSDRP_ERROR;	m_nDECIM_FPIM[2]=CSDRP_ERROR;	// init data for DECIM f.p. (18.12.2002)
m_nDECIM_FPO1[0]=CSDRP_ERROR;	m_nDECIM_FPO1[2]=CSDRP_ERROR;
// -----------------------------------------------------------------------
m_nRATAD_n=CSDRP_ERROR;		m_nRATAD_L=CSDRP_ERROR;		// init data for RATAD (f.3.14)
m_nRATAD_N=CSDRP_ERROR;		m_nRATAD_l=CSDRP_ERROR;		// init data for RATAD (f.3.14)
m_nRATAD_FPIM[0]=CSDRP_ERROR;	m_nRATAD_FPIM[2]=CSDRP_ERROR;	// init data for RATAD f.p. (18.12.2002)
m_nRATAD_FPO1[0]=CSDRP_ERROR;	m_nRATAD_FPO1[2]=CSDRP_ERROR;
// -----------------------------------------------------------------------
m_nCWP_n1=CSDRP_ERROR;		m_nCWP_n2=CSDRP_ERROR;		// init data for CWP (f.3.17)
m_nCWP_FPIM[0]=CSDRP_ERROR;	m_nCWP_FPIM[2]=CSDRP_ERROR;	// init data for CWP f.p. (f.3.17)
m_nCWP_FPO1[0]=CSDRP_ERROR;	m_nCWP_FPO1[2]=CSDRP_ERROR;	// init data for CWP f.p. (f.3.17)
// -----------------------------------------------------------------------
m_nCWS_n1=CSDRP_ERROR;			m_nCWS_n2=CSDRP_ERROR;		// init data for CWS (f.3.18)
m_nCWS_FPIM[0]=CSDRP_ERROR;		m_nCWS_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nCWS_FPO1[0]=CSDRP_ERROR;		m_nCWS_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
// -----------------------------------------------------------------------
m_nCWS2_n=CSDRP_ERROR;									// init data for CWS2 (08.11.2002)
m_nCWS2_FPIM[0]=CSDRP_ERROR;	m_nCWS2_FPIM[2]=CSDRP_ERROR;	// init data for CWS2 f.p. (18.12.2002)
m_nCWS2_FPO1[0]=CSDRP_ERROR;	m_nCWS2_FPO1[2]=CSDRP_ERROR;
// -----------------------------------------------------------------------
m_nCWD_n1=CSDRP_ERROR;			m_nCWD_n2=CSDRP_ERROR;		// init data for CWD (f.3.19)
m_nCWD_FPIM[0]=CSDRP_ERROR;		m_nCWD_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nCWD_FPO1[0]=CSDRP_ERROR;		m_nCWD_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
// -----------------------------------------------------------------------
m_nCWD2_n=CSDRP_ERROR;									// init data for CWD2 (07.11.2002)
m_nCWD2_FPIM[0]=CSDRP_ERROR;	m_nCWD2_FPIM[2]=CSDRP_ERROR;	// init data for CWS2 fixed point (17.12.2002)
m_nCWD2_FPO1[0]=CSDRP_ERROR;	m_nCWD2_FPO1[2]=CSDRP_ERROR;	// init data for CWS2 fixed point (17.12.2002)
// -----------------------------------------------------------------------
m_nCWQ_n1=CSDRP_ERROR;			m_nCWQ_n2=CSDRP_ERROR;		// init data for CWQ (f.3.20)
m_nCWQ_FPIM[0]=CSDRP_ERROR;		m_nCWQ_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nCWQ_FPO1[0]=CSDRP_ERROR;		m_nCWQ_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)

m_nCWSQR_n=CSDRP_ERROR;											// init data for CWSQR (f.3.21)
m_nCWSQR_FPIM[0]=CSDRP_ERROR;	m_nCWSQR_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nCWSQR_FPO1[0]=CSDRP_ERROR;	m_nCWSQR_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)

m_nCWSC_n=CSDRP_ERROR;											// init data for CWSC (f.3.22)
m_nCWSC_FPIM[0]=CSDRP_ERROR;	m_nCWSC_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nCWSC_FPO1[0]=CSDRP_ERROR;	m_nCWSC_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)

m_nABS_n=CSDRP_ERROR;										// init data for ABS (f.3.23)
m_nABS_FPIM[0]=CSDRP_ERROR;		m_nABS_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nABS_FPO1[0]=CSDRP_ERROR;		m_nABS_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)

m_nSQRSUM_n=CSDRP_ERROR;										// init data for SQRSUM (f.3.24)
m_nSQRSUM_FPIM[0]=CSDRP_ERROR;	m_nSQRSUM_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nSQRSUM_FPO1[0]=CSDRP_ERROR;	m_nSQRSUM_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)

m_nPHASE_n=CSDRP_ERROR;											// init data for PHASE (f.3.25)
m_nPHASE_FPIM[0]=CSDRP_ERROR;	m_nPHASE_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nPHASE_FPO1[0]=CSDRP_ERROR;	m_nPHASE_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)

m_nCCPLX_n=CSDRP_ERROR;											// init data for CCPLX (f.3.26)
m_nCCPLX_FPIM[0]=CSDRP_ERROR;	m_nCCPLX_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nCCPLX_FPO1[0]=CSDRP_ERROR;	m_nCCPLX_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)

m_nVSUM_n=CSDRP_ERROR;											// init data for VSUM (f.3.27)
m_nVSUM_FPIM[0]=CSDRP_ERROR;	m_nVSUM_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nVSUM_FPO1[0]=CSDRP_ERROR;	m_nVSUM_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)

m_nSWA_l=CSDRP_ERROR;			m_nSWA_n=CSDRP_ERROR;		// init data for SWA (f.3.28)
m_nSWA_FPIM[0]=CSDRP_ERROR;		m_nSWA_FPIM[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
m_nSWA_FPO1[0]=CSDRP_ERROR;		m_nSWA_FPO1[2]=CSDRP_ERROR;	// init data for ... (19.12.2002)
// -----------------------------------------------------------------------
m_nSINGEN_n=CSDRP_ERROR;		m_nSINGEN_w=CSDRP_ERROR;	// init data for SINGEN (f.3.37)
m_nSINGEN_FPIM[0]=CSDRP_ERROR;	m_nSINGEN_FPIM[2]=CSDRP_ERROR;	// init data for SINGEN f.p. (f.3.37) (18.12.2002)
m_nSINGEN_FPO1[0]=CSDRP_ERROR;	m_nSINGEN_FPO1[2]=CSDRP_ERROR;// init data for SINGEN f.p. (f.3.37) (18.12.2002)
// -----------------------------------------------------------------------
m_nVMEAN_n=CSDRP_ERROR;									// init data for Vector Mean (07.11.2002)
m_nVMEAN_FPIM[0]=CSDRP_ERROR;	m_nVMEAN_FPIM[2]=CSDRP_ERROR;	// init data for: VMEAN fixed point (17.12.2002)
m_nVMEAN_FPO1[0]=CSDRP_ERROR;	m_nVMEAN_FPO1[2]=CSDRP_ERROR;	// init data for: VMEAN fixed point (17.12.2002)
// -----------------------------------------------------------------------
m_nVSQRMEAN_n=CSDRP_ERROR;							// init data for Vector Square Mean (08.11.2002)
m_nVSQRMEAN_FPIM[0]=CSDRP_ERROR;	m_nVSQRMEAN_FPIM[2]=CSDRP_ERROR;	// VSQRMEAN f.p. (18.12.2002)
m_nVSQRMEAN_FPO1[0]=CSDRP_ERROR;	m_nVSQRMEAN_FPO1[2]=CSDRP_ERROR;
// -----------------------------------------------------------------------
}
// =======================================================================
CSDRPrims::~CSDRPrims()
{

}
// =======================================================================
BOOL CSDRPrims::Setup(CFloat dSR)
{
// -----------------------------------------------------------------------
// Description: inits internal data of the class
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 08.11.2002
//          LE: 08.11.2002
// -----------------------------------------------------------------------
m_bInited=true;
#ifdef SDRPDEMO_USEFIX
m_dSR.SetupFrom(dSR);
#endif
m_dSR=dSR;
return(true);
}
// =======================================================================
// Primitives implementation
// =======================================================================
BOOL CSDRPrims::DOTP2(CVectorFloat&x, CVectorFloat&y, CFloat& dotp)
{
// -----------------------------------------------------------------------
// Description: calculates the dot product of the input vectors x and y
//   Parametrs: n1	- len of x-vector
//				n2	- len of y-vector
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 05.11.2002
//          LE: 07.11.2002
// -----------------------------------------------------------------------
int n1=m_nDOTP2_n1, n2=m_nDOTP2_n2;
if (!m_bInited) _ASSERT(0);
if (n1==CSDRP_ERROR) return (false);
if (n2==CSDRP_ERROR) return (false);
if (n1!=n2) return (false);
// -----------------------------------------------------------------------
// (19.12.2002)
#ifdef SDRPDEMO_USEFIX
dotp.Setup		(m_nDOTP2_FPO1);
#endif
// -----------------------------------------------------------------------
dotp=0;
for (int i=0; i<n1; i++)
	{
	CFloat mul=x[i]*y[i];
	dotp=dotp+mul;
	}
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::DOTP2_Setup(int n1, int n2)
	{ m_nDOTP2_n1=n1; m_nDOTP2_n2=n2; return(true); }
// =======================================================================
BOOL CSDRPrims::ACFPNT(CVectorCmplx&x, CComplex& acfpnt)
{
// -----------------------------------------------------------------------
// Description: Autocorrelation single point
//   Parametrs: ...
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 05.11.2002
//          LE: 07.11.2002
// -----------------------------------------------------------------------
int n=m_nACFPNT_n, s=m_nACFPNT_s;
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
if (s==CSDRP_ERROR) return (false);
int i1=max(0, -s);
int i2=n-1-max(0, s);
CFloat zero;
// -----------------------------------------------------------------------
// (19.12.2002)
#ifdef SDRPDEMO_USEFIX
acfpnt.Setup		(m_nACFPNT_FPO1[0], m_nACFPNT_FPO1[2]);
zero.SetupAsInt		(32);
#endif
// -----------------------------------------------------------------------
zero=0;
acfpnt=zero;
for (int i=i1; i<=i2; i++)	acfpnt=x[i].Conj()*x[i+s];
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::ACFPNT(CVectorFloat&xr, CVectorFloat&xi, CFloat& acfpntr, CFloat& acfpnti)
{
// -*!*-------------------------------------------------------------------
// Description: pseudo complex version of ACFPNT
//          MD: 28.11.2002
//          LE: 28.11.2002
// -----------------------------------------------------------------------
int nSize=xr.size();	
CComplex acfpnt;		// result
CVectorCmplx x(nSize);	// vector
CVectConv::SetupFixPointInVector(x, m_nACFPNT_FPIM);
CVectConv::ConvVectFloatToCmplx(xr, xi, x);
// -----------------------------------------------------------------------
BOOL bRes=ACFPNT(x, acfpnt);
acfpntr=acfpnt.Re();
acfpnti=acfpnt.Im();
// -----------------------------------------------------------------------
return(bRes);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::ACFPNT_Setup(int n, int s)
	{ m_nACFPNT_n=n; m_nACFPNT_s=s; return(true); }
// =======================================================================
BOOL CSDRPrims::FFT(CVectorFloat &ReX, CVectorFloat &ImX, CVectorFloat &ReZ, CVectorFloat &ImZ)	{
// -----------------------------------------------------------------------
// Description: FFT (copied from SDFFFT.pl)
//   Parametrs: ...
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 13.01.2003
//          LE: 13.01.2003
// -----------------------------------------------------------------------
_ASSERT(ReX.size());
_ASSERT(ReZ.size());
_ASSERT(ReX.size()==ImX.size());
_ASSERT(ReZ.size()==ImZ.size());
_ASSERT(ReZ.size()==ReX.size());
_ASSERT(IsPowerOfTwo(ReX.size()));
// -----------------------------------------------------------------------
printf("CSDRPrims::FFT(...) - started: ");
// -----------------------------------------------------------------------
int FFTLength=ReX.size();
int PortSize_All=ReZ.size();
// -----------------------------------------------------------------------
    int i,j,k;
//    for (i = 0; i < FFTLength; i++)
//      inp[FFTLength-i-1] = Complex(double(inReal%i), double(inImag%i));

    for (i = 0; i < FFTLength; i++) {
      j = FFTLength-i-1;
      double ReOut = 0.0;
      double ImOut = 0.0;
      for (k = 0; k < FFTLength; k++)
      {
        ReOut += double(ReX[FFTLength - 1 - k]) * cos (-2*M_PI*k*j/FFTLength) - double(ImX[FFTLength - 1 - k]) * sin(-2*M_PI*k*j/FFTLength);
        ImOut += double(ImX[FFTLength - 1 - k]) * cos (-2*M_PI*k*j/FFTLength) + double(ReX[FFTLength - 1 - k]) * sin(-2*M_PI*k*j/FFTLength);
      }
//        out += inp[k]*exp(Complex(0.0,-2*M_PI*k*j/FFTLength));

      ReZ[i] = ReOut;
      ImZ[i] = ImOut;
  }
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CSDRPrims::IFFT(CVectorFloat &inReal, CVectorFloat &inImag, CVectorFloat &outReal, CVectorFloat &outImag)	{
// -----------------------------------------------------------------------
// Description: IFFT (adaptation of SDFInvDFTCxToCxCartRI.pl)
//   Parametrs: ...
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 13.01.2003
//          LE: 13.01.2003, 30.01.2003 (FxP adaptation)
// -----------------------------------------------------------------------
#ifndef SDRPDEMO_USEFIX
// -----------------------------------------------------------------------
_ASSERT(inReal.size());
_ASSERT(outReal.size());
_ASSERT(inReal.size()==inImag.size());
_ASSERT(outReal.size()==outImag.size());
_ASSERT(outReal.size()==inReal.size());
_ASSERT(IsPowerOfTwo(inReal.size()));
// -----------------------------------------------------------------------
printf("CSDRPrims::IFFT(...) - started: ");
// -----------------------------------------------------------------------
int DFTLength=inReal.size();			// Length of DFT.
int numberOfTimeValues=inReal.size();	// Specifies how many values to output at a computation. It must be greater than zero and less than or equal to DFTLength.
// -----------------------------------------------------------------------
int i,j,k;
// -----------------------------------------------------------------------
for (i = 0; i < numberOfTimeValues; i++)
	{
	j = i;
	CComplex out;
	
	for (k = 0; k < DFTLength; k++)
		out += CComplex(inReal[k], inImag[k]) * CComplex(0.0,2*M_PI*k*j/DFTLength).e();
	out /= DFTLength;
    
	outReal[i] = out.real();
	outImag[i] = out.imag();
	printf(".");
	}
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
#else
_ASSERT(0);					// FxP is not supported (30.01.2003)
#endif // SDRPDEMO_USEFIX
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CSDRPrims::FIR	(CVectorFloat&x, CVectorFloat&y)	{
// -----------------------------------------------------------------------
// Description: Finite Impulse Response filtering
//   Parametrs: ...
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 05.11.2002
//          LE: 07.11.2002
// -----------------------------------------------------------------------
printf("CSDRPrims::FIR(...) - started: ");
// -----------------------------------------------------------------------
int n=m_nFIR_n, l=m_nFIR_l;
CVectorFloat h=m_pFIR_h;
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
if (l==CSDRP_ERROR) return (false);
int i, k, idx;
CFloat xik;
// -----------------------------------------------------------------------
// (19.12.2002)
#ifdef SDRPDEMO_USEFIX
CVectConv::SetupFixPointInVector(y, m_nFIR_FPO1);
xik.Setup				(m_nFIR_FPIM);
#endif
// -----------------------------------------------------------------------
printf("n=%d, l=%d : ", n, l);
// -----------------------------------------------------------------------
for (i=0; i<=n-1; i++)
	{
	y[i]=0;
	for (k=0; k<=l-1; k++)
		{
		idx=i-k; xik=0;
		if (idx>=0) xik=x[idx];
//		if ((double)(h[k]*xik)!=0) printf ("Ja!");
		//y[i]=y[i]+h[k]*xik;
		y[i]+=(h[k]*xik)
		#ifdef SDRPDEMO_USEFIX
			.ConvertTo(y[0])
		#endif
			;
		if ((double)(h[k]*xik)!=0 && 0)
			{
			CFloat z=h[k]*xik;
			CFloat yy=y[i];
			printf ("<ok,h, k=%d, z=%lf, y[%d]=%lf>\n", k, (double)z, i, 
				(double)y[i]
				);
			}
		//if ((double)y[i]!=0) printf ("<ok,y, i=%d>\t", i);
		}
	//if ((double)y[i]==0) printf ("out[%d]=0\t", i);
	printf(".");
	}
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::FIR_Setup(CVectorFloat& h, int n, int l) {
	m_nFIR_n=n; m_nFIR_l=l; m_pFIR_h=h; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::FIR_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nFIR_FPIM[0]=nIL;		m_nFIR_FPIM[2]=nIF;
	m_nFIR_FPO1[0]=nO1L;	m_nFIR_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::FIRSE (CVectorFloat&x, CVectorFloat&y)
{
// -----------------------------------------------------------------------
// Description: Finite Impulse Response filtering, Symmetric and Even
//   Parametrs: ...
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 07.11.2002
//          LE: 07.11.2002
// -----------------------------------------------------------------------
int n=m_nFIRSE_n, l=m_nFIRSE_l;
CVectorFloat h=m_pFIRSE_h;
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
if (l==CSDRP_ERROR) return (false);
int i, k;
CFloat xik1, xik2;
// -----------------------------------------------------------------------
// (19.12.2002)
#ifdef SDRPDEMO_USEFIX
CVectConv::SetupFixPointInVector(y, m_nFIRSE_FPO1);
xik1.Setup				(m_nFIRSE_FPIM);
xik2.Setup				(m_nFIRSE_FPIM);
#endif
// -----------------------------------------------------------------------
for (i=0; i<=n-1; i++)
	{
	y[i]=0;	
	for (k=0; k<=l-1; k++)
		{
		xik1=0; if (i-k>=0)			xik1=x[i-k];
		xik2=0;	if (i-2*l+1+k>=0)	xik2=x[i-2*l+1+k];
		y[i]=y[i]+h[k]*(xik1+xik2);
		}
	}
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::FIRSE_Setup(CVectorFloat& h, int n, int l) {
	m_nFIRSE_n=n; m_nFIRSE_l=l; m_pFIRSE_h=h; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::FIRSE_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nFIRSE_FPIM[0]=nIL;	m_nFIRSE_FPIM[2]=nIF;
	m_nFIRSE_FPO1[0]=nO1L;	m_nFIRSE_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::FIRSO (CVectorFloat&x, CVectorFloat&y)
{
// -----------------------------------------------------------------------
// Description: Finite Impulse Response filtering, Symmetric and Odd
//   Parametrs: ...
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 07.11.2002
//          LE: 07.11.2002
// -----------------------------------------------------------------------
int n=m_nFIRSO_n, l=m_nFIRSO_l;
CVectorFloat h=m_pFIRSO_h;
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
if (l==CSDRP_ERROR) return (false);
int i, k;
CFloat xik1, xik2, xik3;
// -----------------------------------------------------------------------
// (19.12.2002)
#ifdef SDRPDEMO_USEFIX
CVectConv::SetupFixPointInVector(y, m_nFIRSO_FPO1);
xik1.Setup				(m_nFIRSO_FPIM);
xik2.Setup				(m_nFIRSO_FPIM);
xik3.Setup				(m_nFIRSO_FPIM);
#endif
// -----------------------------------------------------------------------
for (i=0; i<=n-1; i++)
	{
	y[i]=0;	
	for (k=0; k<=l-1; k++)
		{
		xik1=0; if (i-k>=0)			xik1=x[i-k];
		xik2=0;	if (i-2*l+1+k>=0)	xik2=x[i-2*l+1+k];
		xik3=0;	if (i-l+1>=0)		xik3=x[i-l+1];
		y[i]=y[i]+h[k]*(xik1+xik2) + h[l-1]*xik3;
		}
	}
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::FIRSO_Setup(CVectorFloat& h, int n, int l) {
	m_nFIRSO_n=n; m_nFIRSO_l=l; m_pFIRSO_h=h; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::FIRSO_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nFIRSO_FPIM[0]=nIL;	m_nFIRSO_FPIM[2]=nIF;
	m_nFIRSO_FPO1[0]=nO1L;	m_nFIRSO_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::RSMPL (CVectorFloat&x, CVectorFloat&y)
{
// -----------------------------------------------------------------------
// Description: PERFORMS A RESAMPLING OF THE INPUT BLOCK
//   Parametrs: ...
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 11.11.2002
//          LE: 11.11.2002
// -----------------------------------------------------------------------
int n=m_nRSMPL_n; CFloat ratio=m_nRSMPL_ratio;
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR)		return (false);
if (ratio==CSDRP_ERROR) return (false);
// -----------------------------------------------------------------------
CInt n1, idx;
CFloat w1;
// -----------------------------------------------------------------------
// (19.12.2002)
#ifdef SDRPDEMO_USEFIX
CVectConv::SetupFixPointInVector(y, m_nRSMPL_FPO1);
w1.Setup				(m_nRSMPL_FPIM);
n1.SetupAsInt			(m_nRSMPL_FPIM[0]);
idx.SetupAsInt			(m_nRSMPL_FPIM[0]);
#endif
// -----------------------------------------------------------------------
for (int i=0; i<n; i++)
	{
	idx=i;
	n1=(int)(ratio*idx);
	w1=(ratio*idx)-n1;			// brakets 05.12.2002
	y[i]=w1*x[(int)n1+1] + w1*(x[(int)n1] - x[(int)n1+1]);	
	}
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::RSMPL_Setup(int n, CFloat ratio)
	{ m_nRSMPL_n=n; m_nRSMPL_ratio=ratio; return(true); }
// =======================================================================
BOOL CSDRPrims::INTPOL (CVectorFloat&x, CVectorFloat&y)
{
// -----------------------------------------------------------------------
// Description: performs an interpolation of the input block X
//   Parametrs: ...
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 11.11.2002
//          LE: 20.12.2002, 06.01.2003
// -----------------------------------------------------------------------
printf("CSDRPrims::INTPOL(...) - started: ");
// -----------------------------------------------------------------------
CInt nOne;
CInt i, j, m, i0, iN, idxh;
CInt n, N, l;
CFloat hij, xi;
// -----------------------------------------------------------------------
// (19.12.2002)
#ifdef SDRPDEMO_USEFIX
//hij.Setup				(m_nINTPOL_FPIM);		// intm
hij.SetupFrom			(m_pINTPOL_h[0]);		// intm (06.01.2003)
xi.SetupFrom			(x[0]);					// intm
nOne.SetupAsInt			(32);	i.SetupAsInt			(32);	
j.SetupAsInt			(32);	m.SetupAsInt			(32);
i0.SetupAsInt			(32);	iN.SetupAsInt			(32);
idxh.SetupAsInt			(32);	n.SetupAsInt			(32);
N.SetupAsInt			(32);	l.SetupAsInt			(32);
#endif
// -----------------------------------------------------------------------
CVectorFloat h=m_pINTPOL_h;
if (!m_bInited) _ASSERT(0); 
n=m_nINTPOL_n;
N=m_nINTPOL_N;
l=m_nINTPOL_l; 
if (n==CSDRP_ERROR || N==CSDRP_ERROR || l==CSDRP_ERROR) return (false);
// -----------------------------------------------------------------------
nOne=1;
m=INTPOL_OutpVectLen();
y=CVectorFloat((int)m);		CVectConv::SetupFixPointInVector(y, m_nINTPOL_FPO1);
// -----------------------------------------------------------------------
printf("n=%d, m=%d : ", (int)n, (int)m);
// -----------------------------------------------------------------------
for (j=0; j<m; j++)
	{
	// -------------------------------------------------------------------
	//i0=(int)((j-l)*(1.0/(CFloat)N))+1;
	//i0=((j-l)*(1.0/N))+nOne;
	i0=((j-l)*(1.0/N))
		#ifdef SDRPDEMO_USEFIX
		.ConvertTo(i0)				// (06.01.2003)
		#endif;
	+nOne;
	// -------------------------------------------------------------------
	//iN=(int)(j/N);				// 05.12.2002
	iN=(j*(1.0/N))					// 12.12.2002
		#ifdef SDRPDEMO_USEFIX
		.ConvertTo(iN);				// (06.01.2003)
		#endif
		;
	// -------------------------------------------------------------------
	y[(int)j]=0;
	for (i=i0; i<=iN; i++)
		{
		idxh=j-(i*N)
			#ifdef SDRPDEMO_USEFIX
			.ConvertTo(j)
			#endif
			;
		hij=0;	if(idxh>=0 && idxh<l) hij=h[(int)idxh];
		xi=0;	if(i>=0) xi=x[(int)i];
		y[(int)j]+=(xi*hij)
			#ifdef SDRPDEMO_USEFIX
			.ConvertTo(y[0])
			#endif
			;
		}
	printf(".");
	}
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// -----------------------------------------------------------------------
int	CSDRPrims::INTPOL_OutpVectLen() {
	if (m_nINTPOL_n==CSDRP_ERROR || m_nINTPOL_N==CSDRP_ERROR) 
	return (CSDRP_ERROR); return(m_nINTPOL_n*m_nINTPOL_N); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::INTPOL_Setup(CVectorFloat&h, int n, int N, int l) {
	m_pINTPOL_h=h; m_nINTPOL_n=n; m_nINTPOL_N=N; m_nINTPOL_l=l; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::INTPOL_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nINTPOL_FPIM[0]=nIL;	m_nINTPOL_FPIM[2]=nIF;
	m_nINTPOL_FPO1[0]=nO1L;	m_nINTPOL_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::DECIM (CVectorFloat&x, CVectorFloat&y)
{
// -----------------------------------------------------------------------
// Description: performs a decimation of the input block X
//   Parametrs: ...
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 14.11.2002
//          LE: 18.12.2002, 06.01.2003
// -----------------------------------------------------------------------
printf("CSDRPrims::DECIM(...) - started: ");
// -----------------------------------------------------------------------
CVectorFloat h=m_pDECIM_h;
if (!m_bInited) _ASSERT(0);
int n=m_nDECIM_n; int L=m_nDECIM_L; int l=m_nDECIM_l; 
if (n==CSDRP_ERROR || L==CSDRP_ERROR || l==CSDRP_ERROR) return (false);
// -----------------------------------------------------------------------
int i, j, m, i0, iN, idxh;
CFloat hij, xi;
// -----------------------------------------------------------------------
// (19.12.2002)
#ifdef SDRPDEMO_USEFIX
hij.SetupFrom(h[0]);						// intm (06.01.2003)
xi.Setup	(m_nDECIM_FPIM);				// intm
#endif
// -----------------------------------------------------------------------
m=DECIM_OutpVectLen();
y=CVectorFloat(m);			CVectConv::SetupFixPointInVector(y, m_nDECIM_FPO1);
// -----------------------------------------------------------------------
printf("n=%d, m=%d : ", n, m);
// -----------------------------------------------------------------------
for (j=0; j<m; j++)
	{
	i0=j*L-l+1;
	iN=j*L;
	y[j]=0;
	for (i=i0; i<=iN; i++)
		{
		idxh=j*L-i;
		hij=0;	if(idxh>=0 && idxh<l) hij=h[idxh];
		xi=0;	if(i>=0) xi=x[i];
		y[j]+=(xi*hij)
		#ifdef SDRPDEMO_USEFIX
			.ConvertTo(y[0])
		#endif
			;
		}
	printf(".");
	}
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// -----------------------------------------------------------------------
int	CSDRPrims::DECIM_OutpVectLen() {
	if (m_nDECIM_n==CSDRP_ERROR || m_nDECIM_L==CSDRP_ERROR) 
	return (CSDRP_ERROR); return(m_nDECIM_n/m_nDECIM_L); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::DECIM_Setup(CVectorFloat&h, int n, int L, int l) {
	m_pDECIM_h=h; m_nDECIM_n=n; m_nDECIM_L=L; m_nDECIM_l=l; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::DECIM_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nDECIM_FPIM[0]=nIL;	m_nDECIM_FPIM[2]=nIF;
	m_nDECIM_FPO1[0]=nO1L;	m_nDECIM_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::RATAD (CVectorFloat&x, CVectorFloat&y)
{
// -----------------------------------------------------------------------
// Description: performs a rate adaptation by the rational number N/L
//   Parametrs: ...
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 11.11.2002
//          LE: 18.12.2002
// -----------------------------------------------------------------------
printf("CSDRPrims::RATAD(...) - started: ");
// -----------------------------------------------------------------------
CInt i, j, m, i0, iN, idx;
CInt n, L, N, l;
CInt nOne;
CFloat hij, xi;
// -----------------------------------------------------------------------
// (19.12.2002)
#ifdef SDRPDEMO_USEFIX
CVectConv::SetupFixPointInVector(y, m_nRATAD_FPO1);
hij.SetupFrom			(m_pRATAD_h[0]);		// intm
xi.SetupFrom			(x[0]);					// intm
n.SetupAsInt(32);	L.SetupAsInt(32);
N.SetupAsInt(32);	l.SetupAsInt(32);
m.SetupAsInt(32);	j.SetupAsInt(32);
nOne.SetupAsInt(32);
i0.SetupAsInt(32);	iN.SetupAsInt(32);
i.SetupAsInt(32);	idx.SetupAsInt(32);
#endif
// -----------------------------------------------------------------------
CVectorFloat h=m_pRATAD_h;
if (!m_bInited) _ASSERT(0); 
n=m_nRATAD_n; L=m_nRATAD_L; N=m_nRATAD_N; l=m_nRATAD_l; 
if (n==CSDRP_ERROR || L==CSDRP_ERROR || N==CSDRP_ERROR || l==CSDRP_ERROR)
	return (false);
// -----------------------------------------------------------------------
nOne=1;
m=RATAD_OutpVectLen();
y=CVectorFloat((int)m);	CVectConv::SetupFixPointInVector(y, m_nRATAD_FPO1);
// -----------------------------------------------------------------------
printf("n=%d, m=%d : ", (int)n, (int)m);
// -----------------------------------------------------------------------
for (j=0; j<m; j++)
	{
	i0=((j*L-l)*(1.0/N))
		#ifdef SDRPDEMO_USEFIX
		.ConvertTo(i0)
		#endif
		+nOne;
	//iN=(int)(j*L/N);
	iN=(j*L*(1.0/N))			// (12.12.2002)
		#ifdef SDRPDEMO_USEFIX
		.ConvertTo(iN)
		#endif
		;
	y[(int)j]=0;
	for (i=i0; i<=iN; i++)
		{
		idx=j*L-i*N;
		hij=0;	if(idx>=0 && idx<l) hij=h[(int)idx];
		xi=0;	if(i>=0) xi=x[(int)i];
		y[(int)j]+=(xi*hij)
			#ifdef SDRPDEMO_USEFIX
			.ConvertTo(y[0]);
			#endif
			;
		}
	// -------------------------------------------------------------------
	printf(".");
	// -------------------------------------------------------------------
	}
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// -----------------------------------------------------------------------
int	CSDRPrims::RATAD_OutpVectLen() {
	if (m_nRATAD_n==CSDRP_ERROR || m_nRATAD_L==CSDRP_ERROR || 
		m_nRATAD_N==CSDRP_ERROR) return (CSDRP_ERROR);
	return(m_nRATAD_n*m_nRATAD_N/m_nRATAD_L); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::RATAD_Setup(CVectorFloat&h, int n, int L, int N, int l) {
	m_pRATAD_h=h; m_nRATAD_n=n; m_nRATAD_L=L; m_nRATAD_N=N; 
	m_nRATAD_l=l; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::RATAD_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nRATAD_FPIM[0]=nIL;	m_nRATAD_FPIM[2]=nIF;
	m_nRATAD_FPO1[0]=nO1L;	m_nRATAD_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::CWP(CVectorFloat&x, CVectorFloat&y, CVectorFloat&cwp)
{
// -----------------------------------------------------------------------
// Description: generates componentwise product of two vectors
//   Parametrs: n1	- len of x-vector
//				n2	- len of y-vector
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 05.11.2002
//          LE: 05.11.2002
// -----------------------------------------------------------------------
int n1=m_nCWP_n1, n2=m_nCWP_n2;
if (!m_bInited) _ASSERT(0);
if (n1==CSDRP_ERROR) return (false);
if (n2==CSDRP_ERROR) return (false);
if (n1!=n2) return (false);
	// (19.12.2002)
	#ifdef SDRPDEMO_USEFIX
	CVectConv::SetupFixPointInVector(cwp, m_nCWP_FPO1);
	#endif
for (int i=0; i<n1; i++) cwp[i]=x[i]*y[i];
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWP(CVectorCmplx&x, CVectorCmplx&y, CVectorCmplx&cwp)
{
int n1=m_nCWP_n1, n2=m_nCWP_n2;
if (!m_bInited) _ASSERT(0);
if (n1==CSDRP_ERROR) return (false);
if (n2==CSDRP_ERROR) return (false);
if (n1!=n2) return (false);
	// (19.12.2002)
	#ifdef SDRPDEMO_USEFIX
	CVectConv::SetupFixPointInVector(cwp, m_nCWP_FPO1);
	#endif
for (int i=0; i<n1; i++)
	cwp[i]=(x[i]*y[i])
	#ifdef SDRPDEMO_USEFIX
	.AsComplex(cwp[i])
	#endif
	;
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWP(CVectorFloat&xr, CVectorFloat&xi, CVectorFloat&yr, CVectorFloat&yi, CVectorFloat&cwpr, CVectorFloat&cwpi)
{
// -!---------------------------------------------------------------------
//          MD: 28.11.2002
//          LE: 17.12.2002
// -----------------------------------------------------------------------
int nSize=xr.size();
CVectorCmplx x(nSize);
CVectorCmplx y(nSize);
CVectorCmplx cwp(nSize);
// -----------------------------------------------------------------------
// adjusts fixed point position in intermediate and output vectors (17.12.2002)
// -----------------------------------------------------------------------
CVectConv::SetupFixPointInVector(x, m_nCWP_FPIM);
CVectConv::SetupFixPointInVector(y, m_nCWP_FPIM);
CVectConv::SetupFixPointInVector(cwpi, m_nCWP_FPO1);
CVectConv::SetupFixPointInVector(cwpr, m_nCWP_FPO1);
// -----------------------------------------------------------------------
CVectConv::ConvVectFloatToCmplx(xr, xi, x);
CVectConv::ConvVectFloatToCmplx(yr, yi, y);
BOOL bRes=CWP(x, y, cwp);
CVectConv::ConvVectCmplxToFloat(cwp, cwpr, cwpi);
return(bRes);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWP_Setup(int n1, int n2)	{
	m_nCWP_n1=n1; m_nCWP_n2=n2; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWP_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nCWP_FPIM[0]=nIL;		m_nCWP_FPIM[2]=nIF;
	m_nCWP_FPO1[0]=nO1L;	m_nCWP_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::CWS(CVectorFloat&x, CVectorFloat&y, CVectorFloat&cws)
{
// -----------------------------------------------------------------------
// Description: generates componentwise sum of two vectors
//   Parametrs: n1	- len of x-vector
//				n2	- len of y-vector
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 05.11.2002
//          LE: 05.11.2002
// -----------------------------------------------------------------------
int n1=m_nCWS_n1, n2=m_nCWS_n2;
if (!m_bInited) _ASSERT(0);
if (n1==CSDRP_ERROR) return (false);
if (n2==CSDRP_ERROR) return (false);
if (n1!=n2) return (false);
	#ifdef SDRPDEMO_USEFIX
	CVectConv::SetupFixPointInVector(cws, m_nCWS_FPO1);
	#endif
for (int i=0; i<n1; i++) cws[i]=x[i]+y[i];
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWS(CVectorCmplx&x, CVectorCmplx&y, CVectorCmplx&cws)
{
int n1=m_nCWS_n1, n2=m_nCWS_n2;
if (!m_bInited) _ASSERT(0);
if (n1==CSDRP_ERROR) return (false);
if (n2==CSDRP_ERROR) return (false);
if (n1!=n2) return (false);
	#ifdef SDRPDEMO_USEFIX
	CVectConv::SetupFixPointInVector(cws, m_nCWS_FPO1);
	#endif
for (int i=0; i<n1; i++) cws[i]=x[i]+y[i];
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWS(CVectorFloat&xr, CVectorFloat&xi, CVectorFloat&yr, CVectorFloat&yi, CVectorFloat&cwsr, CVectorFloat&cwsi)
{
// -!---------------------------------------------------------------------
//          MD: 28.11.2002
//          LE: 28.11.2002
// -----------------------------------------------------------------------
int nSize=xr.size();
CVectorCmplx x(nSize);
CVectorCmplx y(nSize);
CVectorCmplx cws(nSize);
CVectConv::SetupFixPointInVector(x, m_nCWS_FPIM);
CVectConv::SetupFixPointInVector(y, m_nCWS_FPIM);
CVectConv::SetupFixPointInVector(cws, m_nCWS_FPO1);
CVectConv::ConvVectFloatToCmplx(xr, xi, x);
CVectConv::ConvVectFloatToCmplx(yr, yi, y);
BOOL bRes=CWS(x, y, cws);
CVectConv::ConvVectCmplxToFloat(cws, cwsr, cwsi);
return(bRes);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWS_Setup(int n1, int n2) {
	m_nCWS_n1=n1; m_nCWS_n2=n2; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWS_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nCWS_FPIM[0]=nIL;		m_nCWS_FPIM[2]=nIF;
	m_nCWS_FPO1[0]=nO1L;	m_nCWS_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::CWS2(CVectorFloat&x, CFloat a, CVectorFloat&cws)
{
// -----------------------------------------------------------------------
// Description: adds a constant to all vector elements
//   Parametrs: ...
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 08.11.2002
//          LE: 19.12.2002, 06.01.2003
// -----------------------------------------------------------------------
int n=m_nCWS2_n;
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
	#ifdef SDRPDEMO_USEFIX
	CVectConv::SetupFixPointInVector(cws, m_nCWS2_FPO1);
	a.ConvertTo(x[0]);	// (06.01.2003)
	#endif
for (int i=0; i<n; i++)
	{
	cws[i]=x[i]+a;
	#ifdef DEBUG_XXX
	double dA=(double)x[i];
	double dB=(double)a;
	double dR=(double)cws[i];
	double dRes=dA+dB;
	double dErr=dR-dRes;
	//_ASSERT(dErr<=0.01);				// error is too great
	if (fabs(dErr)>0.01)
		printf("E");
	#endif
	}
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWS2(CVectorCmplx&x, CFloat a, CVectorCmplx&cws)
{
int n=m_nCWS2_n;
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
	#ifdef SDRPDEMO_USEFIX
	CVectConv::SetupFixPointInVector(cws, m_nCWS2_FPO1);
	#endif
for (int i=0; i<n; i++) cws[i]=x[i]+a;
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWS2(CVectorFloat&xr, CVectorFloat&xi, CFloat a, CVectorFloat&cwsr, CVectorFloat&cwsi)
{
// -!---------------------------------------------------------------------
//          MD: 28.11.2002
//          LE: 19.12.2002
// -----------------------------------------------------------------------
int nSize=xr.size();
CVectorCmplx x(nSize);
CVectorCmplx cws(nSize);
CVectConv::SetupFixPointInVector(x, m_nCWS2_FPIM);	// (18.12.2002)
CVectConv::SetupFixPointInVector(cwsr, m_nCWS2_FPO1);
CVectConv::SetupFixPointInVector(cwsi, m_nCWS2_FPO1);
CVectConv::ConvVectFloatToCmplx(xr, xi, x);
BOOL bRes=CWS2(x, a, cws);
CVectConv::ConvVectCmplxToFloat(cws, cwsr, cwsi);
return(bRes);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWS2_Setup(int n)
	{ m_nCWS2_n=n; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWS2_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nCWS2_FPIM[0]=nIL;	m_nCWS2_FPIM[2]=nIF;
	m_nCWS2_FPO1[0]=nO1L;	m_nCWS2_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::CWD(CVectorFloat&x, CVectorFloat&y, CVectorFloat&cwd)
{
// -----------------------------------------------------------------------
// Description: generates componentwise difference of two vectors
//   Parametrs: n1	- len of x-vector
//				n2	- len of y-vector
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 05.11.2002
//          LE: 05.11.2002
// -----------------------------------------------------------------------
int n1=m_nCWD_n1, n2=m_nCWD_n2;
if (!m_bInited) _ASSERT(0);
if (n1==CSDRP_ERROR) return (false);
if (n2==CSDRP_ERROR) return (false);
if (n1!=n2) return (false);
	#ifdef SDRPDEMO_USEFIX
	CVectConv::SetupFixPointInVector(cwd, m_nCWD_FPO1);
	#endif
for (int i=0; i<n1; i++) cwd[i]=x[i]-y[i];
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWD_Setup(int n1, int n2) {
	m_nCWD_n1=n1; m_nCWD_n2=n2; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWD_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nCWD_FPIM[0]=nIL;		m_nCWD_FPIM[2]=nIF;
	m_nCWD_FPO1[0]=nO1L;	m_nCWD_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::CWD2(CVectorFloat&x, CFloat a, CVectorFloat&cwd)
{
// -----------------------------------------------------------------------
// Description: generates componentwise difference of two vectors
//   Parametrs: n1	- len of x-vector
//				n2	- len of y-vector
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 07.11.2002
//          LE: 07.11.2002
// -----------------------------------------------------------------------
int n=m_nCWD2_n;
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
	#ifdef SDRPDEMO_USEFIX
	CVectConv::SetupFixPointInVector(cwd, m_nCWD2_FPO1);
	#endif
for (int i=0; i<n; i++)
	cwd[i]=x[i]-a;
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWD2_Setup(int n) {
	m_nCWD2_n=n; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWD2_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nCWD2_FPIM[0]=nIL;	m_nCWD2_FPIM[2]=nIF;
	m_nCWD2_FPO1[0]=nO1L;	m_nCWD2_FPO1[2]=nO1F; return(true); }
// =======================================================================
BOOL CSDRPrims::CWQ(CVectorFloat&x, CVectorFloat&y, CVectorFloat&cwq)
{
// -----------------------------------------------------------------------
// Description: generates componentwise quotient of two vectors
//   Parametrs: n1	- len of x-vector
//				n2	- len of y-vector
//      Return: true - ok, false - error
// -----------------------------------------------------------------------
//          MD: 05.11.2002
//          LE: 05.11.2002
// -----------------------------------------------------------------------
int n1=m_nCWQ_n1, n2=m_nCWQ_n2;
if (!m_bInited) _ASSERT(0);
if (n1==CSDRP_ERROR) return (false);
if (n2==CSDRP_ERROR) return (false);
if (n1!=n2) return (false);
	#ifdef SDRPDEMO_USEFIX
	CVectConv::SetupFixPointInVector(cwq, m_nCWQ_FPO1);
	#endif
for (int i=0; i<n1; i++) cwq[i]=x[i]*(1/y[i]);
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWQ_Setup(int n1, int n2)
	{ m_nCWQ_n1=n1; m_nCWQ_n2=n2; return(true); }
// =======================================================================
BOOL CSDRPrims::CWSQR(CVectorFloat&x, CVectorFloat&cwsqr)
{
// -----------------------------------------------------------------------
// Description: computes the absolute squares of the elements of the
//              input vector
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 05.11.2002
//          LE: 07.11.2002
// -----------------------------------------------------------------------
int n=m_nCWSQR_n;
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
	#ifdef SDRPDEMO_USEFIX
	CVectConv::SetupFixPointInVector(cwsqr, m_nCWSQR_FPO1);
	#endif
for (int i=0; i<n; i++)
	//cwsqr[i]=x[i].Conj()*x[i];	// this came from the complex version
	cwsqr[i]=x[i]*x[i];
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWSQR_Setup(int n) {
	m_nCWSQR_n=n; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWSQR_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nCWSQR_FPIM[0]=nIL;	m_nCWSQR_FPIM[2]=nIF;
	m_nCWSQR_FPO1[0]=nO1L;	m_nCWSQR_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::CWSC(CVectorFloat&x, CFloat a, CVectorFloat&cwsc)
{
// -----------------------------------------------------------------------
// Description: scales vector 'px' by a scaling factor 'da'
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 05.11.2002
//          LE: 07.11.2002
// -----------------------------------------------------------------------
int n=m_nCWSC_n;
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
	#ifdef SDRPDEMO_USEFIX
	CVectConv::SetupFixPointInVector(cwsc, m_nCWSC_FPO1);
	#endif
for (int i=0; i<n; i++) 
	cwsc[i]=x[i]*a;	
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWSC_Setup(int n) {
	m_nCWSC_n=n; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::CWSC_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nCWSC_FPIM[0]=nIL;	m_nCWSC_FPIM[2]=nIF;
	m_nCWSC_FPO1[0]=nO1L;	m_nCWSC_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::ABS(CVectorFloat&x, CVectorFloat&y)
{
// -----------------------------------------------------------------------
// Description: computes the absolute value of the input vector x
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 05.11.2002
//          LE: 05.11.2002
// -----------------------------------------------------------------------
int n=m_nABS_n;
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
	#ifdef SDRPDEMO_USEFIX
	CVectConv::SetupFixPointInVector(y, m_nABS_FPO1);
	#endif
for (int i=0; i<n; i++) y[i]=fabs(x[i]);
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::ABS_Setup(int n) {
	m_nABS_n=n; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::ABS_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nABS_FPIM[0]=nIL;		m_nABS_FPIM[2]=nIF;
	m_nABS_FPO1[0]=nO1L;	m_nABS_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::SQRSUM(CVectorFloat&x, CFloat& y)
{
// -----------------------------------------------------------------------
// Description: computes the sum of absolute squares of the elements of the
//              input vector
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 05.11.2002
//          LE: 07.11.2002
// -----------------------------------------------------------------------
int n=m_nSQRSUM_n;
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
	#ifdef SDRPDEMO_USEFIX
	y.Setup(m_nSQRSUM_FPO1);
	#endif
y=0;
//for (int i=0; i<n; i++) y=y+x[i].Conj()*tx[i];	// complex
for (int i=0; i<n; i++) y=y+x[i]*x[i];
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::SQRSUM_Setup(int n) {
	m_nSQRSUM_n=n; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::SQRSUM_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nSQRSUM_FPIM[0]=nIL;	m_nSQRSUM_FPIM[2]=nIF;
	m_nSQRSUM_FPO1[0]=nO1L;	m_nSQRSUM_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::PHASE(CVectorCmplx&x, CVectorInt&y)
{
// -----------------------------------------------------------------------
// Description: computes the phase of the input vector
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 05.11.2002
//          LE: 07.11.2002
// -----------------------------------------------------------------------
int n=m_nPHASE_n;
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
int nPI=180;
for (int i=0; i<n; i++) 	
	{
	y[i]=Rad2Deg(atan(x[i].Im()*(1/x[i].Re())));
	if (x[i].Re()>=0) y[i]=y[i]+nPI;
	}	
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::PHASE(CVectorFloat&xr, CVectorFloat&xi, CVectorInt&y)
{
// -!---------------------------------------------------------------------
//          MD: 28.11.2002
//          LE: 28.11.2002
// -----------------------------------------------------------------------
int nSize=xr.size();
CVectorCmplx x(nSize);
CVectConv::ConvVectFloatToCmplx(xr, xi, x);
BOOL bRes=PHASE(x, y);
return(bRes);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::PHASE_Setup(int n) {
	m_nPHASE_n=n; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::PHASE_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nPHASE_FPIM[0]=nIL;	m_nPHASE_FPIM[2]=nIF;
	m_nPHASE_FPO1[0]=nO1L;	m_nPHASE_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::CCPLX(CVectorCmplx&x, CVectorCmplx&y)
{
// -----------------------------------------------------------------------
// Description: computes the conjugate complex of input vector
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 05.11.2002
//          LE: 07.11.2002
// -----------------------------------------------------------------------
int n=m_nCCPLX_n; if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
for (int i=0; i<n; i++) y[i]=x[i].Conj();
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CCPLX(CVectorFloat&xr, CVectorFloat&xi, CVectorFloat&yr, CVectorFloat&yi)
{
// -!---------------------------------------------------------------------
// Description: pseudo complex version of CCPLX
//          MD: 28.11.2002
//          LE: 28.11.2002
// -----------------------------------------------------------------------
int nSize=xr.size();
CVectorCmplx x(nSize);
CVectorCmplx y(nSize);
CVectConv::ConvVectFloatToCmplx(xr, xi, x);
BOOL bRes=CCPLX(x, y);
CVectConv::ConvVectCmplxToFloat(y, yr, yi);
return(bRes);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::CCPLX_Setup(int n)
	{ m_nCCPLX_n=n; return(true); }
// =======================================================================
BOOL CSDRPrims::VSUM(CVectorFloat&x, CFloat &vsum)
{
// -----------------------------------------------------------------------
// Description: computes the sum over componetns of the input vector
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 05.11.2002
//          LE: 07.11.2002
// -----------------------------------------------------------------------
int n=m_nVSUM_n; if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
	#ifdef SDRPDEMO_USEFIX
	vsum.Setup				(m_nVSUM_FPO1);
	#endif
vsum=0;
for (int i=0; i<n; i++) vsum+=x[i];
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::VSUM_Setup(int n) {
	m_nVSUM_n=n; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::VSUM_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nVSUM_FPIM[0]=nIL;	m_nVSUM_FPIM[2]=nIF;
	m_nVSUM_FPO1[0]=nO1L;	m_nVSUM_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::SWA(CVectorFloat&x, CVectorFloat&y)
{
// -----------------------------------------------------------------------
// Description: calculates the n-l+1 average values of the elements of the
//				input block over a sliding window of lenght l
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 05.11.2002
//          LE: 07.11.2002
// -----------------------------------------------------------------------
// l:=n+1-y.size()
// -----------------------------------------------------------------------
CInt l, n;
CInt i, k;
CInt nOne;
	#ifdef SDRPDEMO_USEFIX
	CVectConv::SetupFixPointInVector(y, m_nSWA_FPO1);
	#endif
if (!m_bInited) _ASSERT(0);
if (l==CSDRP_ERROR) return (false);
if (n==CSDRP_ERROR) return (false);
l=m_nSWA_l; n=m_nSWA_n; nOne=1;
for (i=0; i<=n-l; i++)
	{
	y[(int)i]=0;
	for (k=i; k<=i+l-nOne; k++)		// WARNING: j<i+l-1 or j<=i+l-1 ?
		y[(int)i]=y[(int)i]+x[(int)k];
	y[(int)i]=y[(int)i]*(1.0/l);
	}
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::SWA_Setup(int l, int n) {
	m_nSWA_l=l; m_nSWA_n=n; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::SWA_SetupFP (int nIL, int nIF, int nO1L, int nO1F)	{
	m_nSWA_FPIM[0]=nIL;		m_nSWA_FPIM[2]=nIF;
	m_nSWA_FPO1[0]=nO1L;	m_nSWA_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::SINGEN (double f, double phi, CVectorCmplx&y)
{
// -----------------------------------------------------------------------
// Description: generates the complex wave
//   Parametrs: f		- frequency (normalized by PI: 0=>0, 1=>PI)
//				phi		- phase in RADIANs
//				y		- ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 07.11.2002
//          LE: 11.11.2002, 09.12.2002, 18.12.2002, 03.01.2003
// -----------------------------------------------------------------------
int n=m_nSINGEN_n, w=m_nSINGEN_w;
//if (!m_bInited) return (false);
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
if (w==CSDRP_ERROR) return (false);
// -----------------------------------------------------------------------
// new version (w/o multiplication) (18.12.2002)
double dAngle, dStep;
CFloat dRe, dIm;
// -----------------------------------------------------------------------
	#ifdef SDRPDEMO_USEFIX
	CVectConv::SetupFixPointInVector(y, m_nSINGEN_FPO1);
	dRe.Setup				(m_nSINGEN_FPO1);
	dIm.Setup				(m_nSINGEN_FPO1);
	#endif
// -----------------------------------------------------------------------
dStep=2*M_PI*f/double(m_dSR);
dAngle=0;					// actually it's = dStep*0 + phi
// -----------------------------------------------------------------------
for (int i=0; i<n; i++)
	{
	dRe=cos(dAngle+phi);
	dIm=sin(dAngle+phi);
	y[i]=CComplex(dRe, dIm);
	dAngle=dAngle+dStep;
	}
// -----------------------------------------------------------------------
/* // old version
double dAngle; CFloat dRe, dIm;
// -----------------------------------------------------------------------
// 18.12.2002
#ifdef SDRPDEMO_USEFIX
dRe.Setup(m_nSINGEN_FPO1[0], m_nSINGEN_FPO1[2]);
dIm.Setup(m_nSINGEN_FPO1[0], m_nSINGEN_FPO1[2]);
#endif
// -----------------------------------------------------------------------
for (int i=0; i<n; i++)
	{	
	//dAngle=2*M_PI*f*i*(1/m_dSR)+phi;	// rewritten for especially for CFixNum::operator* (..)
	dAngle=2*M_PI*(double)f*i*(double)(1/m_dSR)+(double)phi;
	dRe=cos(dAngle);
	dIm=sin(dAngle);
	y[i]=CComplex(dRe, dIm);
	}//*/
// -----------------------------------------------------------------------
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::SINGEN (double f, double phi, CVectorFloat&yr, CVectorFloat&yi)
{
// -!---------------------------------------------------------------------
//          MD: 28.11.2002
//          LE: 18.11.2002
// -----------------------------------------------------------------------
int nSize=yr.size();
CVectorCmplx y(nSize);
// -----------------------------------------------------------------------
CVectConv::SetupFixPointInVector(yr, m_nSINGEN_FPO1);	// 18.12.2002
CVectConv::SetupFixPointInVector(yi, m_nSINGEN_FPO1);	// 18.12.2002
// -----------------------------------------------------------------------
BOOL bRes=SINGEN(f, phi, y);
CVectConv::ConvVectCmplxToFloat(y, yr, yi);
return(bRes);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::SINGEN_Setup (int n, int w)	{
	m_nSINGEN_n=n;		m_nSINGEN_w=w; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::SINGEN_SetupFP (int nIL, int nIF, int nO1L, int nO1F)	{
	m_nSINGEN_FPIM[0]=nIL;	m_nSINGEN_FPIM[2]=nIF;
	m_nSINGEN_FPO1[0]=nO1L;	m_nSINGEN_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
// New primitives (implemented by Me)
// =======================================================================
BOOL CSDRPrims::VMEAN(CVectorFloat&x, CFloat& vmean)
{
// -----------------------------------------------------------------------
// Description: calculates the average value of the input vector x
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 07.11.2002
//          LE: 18.12.2002, 06.01.2003
// -----------------------------------------------------------------------
int n=m_nVMEAN_n;
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
// -----------------------------------------------------------------------
CFloat accum, nSize;		// (17.12.2002)
	#ifdef SDRPDEMO_USEFIX
	accum.Setup				(m_nVMEAN_FPIM);
	vmean.Setup				(m_nVMEAN_FPO1);
	nSize.SetupAsInt		(m_nVMEAN_FPIM[0]);
	#endif
// -----------------------------------------------------------------------
nSize=n;
accum=0;
for (int i=0; i<n; i++)
	{
	accum+=x[i]
		#ifdef SDRPDEMO_USEFIX
		.AsFixNum(accum)
		#endif
		;
	#ifdef SDRPDEMO_USEFIX
	if (accum.ovf_occurred()) _ASSERT(0);
	#endif
	}
if (n<=0) return(false);
accum=(accum*(1.0/nSize)
	#ifdef SDRPDEMO_USEFIX
	.ConvertTo(accum)
	#endif
	)
	#ifdef SDRPDEMO_USEFIX
	.ConvertTo(accum)
	#endif
	;
vmean=accum
	#ifdef SDRPDEMO_USEFIX
	.ConvertTo(vmean)
	#endif
	;
// -----------------------------------------------------------------------
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::VMEAN_Setup(int n)	{
	m_nVMEAN_n=n; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::VMEAN_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nVMEAN_FPIM[0]=nIL;	m_nVMEAN_FPIM[2]=nIF;
	m_nVMEAN_FPO1[0]=nO1L;	m_nVMEAN_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
BOOL CSDRPrims::VSQRMEAN(CVectorCmplx&x, CFloat& vsqmn)
{
// -----------------------------------------------------------------------
// Description: calculates the average squared value of the input vector x
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 08.11.2002
//          LE: 08.11.2002, 12.12.2002, 18.12.2002
// -----------------------------------------------------------------------
int n=m_nVSQRMEAN_n;
if (!m_bInited) _ASSERT(0);
if (n==CSDRP_ERROR) return (false);
CComplex xsqr;
CFloat accum, dInv;
// -----------------------------------------------------------------------
	#ifdef SDRPDEMO_USEFIX
	accum.Setup				(m_nVSQRMEAN_FPIM);
	xsqr.Setup				(m_nVSQRMEAN_FPIM);
	dInv.Setup				(m_nVSQRMEAN_FPIM);
	vsqmn.Setup				(m_nVSQRMEAN_FPO1);
	#endif
// -----------------------------------------------------------------------
accum=0;
for (int i=0; i<n; i++)
	{
	xsqr=(x[i].Conj()*x[i])
		#ifdef SDRPDEMO_USEFIX
		.AsComplex(xsqr)
		#endif
		;
	accum+=xsqr.Re();
	#ifdef SDRPDEMO_USEFIX
	if (accum.ovf_occurred()) _ASSERT(0);
	#endif
	}
if (n<=0) return(false);
dInv=1.0/n;
vsqmn=(accum*dInv)
	#ifdef SDRPDEMO_USEFIX
	.ConvertTo(vsqmn)
	#endif
	;
return(true);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::VSQRMEAN(CVectorFloat&xr, CVectorFloat&xi, CFloat& vsqmn)
{
// -!---------------------------------------------------------------------
//          MD: 28.11.2002
//          LE: 18.12.2002
// -----------------------------------------------------------------------
int nSize=xr.size();
CVectorCmplx x(nSize);
CVectConv::SetupFixPointInVector(x, m_nVSQRMEAN_FPIM);
CVectConv::ConvVectFloatToCmplx(xr, xi, x);
BOOL bRes=VSQRMEAN(x, vsqmn);
return(bRes);
}
// -----------------------------------------------------------------------
BOOL CSDRPrims::VSQRMEAN_Setup(int n)	{
	m_nVSQRMEAN_n=n; return(true); }
// -----------------------------------------------------------------------
BOOL CSDRPrims::VSQRMEAN_SetupFP(int nIL, int nIF, int nO1L, int nO1F)	{
	m_nVSQRMEAN_FPIM[0]=nIL;	m_nVSQRMEAN_FPIM[2]=nIF;
	m_nVSQRMEAN_FPO1[0]=nO1L;	m_nVSQRMEAN_FPO1[2]=nO1F;
	return(true); }
// =======================================================================
int CSDRPrims::max(int nD1, int nD2)
	{ return (nD1>nD2)?nD1:nD2; }
// -----------------------------------------------------------------------
CFloat CSDRPrims::max(CFloat dD1, CFloat dD2)
	{ return (dD1>dD2)?dD1:dD2; }
// =======================================================================
int CSDRPrims::min(int nD1, int nD2)
	{ return (nD1<nD2)?nD1:nD2; }
// -----------------------------------------------------------------------
CFloat CSDRPrims::min(CFloat dD1, CFloat dD2)
	{ return (dD1<dD2)?dD1:dD2; }
// =======================================================================
int CSDRPrims::Rad2Deg(double dRad) {
	return(int)(dRad*180*(1.0/M_PI)); }
// =======================================================================
CFloat CSDRPrims::ReduceAngleRad(CFloat dAngle)
{
// -----------------------------------------------------------------------
// Description: reduces angle given in radians to fit in [-PI, +PI] range
//   Parametrs: ...
//      Return: reduced angle value in the range [-PI, +PI]
// -----------------------------------------------------------------------
//          MD: 08.11.2002
//          LE: 08.11.2002
// -----------------------------------------------------------------------
if (dAngle>=-M_PI && dAngle<=M_PI) return (dAngle);
CFloat dNewAngle, dAddVal;
// -----------------------------------------------------------------------
dNewAngle=dAngle;
dAddVal=dAngle>0?2*M_PI:-2*M_PI;
do	{
	dNewAngle=dNewAngle-dAddVal;
	if (dNewAngle>-2*M_PI && dNewAngle<2*M_PI)
		Rad2Deg(dNewAngle);
	} while (dNewAngle<-M_PI || dNewAngle>M_PI);
// -----------------------------------------------------------------------
return (dNewAngle);
// -----------------------------------------------------------------------
}
// =======================================================================
// 802.11a primitives
// =======================================================================
BOOL CSDRPrims::SCRAMBL(CVectorBool &x, CVectorBool &y, CVectorBool &pState)	{
// -!---------------------------------------------------------------------
// Description: scrambles input array
//   Parametrs: x		- input bit stream
//				y		- output (scrambled) bit streams
//				pState	- initial state of the scrambler
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 15.01.2003
//          LE: 15.01.2003
// -----------------------------------------------------------------------
	_ASSERT(x.size());				// input vector is empty
	_ASSERT(x.size()==y.size());	// space is not reserved
	_ASSERT(pState.size()==7);		// wrong size of the state array
	// -------------------------------------------------------------------
	int i, j;
	int nSize=x.size();
	CVectorBool pX(7);
	// -------------------------------------------------------------------
	// copies state
	// -------------------------------------------------------------------
	for(i=0; i<7; i++) pX[i]=pState[i];
	// -------------------------------------------------------------------
	// scrambling
	// -------------------------------------------------------------------
	for(i=0; i<nSize; i++)
		{
		int bScram= pX[7-1] ^ pX[4-1];
		y[i]=x[i] ^ bScram;
		for (j=6; j>0; j--)
			pX[j]=pX[j-1];
		pX[0]=bScram;
		//_DEBUG_TRACEVAR("Data\\p802SCRAMBL.txt", ((i%8)?"%d,\n":"\n%d,\n"), bScram); // (17.01.2003)
		}
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDRPrims::CONVENC(CVectorBool &z, CVectorBool &x, CVectorBool &y)	{
// -!---------------------------------------------------------------------
// Description: convolutional encoder
//   Parametrs: z		- input bit stream
//				x, y	- output bit streams
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 09.01.2003
//          LE: 09.01.2003
// -----------------------------------------------------------------------
	_ASSERT(z.size());				// input vector is empty
	//_ASSERT(z.size()==x.size());	// REM: no space reserved (space will be generated automatically)
	//_ASSERT(z.size()==y.size());	// REM: no space reserved (space will be generated automatically)
	int nSize=z.size();
	// -------------------------------------------------------------------
	x=CVectorBool(nSize);
	y=CVectorBool(nSize);
	// -------------------------------------------------------------------
	CVectorBool pA(7);
	for (int i=0; i<nSize; i++)
		{
		pA[0]=z[i];
		x[i]=pA[0]^pA[2]^pA[3]^pA[5]^pA[6];
		y[i]=pA[0]^pA[1]^pA[2]^pA[3]^pA[6];
		for (int j=6; j>0; j--)
			pA[j]=pA[j-1];			// shiftes data in the memory
		}
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDRPrims::PUNCT(CVectorBool &x, CVectorBool &y, CVectorBool &z, CVectorBool &pMX, CVectorBool &pMY)	{
// -!---------------------------------------------------------------------
// Description: puncturing and parallel to serial convertor
//   Parametrs: x, y		- two input bit streams
//				z			- output bit stream
//				pMX, pMY	- bitmasks for X and Y input bitsreams
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 09.01.2003
//          LE: 09.01.2003
// -----------------------------------------------------------------------
	_ASSERT(x.size());
	_ASSERT(x.size()==y.size());
	//_ASSERT(z.size());		// size of the 'z' will be autocalculated (at this step)
	_ASSERT(pMX.size());
	_ASSERT(pMY.size());
	_ASSERT(pMX.size()==pMY.size());
	// -------------------------------------------------------------------
	int i, idxPat, idxZ=0;	// idx, idx in pattern, idx in Z
	int nOneBits=0;
	int nSizeX=x.size();
	int nSizeZ=0;
	int nSizePat=pMX.size();
	double dCodeRate;
	// -------------------------------------------------------------------
	// calculates size of the output array
	// -------------------------------------------------------------------
	for (i=0; i<nSizePat; i++)
		{
		if (pMX[i]) nOneBits++;
		if (pMY[i]) nOneBits++;
		}
	dCodeRate=double(nOneBits)/double(2*nSizePat);
	nSizeZ=(2*nSizeX)*dCodeRate;
	// -------------------------------------------------------------------
	// fills ouput array
	// -------------------------------------------------------------------
	z=CVectorBool(nSizeZ);
	for (i=0; i<nSizeX; i++)
		{
		idxPat=i%nSizePat;
		if (pMX[idxPat]) z[idxZ++]=x[i];
		if (pMY[idxPat]) z[idxZ++]=y[i];
		}
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDRPrims::INTLEAV(CVectorBool &x, CVectorBool &y, int nNcbps, int nNbpsc)	{
// -!---------------------------------------------------------------------
// Description: performs an interleaving over a binary vector
//   Parametrs: x		- input bit streams
//				y		- output bit stream
//				nNcbps	- number of bits in a single OFDM symbol
//				nNbpsc	- used only in case of 16QAM, 64QAM
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 10.01.2003
//          LE: 10.01.2003
// -----------------------------------------------------------------------
	_ASSERT(x.size());
	//_ASSERT(x.size()==y.size());	// space is generated automatically at this step
	_ASSERT(nNcbps==48 || nNcbps==96 || nNcbps==192 || nNcbps==288);
	_ASSERT(!(x.size()%nNcbps));	// size of the input array is not 
									// a multiply of 'nNcbps'
	// -------------------------------------------------------------------
	int nSizeX=x.size();
	int nBlocks=nSizeX/nNcbps;
	int i, j;
	CVectorBool pBLi(nNcbps),			// input block
		pBLo1(nNcbps), pBLo2(nNcbps);	// output blocks (IL1, IL2)
	// -------------------------------------------------------------------
	y=CVectorBool(nSizeX);
	// -------------------------------------------------------------------
	for (i=0; i<nBlocks; i++)
		{
		for (j=0; j<nNcbps; j++) pBLi[j]=x[i*nNcbps + j];
		INTLEAV1(pBLi, pBLo1, nNcbps);
		if (nNcbps==192 || nNcbps==288)	// 16QAM, 64QAM
			INTLEAV2(pBLo1, pBLo2, nNcbps, nNbpsc);
		else
			pBLo2=pBLo1;
		for (j=0; j<nNcbps; j++) y[i*nNcbps + j]=pBLo2[j];
		}
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDRPrims::INTLEAV1(CVectorBool &x, CVectorBool &y, int nNcbps)	{
// -!---------------------------------------------------------------------
// Description: performs the first step interleaving of a block
//   Parametrs: x		- input bit streams
//				y		- output bit stream
//				nNcbps	- number of bits in a single OFDM symbol
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 10.01.2003
//          LE: 10.01.2003
// -----------------------------------------------------------------------
	_ASSERT(x.size());
	_ASSERT(x.size()==y.size());
	_ASSERT(nNcbps==48 || nNcbps==96 || nNcbps==192 || nNcbps==288);
	// -------------------------------------------------------------------
	int i;
	for (int k=0; k<=nNcbps-1; k++)
		{
		i=(nNcbps/16)*(k % 16) + floor(k/16.);
		y[i]=x[k];
		}
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDRPrims::INTLEAV2(CVectorBool &x, CVectorBool &y, int nNcbps, int nNbpsc)	{
// -!---------------------------------------------------------------------
// Description: performs the second step interleaving of a block
//   Parametrs: x		- input bit streams
//				y		- output bit stream
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 10.01.2003
//          LE: 10.01.2003
// -----------------------------------------------------------------------
	_ASSERT(x.size());
	_ASSERT(x.size()==y.size());
	_ASSERT(nNcbps==192 || nNcbps==288);
	// -------------------------------------------------------------------
	int j;
	int s=max(nNbpsc/2, 1);
	for (int i=0; i<=nNcbps-1; i++)
		{
		j=s*floor(double(i)/double(s))+int(i+ nNcbps - floor(16*i/nNcbps))%s;
		y[j]=x[i];
		}
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDRPrims::MODUL_16QAM(CVectorBool &x, CVectorFloat &I, CVectorFloat &Q)	{
// -----------------------------------------------------------------------
// Description: performs 16QAM modulation over a 192 bits block
//   Parametrs: x		- input bit streams
//				I		- output I stream (freq. domain)
//				Q		- output I stream (freq. domain)
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 16.01.2003
//          LE: 16.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	_ASSERT(x.size());
	_ASSERT(x.size()==48*4);	// wrong size of the input array
	// -------------------------------------------------------------------
	int i;
	int nSizeX=x.size();
	int nSizeY=11+nSizeX/4;		// plus 6 starting and 5 ending zeros
	double dKmod=1./sqrt(10);	// normalization factor
	// -------------------------------------------------------------------
	I=CVectorFloat(nSizeY);
	Q=CVectorFloat(nSizeY);
	// -------------------------------------------------------------------
	for (i=0; i<nSizeY; i++)	{
		if (x[i*4+0]==0 && x[i*4+1]==0) I[i+6]=-3;
		if (x[i*4+0]==0 && x[i*4+1]==1) I[i+6]=-1;
		if (x[i*4+0]==1 && x[i*4+1]==1) I[i+6]= 1;
		if (x[i*4+0]==1 && x[i*4+1]==0) I[i+6]= 3;

		if (x[i*4+2]==0 && x[i*4+3]==0) Q[i+6]=-3;
		if (x[i*4+2]==0 && x[i*4+3]==1) Q[i+6]=-1;
		if (x[i*4+2]==1 && x[i*4+3]==1) Q[i+6]= 1;
		if (x[i*4+2]==1 && x[i*4+3]==0) Q[i+6]= 3;
		}
	// -------------------------------------------------------------------
	for (i=0; i<nSizeY; i++)	{
			I[i]*=dKmod; Q[i]*=dKmod; }
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDRPrims::MODUL_64QAM(CVectorBool &x, CVectorFloat &I, CVectorFloat &Q)	{
// -!---------------------------------------------------------------------
// Description: performs 64QAM modulation over a 288 bits sequence
//   Parametrs: x		- input bit streams
//				I		- output I stream (freq. domain)
//				Q		- output I stream (freq. domain)
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 21.01.2003
//          LE: 21.01.2003
// -----------------------------------------------------------------------
//		  TODO: test it !
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	_ASSERT(x.size());
	_ASSERT(x.size()==48*6);	// wrong size of the input array
	// -------------------------------------------------------------------
	int i;
	int nSizeX=x.size();
	int nSizeY=11+nSizeX/6;		// plus 6 starting and 5 ending zeros
	double dKmod=1./sqrt(42);	// normalization factor
	// -------------------------------------------------------------------
	I=CVectorFloat(nSizeY);
	Q=CVectorFloat(nSizeY);
	// -------------------------------------------------------------------
	for (i=0; i<nSizeY; i++)	{
		if (x[i*6+0]==0 && x[i*6+1]==0 && x[i*6+2]==0) I[i+6]=-7;
		if (x[i*6+0]==0 && x[i*6+1]==0 && x[i*6+2]==1) I[i+6]=-5;
		if (x[i*6+0]==0 && x[i*6+1]==1 && x[i*6+2]==1) I[i+6]=-3;
		if (x[i*6+0]==0 && x[i*6+1]==1 && x[i*6+2]==0) I[i+6]=-1;

		if (x[i*6+0]==1 && x[i*6+1]==1 && x[i*6+2]==0) I[i+6]=1;
		if (x[i*6+0]==1 && x[i*6+1]==1 && x[i*6+2]==1) I[i+6]=3;
		if (x[i*6+0]==1 && x[i*6+1]==0 && x[i*6+2]==1) I[i+6]=5;
		if (x[i*6+0]==1 && x[i*6+1]==0 && x[i*6+2]==0) I[i+6]=7;
	
		if (x[i*6+3]==0 && x[i*6+4]==0 && x[i*6+5]==0) Q[i+6]=-7;
		if (x[i*6+3]==0 && x[i*6+4]==0 && x[i*6+5]==1) Q[i+6]=-5;
		if (x[i*6+3]==0 && x[i*6+4]==1 && x[i*6+5]==1) Q[i+6]=-3;
		if (x[i*6+3]==0 && x[i*6+4]==1 && x[i*6+5]==0) Q[i+6]=-1;

		if (x[i*6+3]==1 && x[i*6+4]==1 && x[i*6+5]==0) Q[i+6]=1;
		if (x[i*6+3]==1 && x[i*6+4]==1 && x[i*6+5]==1) Q[i+6]=3;
		if (x[i*6+3]==1 && x[i*6+4]==0 && x[i*6+5]==1) Q[i+6]=5;
		if (x[i*6+3]==1 && x[i*6+4]==0 && x[i*6+5]==0) Q[i+6]=7;
		}
	// -------------------------------------------------------------------
	for (i=0; i<nSizeY; i++)	{
		I[i]*=dKmod; Q[i]*=dKmod; }
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDRPrims::MODUL_BPSK(CVectorBool &x, CVectorFloat &I, CVectorFloat &Q)	{
// -----------------------------------------------------------------------
// Description: performs BPSK modulation over a 48 bits sequence
//   Parametrs: x		- input bit streams
//				I		- output I stream (freq. domain)
//				Q		- output I stream (freq. domain)
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 10.01.2003
//          LE: 16.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	_ASSERT(x.size());
	_ASSERT(x.size()==48);	// wrong size of the input array
	// -------------------------------------------------------------------
	int nSizeX=x.size();
	int nSizeY=nSizeX+11;		// plus 6 starting and 5 ending zeros
	// -------------------------------------------------------------------
	I=CVectorFloat(nSizeY);
	Q=CVectorFloat(nSizeY);
	// -------------------------------------------------------------------
	for (int i=0; i<nSizeX; i++)	{
		I[i+6]=(x[i])?(1):(-1);
		Q[i+6]=0;
		}
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDRPrims::MODUL_QPSK(CVectorBool &x, CVectorFloat &I, CVectorFloat &Q)	{
// -----------------------------------------------------------------------
// Description: performs QPSK modulation over a 96 bits block
//   Parametrs: x		- input bit streams
//				I		- output I stream (freq. domain)
//				Q		- output I stream (freq. domain)
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 21.01.2003
//          LE: 21.01.2003
// -----------------------------------------------------------------------
//		  TODO: test it !
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	_ASSERT(x.size());
	_ASSERT(x.size()==48*2);	// wrong size of the input array
	// -------------------------------------------------------------------
	int i;
	int nSizeX=x.size();
	int nSizeY=11+nSizeX/2;		// plus 6 starting and 5 ending zeros
	double dKmod=1./sqrt(2);	// normalization factor
	// -------------------------------------------------------------------
	I=CVectorFloat(nSizeY);
	Q=CVectorFloat(nSizeY);
	// -------------------------------------------------------------------
	for (i=0; i<nSizeY; i++)	{
		if (x[i*2+0]==0) I[i+6]=-1;
		if (x[i*2+0]==1) I[i+6]=1;
		
		if (x[i*2+1]==0) Q[i+6]=-1;
		if (x[i*2+1]==1) Q[i+6]=1;
		}
	// -------------------------------------------------------------------
	for (i=0; i<nSizeY; i++)	{
		I[i]*=dKmod; Q[i]*=dKmod; }
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDRPrims::IsPowerOfTwo(int nNumber)	{
	double dPow=log(nNumber)/log(2);
	int nPow=ceil(dPow);
	int nNumber2=1 << nPow;
	return(nNumber==nNumber2);
	}
// =======================================================================
BOOL CSDRPrims::WindowW(CVectorFloat &x, CVectorFloat &y, int nSize)	{
// -!---------------------------------------------------------------------
// Description: window function
//   Parametrs: x		- input vector
//				y		- output vector
//				nSize	- size of the window (=x.size())
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 14.01.2003
//          LE: 14.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	_ASSERT(x.size());
	_ASSERT(y.size());
	_ASSERT(x.size()==y.size());
	_ASSERT(x.size()==nSize);
	// -------------------------------------------------------------------
	y=x;
	y[0]*=0.5;
	y[y.size()-1]*=0.5;
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
