// =======================================================================
// SDRPrims ver. 1.0
// impementation: floating point (double)
// -----------------------------------------------------------------------
//       MD: 05.11.2002
//       LE: 07.11.2002
// -----------------------------------------------------------------------
// Compiler: MS VC 6.0
// =======================================================================
// SDRPrims.h: interface for the CSDRPrims class.
// =======================================================================
#if !defined(AFX_SDRPRIMS_H__5E9EE5B9_058F_4E8A_87CF_FF5D442CDF0E__INCLUDED_)
#define AFX_SDRPRIMS_H__5E9EE5B9_058F_4E8A_87CF_FF5D442CDF0E__INCLUDED_
// =======================================================================
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// =======================================================================
#include "DataTypes.h"	// 05.11.2002, 04.12.2002
// =======================================================================
// CSDRPrims errors
// =======================================================================
const int CSDRP_ERROR=-1;	// error (07.11.2002)
// =======================================================================
// some declarations
// =======================================================================
// =======================================================================
// CSDRPrimitives (05.11.2002)
// =======================================================================
class CSDRPrims
{
public:
	static BOOL MODUL_QPSK(CVectorBool &x, CVectorFloat &I, CVectorFloat &Q);
	static BOOL MODUL_64QAM(CVectorBool &x, CVectorFloat &I, CVectorFloat &Q);
	static BOOL MODUL_16QAM(CVectorBool&x, CVectorFloat& I, CVectorFloat& Q);
	static BOOL WindowW(CVectorFloat&x, CVectorFloat&y, int nSize);	// window function (14.01.2003)
	static BOOL IsPowerOfTwo(int nNumber);		// returns true, if given number is a power of two (13.01.2003)
	// -------------------------------------------------------------------
	// Binary data processing primitives (need for IEEE 802.11a)
	// -------------------------------------------------------------------
	static BOOL IFFT(CVectorFloat&xr, CVectorFloat&xi, CVectorFloat&yr, CVectorFloat&yi);	// inverse Fourier transform (13.01.2003)
	static BOOL FFT(CVectorFloat&xr, CVectorFloat&xi, CVectorFloat&yr, CVectorFloat&yi);	// Fourier transform (13.01.2003)
	static BOOL MODUL_BPSK(CVectorBool& x, CVectorFloat& I, CVectorFloat& Q);	// performs BPSK modulation over a bit sequence (10.01.2003)
	static BOOL INTLEAV(CVectorBool&x, CVectorBool&y, int nNcbps, int nNbpsc);	// performs an interleaving over a binary vector (10.01.2003)
	static BOOL INTLEAV1(CVectorBool &x, CVectorBool &y, int nNcbps);			// performs the first step interleaving of a block (10.01.2003)
	static BOOL INTLEAV2(CVectorBool&x, CVectorBool&y, int nNcbps, int nNbpsc);	// performs the second step interleaving of a block (10.01.2003)
	static BOOL PUNCT(CVectorBool&x, CVectorBool&y, CVectorBool&z, CVectorBool& pMX, CVectorBool& pMY);	// puncturing and parallel to serial convertor (09.01.2003)
	static BOOL CONVENC(CVectorBool&z, CVectorBool&x, CVectorBool&y);			// convolutional encoder (09.01.2003)
	static BOOL SCRAMBL(CVectorBool&x, CVectorBool&y, CVectorBool& pState);		// scrambles input array (15.01.2003)
	// -------------------------------------------------------------------
	// Primitives
	// -------------------------------------------------------------------
	BOOL DOTP2			(CVectorFloat&x, CVectorFloat&y, CFloat& dotp);	// (f.3.2)
	BOOL DOTP2_Setup	(int n1, int n2);								// setup of (f.3.2)
	BOOL ACFPNT		(CVectorCmplx&x, CComplex& y);						// (f.3.5)
	BOOL ACFPNT		(CVectorFloat&xr, CVectorFloat&xi, CFloat& acfpntr, CFloat& acfpnti);	// pseudo complex version of ACFPNT (f.3.5)
	BOOL ACFPNT_Setup	(int n, int s);									// setup: (f.3.5)
	BOOL FIR		(CVectorFloat&x, CVectorFloat&y);					// (f.3.8)
	BOOL FIR_Setup	(CVectorFloat&h, int n, int l);						// setup: (f.3.8)
	BOOL FIR_SetupFP(int nIL, int nIF, int nO1L, int nO1F);				// setup: FIR f.p. (f.3.8) (19.12.2002)
	BOOL FIRSE		(CVectorFloat&x, CVectorFloat&y);					// (f.3.9)
	BOOL FIRSE_Setup(CVectorFloat&h, int n, int l);						// setup: (f.3.9)
	BOOL FIRSE_SetupFP(int nIL, int nIF, int nO1L, int nO1F);			// setup: FIRSE f.p. (f.3.9) (19.12.2002)
	BOOL FIRSO		(CVectorFloat&x, CVectorFloat&y);					// (f.3.10)
	BOOL FIRSO_Setup(CVectorFloat&h, int n, int l);						// setup: (f.3.10)
	BOOL FIRSO_SetupFP(int nIL, int nIF, int nO1L, int nO1F);			// setup: FIRSO f.p. (f.3.10) (19.12.2002)
	BOOL RSMPL		(CVectorFloat&x, CVectorFloat&y);					// ReSample (f.3.11)
	BOOL RSMPL_Setup(int n, CFloat ratio);								// setup: (f.3.11)
	BOOL INTPOL		(CVectorFloat&x, CVectorFloat&y);					// Interpolation (f.3.12)
	int	 INTPOL_OutpVectLen	();											// Interpolation: returns output vector length (f.3.12)
	BOOL INTPOL_Setup(CVectorFloat&h, int n, int N, int l);				// setup: (f.3.12)
	BOOL INTPOL_SetupFP(int nIL, int nIF, int nO1L, int nO1F);			// setup: INTPOL f.p. (f.3.12) (18.12.2002)
	BOOL DECIM		(CVectorFloat&x, CVectorFloat&y);					// Decimation (f.3.13)
	int	 DECIM_OutpVectLen	();											// Decimation: returns output vector length (f.3.13)
	BOOL DECIM_Setup(CVectorFloat&h, int n, int L, int l);				// setup: (f.3.13)
	BOOL DECIM_SetupFP(int nIL, int nIF, int nO1L, int nO1F);			// setup: DECIM f.p. (f.3.13) (18.12.2002)
	BOOL RATAD		(CVectorFloat&x, CVectorFloat&y);					// RateAdapt (f.3.14)
	int	 RATAD_OutpVectLen	();											// RateAdapt: returns output vector length (f.3.14)
	BOOL RATAD_Setup(CVectorFloat&h, int n, int L, int N, int l);		// setup: (f.3.14)	
	BOOL RATAD_SetupFP(int nIL, int nIF, int nO1L, int nO1F);			// setup: RATAD f.p. (f.3.14) (18.12.2002)
	BOOL CWP		(CVectorFloat&x, CVectorFloat&y, CVectorFloat&cwp);	// float (f.3.17)
	BOOL CWP		(CVectorCmplx&x, CVectorCmplx&y, CVectorCmplx&cwp);	// complex (f.3.17)
	BOOL CWP		(CVectorFloat&xr, CVectorFloat&xi, CVectorFloat&yr, CVectorFloat&yi, CVectorFloat&cwpr, CVectorFloat&cwpi); // pseudo-complex (f.3.17)
	BOOL CWP_Setup	(int n1, int n2);									// setup: (f.3.17)
	BOOL CWP_SetupFP(int nIL, int nIF, int nO1L, int nO1F);				// setup: CWP fixed point (f.3.17)
	BOOL CWS		(CVectorFloat&x, CVectorFloat&y, CVectorFloat&cws);	// float (f.3.18)
	BOOL CWS		(CVectorCmplx&x, CVectorCmplx&y, CVectorCmplx&cws);	// complex (f.3.18)
	BOOL CWS		(CVectorFloat&xr, CVectorFloat&xi, CVectorFloat&yr, CVectorFloat&yi, CVectorFloat&cwsr, CVectorFloat&cwsi); // pseudo-complex (f.3.18)
	BOOL CWS_Setup	(int n1, int n2);									// setup: (f.3.18)
	BOOL CWS_SetupFP(int nIL, int nIF, int nO1L, int nO1F);				// setup: CWS f.p. (f.3.18) (19.12.2002)
	BOOL CWS2		(CVectorFloat&x, CFloat a, CVectorFloat&cws);		// adds a constant to all vector elemnts (08.11.2002)
	BOOL CWS2		(CVectorCmplx&x, CFloat a, CVectorCmplx&cws);		// adds a constant to all vector elemnts (08.11.2002)
	BOOL CWS2		(CVectorFloat&xr, CVectorFloat&xi, CFloat a, CVectorFloat&cwsr, CVectorFloat&cwsi); // pseudo-complex (28.11.2002)
	BOOL CWS2_Setup	(int n);											// setup: CWS2
	BOOL CWS2_SetupFP(int nIL, int nIF, int nO1L, int nO1F);			// setup: CWS2 f.p. (18.12.2002)
	BOOL CWD		(CVectorFloat&x, CVectorFloat&y, CVectorFloat&cwd);	// (f.3.19)
	BOOL CWD_Setup	(int n1, int n2);									// setup: (f.3.19)
	BOOL CWD_SetupFP(int nIL, int nIF, int nO1L, int nO1F);				// setup: CWD f.p. (f.3.19) (19.12.2002)
	BOOL CWD2		(CVectorFloat&x, CFloat a, CVectorFloat&cwd);		// CWD 2 (07.11.2002)
	BOOL CWD2_Setup	(int n);											// setup: CWD2
	BOOL CWD2_SetupFP(int nIL, int nIF, int nO1L, int nO1F);			// setup: CWD2 f.p. (19.12.2002)
	BOOL CWQ		(CVectorFloat&x, CVectorFloat&y, CVectorFloat&cwq);	// (f.3.20)
	BOOL CWQ_Setup	(int n1, int n2);									// setup: (f.3.20)
	BOOL CWSQR		(CVectorFloat&x, CVectorFloat&cwsqr);				// (f.3.21)
	BOOL CWSQR_Setup	(int n);										// setup: (f.3.21)
	BOOL CWSQR_SetupFP(int nIL, int nIF, int nO1L, int nO1F);			// setup: CWSQR f.p. (f.3.21) (19.12.2002)
	BOOL CWSC		(CVectorFloat&x, CFloat a, CVectorFloat&cwsc);		// (f.3.22)
	BOOL CWSC_Setup	(int n);											// setup: (f.3.22)
	BOOL CWSC_SetupFP(int nIL, int nIF, int nO1L, int nO1F);			// setup: CWSC f.p. (f.3.22) (19.12.2002)
	BOOL ABS		(CVectorFloat&x, CVectorFloat&y);					// (f.3.23)
	BOOL ABS_Setup	(int n);											// setup: (f.3.23)
	BOOL ABS_SetupFP(int nIL, int nIF, int nO1L, int nO1F);				// setup: ABS f.p. (f.3.23) (19.12.2002)
	BOOL SQRSUM		(CVectorFloat&x, CFloat& y);						// (f.3.24)
	BOOL SQRSUM_Setup	(int n);										// setup: (f.3.24)
	BOOL SQRSUM_SetupFP	(int nIL, int nIF, int nO1L, int nO1F);			// setup: SQRSUM f.p. (f.3.24) (19.12.2002)
	BOOL PHASE			(CVectorCmplx&x, CVectorInt&y);					// (f.3.25)
	BOOL PHASE			(CVectorFloat&xr, CVectorFloat&xi, CVectorInt&y);	// pseudo-complex (f.3.25)
	BOOL PHASE_Setup	(int n);										// setup: (f.3.25)
	BOOL PHASE_SetupFP	(int nIL, int nIF, int nO1L, int nO1F);			// setup: PHASE f.p. (f.3.25) (19.12.2002)
	BOOL CCPLX			(CVectorCmplx&x, CVectorCmplx&y);				// (f.3.26)
	BOOL CCPLX			(CVectorFloat&xr, CVectorFloat&xi, CVectorFloat&yr, CVectorFloat&yi);	// pseudo-complex version of CCPLX (f.3.26)
	BOOL CCPLX_Setup	(int n);										// setup: (f.3.26)
	BOOL VSUM			(CVectorFloat&x, CFloat& vsum);					// (f.3.27)
	BOOL VSUM_Setup		(int n);										// setup: (f.3.27)
	BOOL VSUM_SetupFP	(int nIL, int nIF, int nO1L, int nO1F);			// setup: VSUM f.p. (f.3.27) (19.12.2002)
	BOOL SWA			(CVectorFloat&x, CVectorFloat&y);				// (f.3.28)
	BOOL SWA_Setup		(int l, int n);									// setup: (f.3.28)
	BOOL SWA_SetupFP	(int nIL, int nIF, int nO1L, int nO1F);			// setup: SWA f.p. (f.3.28) (19.12.2002)
	BOOL SINGEN			(double f, double phi, CVectorCmplx&y);			// normalized by PI (f.3.37)
	BOOL SINGEN			(double f, double phi, CVectorFloat&yr, CVectorFloat&yi);	// pseudo-complex (f.3.37)
	BOOL SINGEN_Setup	(int n, int w);									// setup: (f.3.37)
	BOOL SINGEN_SetupFP (int nIL, int nIF, int nO1L, int nO1F);			// setup: SINGEN (f.3.37) (18.12.2002)
	// -------------------------------------------------------------------
	BOOL VMEAN			(CVectorFloat&x, CFloat& vmean);	// Vector Mean (07.11.2002)
	BOOL VMEAN_Setup	(int n);							// setup: Vector Mean (07.11.2002)
	BOOL VMEAN_SetupFP	(int nIL, int nIF, int nO1L, int nO1F);	// setup of fixed point: Vector Mean(17.12.2002)
	BOOL VSQRMEAN		(CVectorCmplx&x, CFloat& vsqmn);		// Vector Squared Mean (08.11.2002)
	BOOL VSQRMEAN		(CVectorFloat&xr, CVectorFloat&xi, CFloat& vsqmn); // pseudo complex (28.11.2002)
	BOOL VSQRMEAN_Setup	(int n);									// setup: Vector Squared Mean (08.11.2002)
	BOOL VSQRMEAN_SetupFP(int nIL, int nIF, int nO1L, int nO1F);	// setup: VSQRMEAN fixed point (18.12.2002)
	// -------------------------------------------------------------------
	BOOL Setup			(CFloat dSR);		// inits internal data of the class (08.11.2002)
	CSDRPrims();
	virtual ~CSDRPrims();
	// -------------------------------------------------------------------
private:
	CFloat	ReduceAngleRad(CFloat dAngle);	// reduces angle given in radians to fit in [-PI, +PI] range (08.11.2002)
	int		Rad2Deg(double dRad);			// converts value given in Radians into value in Degrees
	CFloat	max(CFloat dD1, CFloat dD2);	// returns MAX of arguments
static int	max(int nD1, int nD2);			// returns MAX of arguments
	CFloat	min(CFloat dD1, CFloat dD2);	// returns MIN of arguments
	int		min(int nD1, int nD2);			// returns MIN of arguments
	// -------------------------------------------------------------------
	// class setup
	// -------------------------------------------------------------------
	BOOL m_bInited;			// true, if class is inited (08.11.2002)
	CFloat m_dSR;			// sample rate (08.11.2002)
	// -------------------------------------------------------------------
	// Setup data for primitives (07.11.2002)
	// -------------------------------------------------------------------
	int m_nDOTP2_n1,		m_nDOTP2_n2;		// init data for: DOTP (f.3.2)
	int m_nDOTP2_FPIM[3],	m_nDOTP2_FPO1[3];	// init data for: DOTP (f.3.2)
	
	int m_nACFPNT_n,		m_nACFPNT_s;		// init data for: ACFPNT	(f.3.5)
	int m_nACFPNT_FPIM[3],	m_nACFPNT_FPO1[3];	// init data for: ACFPNT	(f.3.5)

	int m_nFIR_n,			m_nFIR_l;			// init data for: FIR (f.3.8)
	int m_nFIR_FPIM[3],		m_nFIR_FPO1[3];		// init data for: FIR (f.3.8)
	CVectorFloat m_pFIR_h;						// init data for: FIR (array) (f.3.8)

	int m_nFIRSE_n,			m_nFIRSE_l;			// init data for: FIRSE (f.3.9)
	int m_nFIRSE_FPIM[3],	m_nFIRSE_FPO1[3];	// init data for: FIR (f.3.8)
	CVectorFloat m_pFIRSE_h;					// init data for: FIRSE (array) (f.3.9)

	int m_nFIRSO_n,			m_nFIRSO_l;			// init data for: FIRSE (f.3.10)
	int m_nFIRSO_FPIM[3],	m_nFIRSO_FPO1[3];	// init data for: FIR (f.3.8)
	CVectorFloat m_pFIRSO_h;					// init data for: FIRSE (array) (f.3.10)

	int m_nRSMPL_n;								// init data for: RSMPL (f.3.11)
	int m_nRSMPL_FPIM[3],	m_nRSMPL_FPO1[3];	// init data for: RSMPL (f.3.11)
	CFloat m_nRSMPL_ratio;						// init data for: RSMPL (f.3.11)
	// -------------------------------------------------------------------
	int m_nINTPOL_n,	m_nINTPOL_l;	// init data for: INTPOL (f.3.12)
	int m_nINTPOL_N;					// init data for: INTPOL (f.3.12)
	int m_nINTPOL_FPIM[3],	m_nINTPOL_FPO1[3];// init data for INTPOL f.p. (18.12.2002)
	CVectorFloat m_pINTPOL_h;			// init data for: INTPOL (array) (f.3.12)
	// -------------------------------------------------------------------
	int m_nDECIM_n,	m_nDECIM_l;			// init data for: DECIM (f.3.13)
	int m_nDECIM_L;						// init data for: DECIM (f.3.13)
	int m_nDECIM_FPIM[3],	m_nDECIM_FPO1[3];	// init data for DECIM f.p. (18.12.2002)
	CVectorFloat m_pDECIM_h;			// init data for: DECIM (array) (f.3.13)
	// -------------------------------------------------------------------
	int m_nRATAD_n,		m_nRATAD_l;		// init data for: RATAD (f.3.14)
	int m_nRATAD_N,		m_nRATAD_L;		// init data for: RATAD (f.3.14)
	int m_nRATAD_FPIM[3],	m_nRATAD_FPO1[3];// init data for RATAD f.p. (18.12.2002)
	CVectorFloat m_pRATAD_h;			// init data for: RATAD (array) (f.3.14)
	// -------------------------------------------------------------------
	int m_nCWP_n1,		m_nCWP_n2;		// init data for: CWP (f.3.17)
	int m_nCWP_FPIM[3],	m_nCWP_FPO1[3];	// init data for: CWP f.p. (f.3.17)
	// -------------------------------------------------------------------
	int m_nCWS_n1,		m_nCWS_n2;		// init data for: CWS (f.3.18)
	int m_nCWS_FPIM[3],	m_nCWS_FPO1[3];	// init data for: CWS (f.3.18)

	int m_nCWP2_n;						// init data for: CWP with a constant (CWP2)
	int m_nCWS2_n;						// init data for: CWS2 (08.11.2002)
	int m_nCWS2_FPIM[3],	m_nCWS2_FPO1[3];	// init data for CWS2 f.p. (18.12.2002)

	int m_nCWD_n1,		m_nCWD_n2;		// init data for: CWD (f.3.19)
	int m_nCWD_FPIM[3],	m_nCWD_FPO1[3];	// init data for: CWS (f.3.18)
	// -------------------------------------------------------------------
	int m_nCWD2_n;						// init data for: CWD2 (07.11.2002)
	int m_nCWD2_FPIM[3],	m_nCWD2_FPO1[3];	// init data for: CWD with a constant fixed number (CWD2)
	// -------------------------------------------------------------------
	int m_nCWQ_n1,		m_nCWQ_n2;		// init data for: CWQ (f.3.20)
	int m_nCWQ_FPIM[3],	m_nCWQ_FPO1[3];	// init data for: CWS (f.3.18)
	// -------------------------------------------------------------------
	int m_nCWSQR_n;						// init data for: CWSQR (f.3.21)
	int m_nCWSQR_FPIM[3],	m_nCWSQR_FPO1[3];	// init data for: CWS (f.3.18)

	int m_nCWSC_n;						// init data for: CWSC (f.3.22)
	int m_nCWSC_FPIM[3],	m_nCWSC_FPO1[3];	// init data for: CWS (f.3.18)

	int m_nABS_n;						// init data for: ABS (f.3.23)
	int m_nABS_FPIM[3],		m_nABS_FPO1[3];	// init data for: CWS (f.3.18)

	int m_nSQRSUM_n;					// init data for: SQRSUM (f.3.24)
	int m_nSQRSUM_FPIM[3],	m_nSQRSUM_FPO1[3];	// init data for: CWS (f.3.18)

	int m_nPHASE_n;						// init data for: PHASE (f.3.25)
	int m_nPHASE_FPIM[3],	m_nPHASE_FPO1[3];	// init data for: CWS (f.3.18)

	int m_nCCPLX_n;						// init data for: CCPLX (f.3.26)
	int m_nCCPLX_FPIM[3],	m_nCCPLX_FPO1[3];	// init data for: CWS (f.3.18)

	int m_nVSUM_n;						// init data for: VSUM (f.3.27)
	int m_nVSUM_FPIM[3],	m_nVSUM_FPO1[3];	// init data for: CWS (f.3.18)

	int m_nSWA_l, m_nSWA_n;				// init data for: SWA (f.3.28)
	int m_nSWA_FPIM[3],		m_nSWA_FPO1[3];	// init data for: CWS (f.3.18)

	int m_nSINGEN_n, m_nSINGEN_w;		// init data for: SINGEN (f.3.37)
	int m_nSINGEN_FPIM[3],	m_nSINGEN_FPO1[3];
	// -------------------------------------------------------------------
	int m_nVMEAN_n;						// init data for: VMEAN (07.11.2002)
	int m_nVMEAN_FPIM[3],	m_nVMEAN_FPO1[3];	// init data for: VMEAN fixed point (17.12.2002)

	int m_nVSQRMEAN_n;					// init data for: VSQRMEAN (08.11.2002)
	int m_nVSQRMEAN_FPIM[3], m_nVSQRMEAN_FPO1[3];
	// -------------------------------------------------------------------
};
// =======================================================================
#endif // !defined(AFX_SDRPRIMS_H__5E9EE5B9_058F_4E8A_87CF_FF5D442CDF0E__INCLUDED_)
// =======================================================================
