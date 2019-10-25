// =======================================================================
// SDRTest ver. 1.0
// set of the test functions
// -----------------------------------------------------------------------
//       MD: 21.11.2002
//       LE: 21.11.2002
// -----------------------------------------------------------------------
// Compiler: MS VC 6.0
// =======================================================================
// SDRTest.cpp: implementation of the CSDRTest class.
// =======================================================================
#include "stdafx.h"
// -----------------------------------------------------------------------
#include <math.h>			// log, 14.11.2002
#include <string.h>			// strncmp (21.11.2002)
// -----------------------------------------------------------------------
#include "_DEBUG.H"			// 11.11.2002
#include "FilterCoeff.h"	// 12.11.2002
#include "SDRBlock.h"		// (21.11.2002)
#include "SDR80211a.h"		// (10.01.2003)
#include "VectConv.h"		// ConvVect... (09.01.2003)
// -----------------------------------------------------------------------
#include "SDRTest.h"
// =======================================================================
const double M_PI=3.1415926535897932384626433832795;
// =======================================================================
// Construction/Destruction
// =======================================================================
CSDRTest::CSDRTest()
{

}
// =======================================================================
CSDRTest::~CSDRTest()
{

}
// =======================================================================
// public functions
// =======================================================================
BOOL CSDRTest::Setup()
{
return(true);
}
// =======================================================================
BOOL CSDRTest::Test80211a()	{
// -----------------------------------------------------------------------
// Description: tests generating of a 802.11a signal (10.01.2003)
//   Parametrs: <none>
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 10.01.2003
//          LE: 10.01.2003
// -----------------------------------------------------------------------
printf("CSDRTest::Test80211a() - started: ");
// -----------------------------------------------------------------------
int i;
//int nRate=36;		// 36 Mbits/s
// -----------------------------------------------------------------------
CVectorFloat pSTr, pSTi;
CVectorFloat pSSTr, pSSTi;
CVectorFloat pLSTr, pLSTi;
// -----------------------------------------------------------------------
// Declarations
// -----------------------------------------------------------------------
CSDR80211a tT;
tT.CreateFieldSIGNALtd(36, 100, pSTr, pSTi);
tT.GenerateShortSequenceTD(pSSTr, pSSTi);
tT.GenerateLongSequenceTD(pLSTr, pLSTi);
// -----------------------------------------------------------------------
CVectorBool pD0, pD1, pD2, pD3, pWnd;
CVectorFloat pD4r[6], pD4i[6];
CVectorFloat pTr[6], pTi[6];
CVectorFloat pPolar(6);
// -----------------------------------------------------------------------
pPolar[0]=1;	pPolar[1]=1;	pPolar[2]=1;
pPolar[3]=-1;	pPolar[4]=-1;	pPolar[5]=-1;
// -----------------------------------------------------------------------
// test polarity (to calculate signal w/o pilots) (16.01.2003)
//pPolar[0]=0;	pPolar[1]=0;	pPolar[2]=0;
//pPolar[3]=0;	pPolar[4]=0;	pPolar[5]=0;
// -----------------------------------------------------------------------
pD0=tT.GetDummyData();
tT.DataScramble(pD0, pD1);
// -----------------------------------------------------------------------
for (i=816; i<822; i++) pD1[i]=0;	// (20.01.2003) 6 bits are zeroed
// -----------------------------------------------------------------------
tT.DateEncode(pD1, pD2, 36);
tT.DataIntleav(pD2, pD3, 36);
for (i=0; i<6; i++)
	{
	pWnd=CVectConv::GetWindow(pD3, 192, i);
	tT.DataConvToFD(pWnd, pD4r[i], pD4i[i], CSDR_MODUL16QAM, pPolar[i]);
	tT.Conv64FDToTD(pD4r[i], pD4i[i], pTr[i], pTi[i]);
	}
// -----------------------------------------------------------------------
// test 02
// -----------------------------------------------------------------------
CVectorFloat pPackR, pPackI;
tT.CreatePacket(36, 100, pD0, pPackR, pPackI);
int xx=pD2.size();
int yy=pD3.size();
// -----------------------------------------------------------------------
// debug section
// -----------------------------------------------------------------------
_DEBUG_TRACEVECT3("Data\\p802Data1scr.txt", pD1, pD1.size(), "%d\n", int);
_DEBUG_TRACEVECT3("Data\\p802Data2encp.txt", pD2, pD2.size(), "%d\n", int);
_DEBUG_TRACEVECT3("Data\\p802Data3il.txt", pD3, pD3.size(), "%d\n", int);
// -----------------------------------------------------------------------
// FD
// -----------------------------------------------------------------------
_DEBUG_TRACEVECT3("Data\\p802Data41re.txt", pD4r[0], pD4r[0].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data41im.txt", pD4i[0], pD4i[0].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data42re.txt", pD4r[1], pD4r[1].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data42im.txt", pD4i[1], pD4i[1].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data43re.txt", pD4r[2], pD4r[2].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data43im.txt", pD4i[2], pD4i[2].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data44re.txt", pD4r[3], pD4r[3].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data44im.txt", pD4i[3], pD4i[3].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data45re.txt", pD4r[4], pD4r[4].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data45im.txt", pD4i[4], pD4i[4].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data46re.txt", pD4r[5], pD4r[5].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data46im.txt", pD4i[5], pD4i[5].size(), "%9.3lf", double);
// -----------------------------------------------------------------------
// TD
// -----------------------------------------------------------------------
_DEBUG_TRACEVECT3("Data\\p802Data51re.txt", pTr[0], pTr[0].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data51im.txt", pTi[0], pTi[0].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data52re.txt", pTr[1], pTr[1].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data52im.txt", pTi[1], pTi[1].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data53re.txt", pTr[2], pTr[2].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data53im.txt", pTi[2], pTi[2].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data54re.txt", pTr[3], pTr[3].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data54im.txt", pTi[3], pTi[3].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data55re.txt", pTr[4], pTr[4].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data55im.txt", pTi[4], pTi[4].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data56re.txt", pTr[5], pTr[5].size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802Data56im.txt", pTi[5], pTi[5].size(), "%9.3lf", double);
// -----------------------------------------------------------------------
// test 02
// -----------------------------------------------------------------------
_DEBUG_TRACEVECT4("Data\\p802ChainR.txt", pPackR, pPackR.size(), "%9.3lf", double, 80);
_DEBUG_TRACEVECT4("Data\\p802ChainI.txt", pPackI, pPackI.size(), "%9.3lf", double, 80);
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CSDRTest::TestChain()
{
// -----------------------------------------------------------------------
// Description: tests all Signal Processing Chains (11.11.2002)
//   Parametrs: <none>
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 11.11.2002
//          LE: 28.11.2002, 18.12.2002
// -----------------------------------------------------------------------
printf("CSDRTest::TestChain() - started: ");
// -----------------------------------------------------------------------
// Declarations
// -----------------------------------------------------------------------
int n;
CFloat dSR;			// sampling rate
// -----------------------------------------------------------------------
CFloat phi;			// phase
CFloat dDCC;		// DC constant to remove (noise)
CFloat dFS, dPS;	// frequency shift & phase shift
CFloat dR0, dR1, dStep;
// -----------------------------------------------------------------------
// Values to calculate (zu berechnende Werte)
// -----------------------------------------------------------------------
CFloat dSignPow;		// signal power
// -----------------------------------------------------------------------
#ifdef SDRPDEMO_USEFIX
phi.Setup	(12, 8);
dDCC.Setup	(12, 8);
dFS.Setup	(12, 8);
dPS.Setup	(12, 8);
dSR.Setup	(12, 8);
dR0.Setup	(12, 8);
dR1.Setup	(12, 8);
dStep.Setup	(12, 8);
dSignPow.Setup(12, 8);
#endif
// -----------------------------------------------------------------------
phi=0.00;		// phase
dDCC=1.5;		// DC constant to remove (noise)
dFS=0.02;		// frequency shift
dPS=0;			// no phase shift
dSR=1;			// sampling rate
// -----------------------------------------------------------------------
CVectorFloat h;
int l;
// -----------------------------------------------------------------------
CSDRBlock tB;			// blocks
CSDRPrims tP;			// primitive
// -----------------------------------------------------------------------
tB.Setup(dSR);			// setups blocks	(12.11.2002)
tP.Setup(dSR);			// setups class CSDRPrims with the sample rate
// -----------------------------------------------------------------------
// fixed point setup (17.12.2002)
// -----------------------------------------------------------------------
tB.TestGenerateSpectrum_SetupFP	(-1, -1, 24,10, 12, 6);	// 18.12.2002
tB.DCOffRem_SetupFP				(-1, -1, 24,10, 12, 6);	// FP: 17.12.2002
tB.FreqPhaseCorr_SetupFP		(-1, -1, 30, 7, 12, 6);	// FP: 17.12.2002
tB.SigPowInd_SetupFP			(-1, -1, 28, 8, 12, 6);	// FP: 18.12.2002
tB.SampRateConv_SetupFP			(-1, -1, 16, 5, 12, 6);
// --------------------------------------------------------------
CVectConv::SetupFixPointInVector		(h, 24, 12);			// Int.m.
tP.CWS2_SetupFP					(14, 6, 12, 6);
// -----------------------------------------------------------------------
int nSizeS3;			// length of the vector stream 3 (after RATAD)
// -----------------------------------------------------------------------
// Test values (11.11.2002)
// -----------------------------------------------------------------------
n=512;				// number of stadard input values
// -----------------------------------------------------------------------
// Test values ... Filter coefficients
// -----------------------------------------------------------------------
h=GetFilterLP25();		// test
l=h.size();
// -----------------------------------------------------------------------
CVectorFloat tSI(n);	// re. part of the complex signal
CVectorFloat tSQ(n);	// im. part of the complex signal
// -----------------------------------------------------------------------
// data streams
// -----------------------------------------------------------------------
CVectorFloat tSI0(n), tSI1(n), tSI2(n), tSI3;	// real
CVectorFloat tSQ0(n), tSQ1(n), tSQ2(n), tSQ3;	// im
// -----------------------------------------------------------------------
// setup section
// -----------------------------------------------------------------------
tP.CWS2_Setup(n);		// setups CWS2
// -----------------------------------------------------------------------
tB.DCOffRem_Setup(n);		// setups DCOffRem
tB.SigPowInd_Setup(n);		// signal power indication
tB.FreqPhaseCorr_Setup(n);	// freq-phase correction
tB.SampRateConv_Setup(h, n, l, 2, 1);	// rample rate adaptation
// -----------------------------------------------------------------------
// source signal generation section
// -----------------------------------------------------------------------
dR0=0.10;	dR1=0.30;	dStep=0.1;
dR0=dR0+dFS;dR1=dR1+dFS;
tB.TestGenerateSpectrum(dR0, dR1, dStep, n, tSI, tSQ);	// generates mix of 3 sin signals (28.11.2002)
tP.CWS2(tSI, dDCC, tSI0);	// adds a constant to all elements of the vector
tP.CWS2(tSQ, dDCC, tSQ0);	// adds a constant to all elements of the vector
// -----------------------------------------------------------------------
// Process chain
// -----------------------------------------------------------------------
tB.DCOffRem(tSI0, tSI1);				// removes DC component
tB.DCOffRem(tSQ0, tSQ1);				// removes DC component
tB.SigPowInd(tSI1, tSQ1, dSignPow);		// calculates signal power
tB.FreqPhaseCorr(tSI1, tSQ1, -dFS, -dPS, tSI2, tSQ2);
tB.SampRateConvRATAD(tSI2,tSI3,nSizeS3);	// sample rate convertion
tB.SampRateConvRATAD(tSQ2,tSQ3,nSizeS3);	// sample rate convertion
// -----------------------------------------------------------------------
// Output
// -----------------------------------------------------------------------
printf ("Signal power = %9.6e\n", (double)dSignPow);
_DEBUG_TRACEVECT3("Data\\tSI0.txt", tSI0, tSI0.size(), "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSQ0.txt", tSQ0, tSQ0.size(), "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSI1.txt", tSI1, tSI1.size(), "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSQ1.txt", tSQ1, tSQ1.size(), "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSI2.txt", tSI2, tSI2.size(), "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSQ2.txt", tSQ2, tSQ2.size(), "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSI3.txt", tSI3, tSI3.size(), "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSQ3.txt", tSQ3, tSQ3.size(), "%9.6e", double);
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CSDRTest::TestDCOffRem()
{
// -----------------------------------------------------------------------
// Description: checks DC offset removal function (07.11.2002)
//				following situation:
//				There is an interferenced sinus signal at the input of 
//				DCOffRem function
//				There is "clear" sinus signal at the output of the function
//   Parametrs: <none>
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 07.11.2002
//          LE: 28.11.2002, 20.12.2002
// -----------------------------------------------------------------------
printf("CSDRTest::TestDCOffRem() - started: ");
// -----------------------------------------------------------------------
// Test values (08.11.2002)
// -----------------------------------------------------------------------
int n=64;				// 64 values
CFloat f;				// freq in Hz
CFloat phi;				// phase
CFloat dConst;			// constant to remove
CFloat dSR;				// sample rate
// -----------------------------------------------------------------------
#ifdef SDRPDEMO_USEFIX
f.Setup(12, 8);
phi.Setup(12, 8);
dSR.Setup(12, 8);
dConst.Setup(12, 8);
#endif
// -----------------------------------------------------------------------
f=0.30;			// freq in Hz
phi=0.00;		// phase
dConst=5;		// constant to remove
dSR=7;			// sample rate
// -----------------------------------------------------------------------
// Values to calculate (zu berechnende Werte)
// -----------------------------------------------------------------------
CSDRBlock tB;			// blocks
CSDRPrims tP;			// primitive
CVectorFloat tSin1(n);	// sinus signal
CVectorFloat tSin2(n);	// sinus signal (distorted)
CVectorFloat tSin3(n);	// coreccted sinus signal
CVectorFloat tXXX(n);	// not used, but it's need for convertion function
// -----------------------------------------------------------------------
// setup section
// -----------------------------------------------------------------------
tB.Setup(dSR);			// setups blocks	(12.11.2002)
tP.Setup(dSR);			// setups class CSDRPrims
tP.SINGEN_Setup(n, 1);	// '1' - dummy-number, really - capacity in bits
tP.CWS2_Setup(n);		// setups CWS2
tB.DCOffRem_Setup(n);	// setups DCOffRem
// -----------------------------------------------------------------------
// f.p. setup (18.12.2002)
// -----------------------------------------------------------------------
tP.SINGEN_SetupFP	(32, 12, 12, 6);
tP.CWS2_SetupFP		(14,  6, 12, 6);
tB.DCOffRem_SetupFP (12,  6, 18, 6, 12, 6);
CVectConv::SetupFixPointInVector(tSin2, 12, 6);
// -----------------------------------------------------------------------
// source signal generation section
// -----------------------------------------------------------------------
tP.SINGEN(f, phi, tXXX, tSin1);	// gets float sinus (28.11.2002)
tSin2=tSin1;					// gets copy of float sinus
tP.CWS2(tSin1, dConst, tSin2);	// adds a constant to all elements of the vector
// -----------------------------------------------------------------------
// Process chain
// -----------------------------------------------------------------------
tB.DCOffRem(tSin2, tSin3);			// removes DC component
// -----------------------------------------------------------------------
// Output
// -----------------------------------------------------------------------
_DEBUG_TRACEVECT3("Data\\tDCORSI1.txt", tSin1, tSin1.size(), "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tDCORSI2.txt", tSin2, tSin2.size(), "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tDCORSO1.txt", tSin3, tSin3.size(), "%9.6e", double);
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CSDRTest::TestFreqPhaseCorr()
{
// -----------------------------------------------------------------------
// Description: tests Freq&Phase correction Chain
//   Parametrs: <none>
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 11.11.2002
//          LE: 28.11.2002, 20.12.2002
// -----------------------------------------------------------------------
printf("CSDRTest::TestFreqPhaseCorr() - started: ");
// -----------------------------------------------------------------------
// Test values (11.11.2002)
// -----------------------------------------------------------------------
int n=500;				// number of stadard input values
CFloat f;				// freq (normalized by PI)
CFloat f_shift;			// freq shift (normalized by PI)
CFloat phi;				// phase
CFloat phi_shift;		// phase shift
CFloat dSR;				// sampling rate
// -----------------------------------------------------------------------
// (20.12.2002)
#ifdef SDRPDEMO_USEFIX
f.Setup			(12, 8);
f_shift.Setup	(12, 8);
phi.Setup		(12, 8);
phi_shift.Setup	(12, 8);
dSR.Setup		(12, 8);
#endif
// -----------------------------------------------------------------------
f=0.5;			// freq (normalized by PI)
f_shift=0.05;	// freq shift (normalized by PI)
phi=0.00;		// phase
phi_shift=0.3;	// phase shift
dSR=5;			// sample rate
// -----------------------------------------------------------------------
// Values to calculate (zu berechnende Werte)
// -----------------------------------------------------------------------
CSDRBlock tB;			// blocks
CSDRPrims tP;			// primitive
CVectorFloat tSin1(n);	// sinus signal
CVectorFloat tCos1(n);	// cosine signal
CVectorFloat tSin2(n);	// sinus signal (with frequency shift)
CVectorFloat tCos2(n);	// cosine signal (with frequency shift)
CVectorFloat tSin3(n);	// corected sinus signal (w/o freq. shift)
CVectorFloat tCos3(n);	// corected cosine signal (w/o freq. shift)
// -----------------------------------------------------------------------
// setup section
// -----------------------------------------------------------------------
tB.Setup(dSR);			// setups blocks	(12.11.2002)
tP.Setup(dSR);			// setups class CSDRPrims with the sample rate
tP.SINGEN_Setup(n, 1);	// '1' - dummy-number, really - capacity in bits
// -----------------------------------------------------------------------
tB.FreqPhaseCorr_Setup(n);	//
// -----------------------------------------------------------------------
// F.P. setup (18.12.2002)
// -----------------------------------------------------------------------
tP.SINGEN_SetupFP	(32, 6, 12, 6);
tB.FreqPhaseCorr_SetupFP(12, 6, 16, 6, 12, 6);
// -----------------------------------------------------------------------
// source signal generation section
// -----------------------------------------------------------------------
tP.SINGEN(f, phi, tCos1, tSin1);					// generates sinus (28.11.2002)
tP.SINGEN(f+f_shift, phi+phi_shift, tCos2, tSin2);	// generates shifted sinus (28.11.2002)
// -----------------------------------------------------------------------
// Process chain
// -----------------------------------------------------------------------
tB.FreqPhaseCorr(tSin2, tCos2, f_shift, phi_shift, tSin3, tCos3);
// -----------------------------------------------------------------------
// Output
// -----------------------------------------------------------------------
_DEBUG_TRACEVECT3("Data\\tFPCSin1.txt", tSin1, n, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tFPCSin2.txt", tSin2, n, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tFPCSin3.txt", tSin3, n, "%9.6e", double);
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CSDRTest::TestRef()
{
// -----------------------------------------------------------------------
// Description: compares results of the RATAD block with referenced data
//   Parametrs: <none>
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 21.11.2002
//          LE: 18.12.2002
// -----------------------------------------------------------------------
printf("CSDRTest::TestRef() - started: ");
// -----------------------------------------------------------------------
int n;					// number of stadard input values
int m;					// size of the output vector
CFloat phi;				// phase
CFloat dSR;				// sample rate
// -----------------------------------------------------------------------
int nFI, nFD;			// interpolation & decimations factors 
// -----------------------------------------------------------------------
CVectorFloat h;			// Filter coefficients
int l;					// filter order+1 (number of coefficients)
// -----------------------------------------------------------------------
h=FilterLoadFromFile("Inbound\\FilterCoeff");
l=h.size();
// -----------------------------------------------------------------------
CSDRBlock tB;		// blocks
CVectorFloat tSI1i;	// input signal
CVectorFloat tSO1i;	// output signal
CVectorFloat tSOxi;	// referenced output signal
// -----------------------------------------------------------------------
// (06.01.2003)
#ifdef SDRPDEMO_USEFIX
phi.Setup		(12, 8);
dSR.Setup		(12, 8);
#endif
// -----------------------------------------------------------------------
phi=0.10;		// phase
dSR=2;			// sample rate
nFI=2;
nFD=1;
tSI1i=DataILoadFromFile("Inbound\\ReferenceData");
tSOxi=DataOLoadFromFile("Inbound\\OutputData", nFD, nFI, 6, 4);
n=tSI1i.size();
// -----------------------------------------------------------------------
// Process chain
// -----------------------------------------------------------------------
tB.Setup(dSR);			// setups blocks	(12.11.2002)
tB.SampRateConv_Setup(h, n, l, nFI, nFD);
tB.SampRateConv_SetupFP(12, 6, 20, 6, 12, 6);	// (18.12.2002)
// -----------------------------------------------------------------------
// Process chain
// -----------------------------------------------------------------------
tB.SampRateConvRATAD(tSI1i, tSO1i, m);
// -----------------------------------------------------------------------
// Output
// -----------------------------------------------------------------------
_DEBUG_TRACEVECT3("Data\\tSRI1i.txt", tSI1i, tSI1i.size(), "%9.4e", double);
_DEBUG_TRACEVECT3("Data\\tSRO1i.txt", tSO1i, tSO1i.size(), "%9.4e", double);
_DEBUG_TRACEVECT3("Data\\tSROxi.txt", tSOxi, tSOxi.size(), "%9.4e", double);
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CSDRTest::TestSRCFIR()
{
// -----------------------------------------------------------------------
// Description: tests Sampling Rate Conversion chain - FIR (step 1)
//   Parametrs: <none>
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 11.11.2002
//          LE: 20.11.2002
// -----------------------------------------------------------------------
printf("CSDRTest::TestSCRFIR() - started: ");
// -----------------------------------------------------------------------
// Test values (11.11.2002)
// -----------------------------------------------------------------------
int n=1024;				// number of stadard input values
int m;					// size of the output vector
CFloat dSR;				// sample rate
CFloat dR0, dR1, dStep;	// Test Generate Spectrum
// -----------------------------------------------------------------------
CVectorFloat h;			// Filter coefficients
int l;					// filter order+1 (number of coefficients)
// -----------------------------------------------------------------------
// (20.12.2002)
#ifdef SDRPDEMO_USEFIX
dSR.Setup		(12, 8);
dR0.Setup		(12, 8);
dR1.Setup		(12, 8);
dStep.Setup		(12, 8);
#endif
// -----------------------------------------------------------------------
dSR=2;					// sample rate
dR0=0.10;
dR1=0.40;
dStep=0.1;
// -----------------------------------------------------------------------
// Test values ... Filter coefficients
// -----------------------------------------------------------------------
h=GetFilterBP2030();
//h=GetFilterBS2030();
//h=GetFilterHP20();
//h=GetFilterLP25();
l=h.size();
// -----------------------------------------------------------------------
// Values to calculate (zu berechnende Werte)
// -----------------------------------------------------------------------
CSDRBlock tB;			// blocks
CSDRPrims tP;			// primitive
CVectorFloat tCos1(n), tSin1(n);	// sinus signal  (freq1)	// re, im
CVectorFloat tCos2(n), tSin2(n);	// sinus signal  (freq1)	// re ,im
CVectorFloat tSIR1(n), tSII1(n);	// input signal				// re, im
CVectorFloat tSOR1, tSOI1;			// output signal			// re, im
// -----------------------------------------------------------------------
// setup section
// -----------------------------------------------------------------------
tB.Setup(dSR);			// setups blocks	(12.11.2002)
tP.Setup(dSR);			// setups class CSDRPrims with the sample rate
tB.SampRateConv_Setup(h, n, l, 1, 1);
// -----------------------------------------------------------------------
tB.TestGenerateSpectrum_SetupFP	(12, 6, 22, 8, 12, 6);	// 18.12.2002
tB.SampRateConv_SetupFP			(12, 6, 12, 6, 12, 6);
// -----------------------------------------------------------------------
// source signal generation section
// -----------------------------------------------------------------------
tB.TestGenerateSpectrum			(dR0, dR1, dStep, n, tSIR1, tSII1);
// -----------------------------------------------------------------------
// Process chain
// -----------------------------------------------------------------------
tB.SampRateConvFIR(tSIR1, tSOR1, m);
tB.SampRateConvFIR(tSII1, tSOI1, m);
// -----------------------------------------------------------------------
// Output
// -----------------------------------------------------------------------
_DEBUG_TRACEVECT3("Data\\tSRCSI1r.txt", tSIR1, tSIR1.size(), "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRCSI1i.txt", tSII1, tSII1.size(), "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRCSO1r.txt", tSOR1, tSOR1.size(), "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRCSO1i.txt", tSOI1, tSOI1.size(), "%9.6e", double);
// -----------------------------------------------------------------------
// Test !!!
// -----------------------------------------------------------------------
/*
CVectorFloat h2=GetFilterBS1020();	SampRateConv_Setup(h2, n, h2.size());
CVectorFloat tSOI2;					SampRateConv(tSOI1, tSOI2, m);
_DEBUG_TRACEVECT2("Data\\tSRCSO1i.txt", tSOI2, tSOI2.size(), "%9.6e");//*/
/*
CFloat dPow;
SigPowInd_Setup(n);
SigPowInd(tSOR1, tSOI1, dPow);
printf("power = %g\n", dPow);//*/
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CSDRTest::TestSRCIP2DE()
{
// -----------------------------------------------------------------------
// Description: tests Sampling Rate Conversion chain in 
//				"decimate and then interpolate" mode and in
//				"interpolate and then decimate" mode
//   Parametrs: <none>
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 18.11.2002
//          LE: 28.11.2002
// -----------------------------------------------------------------------
printf("CSDRTest::TestIP2DE() - started: ");
// -----------------------------------------------------------------------
// Test values (11.11.2002)
// -----------------------------------------------------------------------
double f1, f2;			// freq (normalized by 2*PI)
int nFact=2;			// INTPOL and DECIM factor (19.11.2002)
int n=1024;				// number of stadard input values
int m;					// size of the output vector
CFloat phi;				// phase
CFloat dSR;				// sample rate
// -----------------------------------------------------------------------
CVectorFloat h;			// Filter coefficients
int l;					// filter order+1 (number of coefficients)
// -----------------------------------------------------------------------
// (20.12.2002)
#ifdef SDRPDEMO_USEFIX
phi.Setup	(12, 8);
dSR.Setup	(12, 8);
#endif
// -----------------------------------------------------------------------
phi=0.10;		// phase
dSR=2;			// sample rate
f1=0.05;
f2=0.30;		// freq (normalized by 2*PI)
// -----------------------------------------------------------------------
// Test values ... Filter coefficients
// -----------------------------------------------------------------------
//h=GetFilterLP10();	// INTPOL x 4
//h=GetFilterLP15();	// INTPOL x 3
//h=GetFilterLP25X();	// INTPOL x 2
h=GetFilterLP30();		// pass the whole spectrum
//h=GetFilterLPSuper();	// pass the whole spectrum
l=h.size();
// -----------------------------------------------------------------------
// Values to calculate (zu berechnende Werte)
// -----------------------------------------------------------------------
CSDRBlock tB;			// blocks
CSDRPrims tP;			// primitive
CVectorFloat tSIR1(n), tSII1(n);	// input signal		// re, im
CVectorFloat tSOR1, tSOI1;			// output signal	// re, im	- INTPOL
CVectorFloat tSOR2, tSOI2;			// output signal	// re, im	- DECIM
CVectorFloat tSOR3, tSOI3;			// output signal	// re, im	- DECIM
CVectorFloat tSOR4, tSOI4;			// output signal	// re, im	- INTPOL
// -----------------------------------------------------------------------
// setup section
// -----------------------------------------------------------------------
tB.Setup(dSR);			// setups blocks	(12.11.2002)
tP.Setup(dSR);			// setups class CSDRPrims with the sample rate
// -----------------------------------------------------------------------
tB.SampRateConv_SetupFP			(12, 6, 32, 6, 12, 6);
tB.TestGenerateSpectrum_SetupFP	(12, 6, 32, 6, 12, 6);	// 18.12.2002
// -----------------------------------------------------------------------
// normalizes input frequencies
// -----------------------------------------------------------------------
f1*=(double)dSR;
f2*=(double)dSR;
// -----------------------------------------------------------------------
// source signal generation section
// -----------------------------------------------------------------------
tB.TestGenerateSpectrum(f1, f2, f2-f1, n, tSIR1, tSII1);	// (28.11.2002)
// -----------------------------------------------------------------------
// Process chain
// -----------------------------------------------------------------------
// INTPOL and then DECIM
tB.SampRateConv_Setup(h, n, l, nFact, 1);
tB.SampRateConvIP(tSIR1, tSOR1, m);	// INTPOL
tB.SampRateConvIP(tSII1, tSOI1, m);
tB.SampRateConv_Setup(h, m, l, 1, nFact);
tB.SampRateConvDE(tSOR1, tSOR2, m);	// DECIM
tB.SampRateConvDE(tSOI1, tSOI2, m);
// -----------------------------------------------------------------------
// DECIM and then INTPOL
tB.SampRateConv_Setup(h, n, l, 1, nFact);
tB.SampRateConvDE(tSIR1, tSOR3, m);	// DECIM
tB.SampRateConvDE(tSII1, tSOI3, m);
tB.SampRateConv_Setup(h, m, l, nFact, 1);	// interpolates with factor nFact
tB.SampRateConvIP(tSOR3, tSOR4, m);	// INTPOL
tB.SampRateConvIP(tSOI3, tSOI4, m);
// -----------------------------------------------------------------------
// Output
// -----------------------------------------------------------------------
int li1=tSIR1.size();
int lo1=SizePow2(tSOR1.size());
int lo2=SizePow2(tSOR2.size());
int lo3=SizePow2(tSOR3.size());
int lo4=SizePow2(tSOR4.size());
// -----------------------------------------------------------------------
_DEBUG_TRACEVECT3("Data\\tSRC4SI1r.txt", tSIR1, li1, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC4SI1i.txt", tSII1, li1, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC4SO1r.txt", tSOR1, lo1, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC4SO1i.txt", tSOI1, lo1, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC4SO2r.txt", tSOR2, lo2, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC4SO2i.txt", tSOI2, lo2, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC4SO3r.txt", tSOR3, lo3, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC4SO3i.txt", tSOI3, lo3, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC4SO4r.txt", tSOR4, lo4, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC4SO4i.txt", tSOI4, lo4, "%9.6e", double);
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CSDRTest::TestSRCIPandDE()
{
// -----------------------------------------------------------------------
// Description: tests Sampling Rate Conversion chain - INTPOL, DECIM (step 2)
//   Parametrs: <none>
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 11.11.2002
//          LE: 28.11.2002
// -----------------------------------------------------------------------
printf("CSDRTest::TestIPandDE() - started: ");
// -----------------------------------------------------------------------
// Test values (11.11.2002)
// -----------------------------------------------------------------------
double f1, f2;			// freq (normalized by 2*PI)
int n=512;				// number of stadard input values
int m;					// size of the output vector
CFloat phi;				// phase
CFloat dSR;				// sample rate
// -----------------------------------------------------------------------
CVectorFloat h;			// Filter coefficients
int l;					// filter order+1 (number of coefficients)
// -----------------------------------------------------------------------
// (20.12.2002)
#ifdef SDRPDEMO_USEFIX
phi.Setup		(12, 8);
dSR.Setup		(12, 8);
#endif
// -----------------------------------------------------------------------
f1=0.05;	f2=0.40;	// 2 freqs
phi=0.10;				// phase
dSR=2;					// sample rate
// -----------------------------------------------------------------------
// Test values ... Filter coefficients
// -----------------------------------------------------------------------
//h=GetFilterLP10();	// INTPOL x 4
h=GetFilterLP25();	// INTPOL x 3
//h=GetFilterLP25X();	// INTPOL x 2
//h=GetFilterLPSuper();	// pass the whole spectrum
l=h.size();
// -----------------------------------------------------------------------
// Values to calculate (zu berechnende Werte)
// -----------------------------------------------------------------------
CSDRBlock tB;
CSDRPrims tP;			// primitive
CVectorFloat tSIR1(n), tSII1(n);	// input signal		// re, im
CVectorFloat tSOR1, tSOI1;			// output signal	// re, im	- INTPOL
CVectorFloat tSOR2, tSOI2;			// output signal	// re, im	- DECIM
// -----------------------------------------------------------------------
// setup section
// -----------------------------------------------------------------------
tB.Setup(dSR);			// setups blocks	(12.11.2002)
tP.Setup(dSR);			// setups class CSDRPrims with the sample rate
// -----------------------------------------------------------------------
tB.SampRateConv_Setup(h, n, l, 2, 2);
// -----------------------------------------------------------------------
#ifdef SDRPDEMO_USEFIX
//f1.Setup(24, 10);
//f2.Setup(24, 10);
#endif
// -----------------------------------------------------------------------
tB.SampRateConv_SetupFP			(12, 6, 32, 6, 12, 6);
tB.TestGenerateSpectrum_SetupFP	(12, 6, 32, 6, 12, 6);	// 18.12.2002
// -----------------------------------------------------------------------
// normalizes input frequencies
// -----------------------------------------------------------------------
f1=f1*(double)dSR;	f2=f2*(double)dSR;//*/
// -----------------------------------------------------------------------
// source signal generation section
// -----------------------------------------------------------------------
tB.TestGenerateSpectrum(f1, f2, f2-f1, n, tSIR1, tSII1);	// (28.11.2002)
// -----------------------------------------------------------------------
// Process chain
// -----------------------------------------------------------------------
tB.SampRateConvDE(tSIR1, tSOR2, m);	// DECIM
tB.SampRateConvDE(tSII1, tSOI2, m);
tB.SampRateConvIP(tSIR1, tSOR1, m);	// INTPOL
tB.SampRateConvIP(tSII1, tSOI1, m);
// -----------------------------------------------------------------------
// Output
// -----------------------------------------------------------------------
int li1=tSIR1.size();
int lo1=SizePow2(tSOR1.size());
int lo2=SizePow2(tSOR2.size());
//int lo1=tSOR1.size();
//int lo2=tSOR2.size();
// -----------------------------------------------------------------------
_DEBUG_TRACEVECT3("Data\\tSRC2SI1r.txt", tSIR1, li1, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC2SI1i.txt", tSII1, li1, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC2SO1r.txt", tSOR1, lo1, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC2SO1i.txt", tSOI1, lo1, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC2SO2r.txt", tSOR2, lo2, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC2SO2i.txt", tSOI2, lo2, "%9.6e", double);
// -----------------------------------------------------------------------
printf("ok\n");
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CSDRTest::TestSRCRATAD()
{
// -----------------------------------------------------------------------
// Description: tests Sampling Rate Conversion chain - RATAD (step 2)
//   Parametrs: <none>
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 11.11.2002
//          LE: 18.11.2002
// -----------------------------------------------------------------------
printf("CSDRTest::TestSRCRATAD() - started: ");
// -----------------------------------------------------------------------
// Test values (11.11.2002)
// -----------------------------------------------------------------------
double f1, f2;			// 2 freqs
int n=1024;				// number of stadard input values
int m;					// size of the output vector
CFloat phi;				// phase
CFloat dSR;				// sample rate
CFloat dR0, dR1, dStep;	// 
// -----------------------------------------------------------------------
CVectorFloat h;			// Filter coefficients
int l;					// filter order+1 (number of coefficients)
// -----------------------------------------------------------------------
// (20.12.2002)
#ifdef SDRPDEMO_USEFIX
phi.Setup		(12, 8);
dSR.Setup		(12, 8);
dR0.Setup		(12, 8);
dR1.Setup		(12, 8);
dStep.Setup		(12, 8);
#endif
// -----------------------------------------------------------------------
f1=0.05;	f2=0.35;	// 2 freqs
phi=0.10;				// phase
dSR=2;					// sample rate
dR0=0.01;
dR1=0.10;
dStep=0.01;
// -----------------------------------------------------------------------
// Test values ... Filter coefficients
// -----------------------------------------------------------------------
//h=GetFilterLP05();	// INTPOL x 4
//h=GetFilterLP15();	// INTPOL x 3
//h=GetFilterLP25X();	// INTPOL x 2
//h=GetFilterLP10();		// ... test ... (for 5,5)
h=GetFilterLP25();		// ... test ...
//h=GetFilterLP40();	// ... test ...
//h=GetFilterLPSuper();	// pass the whole spectrum
l=h.size();
// -----------------------------------------------------------------------
// Values to calculate (zu berechnende Werte)
// -----------------------------------------------------------------------
CSDRBlock tB;			// blocks
CSDRPrims tP;			// primitive
CVectorFloat tSIR1(n), tSII1(n);	// input signal		// re, im
CVectorFloat tSOR1, tSOI1;			// output signal	// re, im	- RATAD
CVectorFloat tSOR2, tSOI2;			// test output signal (18.11.2002)
// -----------------------------------------------------------------------
// setup section
// -----------------------------------------------------------------------
tB.Setup(dSR);			// setups blocks	(12.11.2002)
tP.Setup(dSR);			// setups class CSDRPrims with the sample rate
// -----------------------------------------------------------------------
//tB.SampRateConv_Setup(h, n, l, 5, 5);
tB.SampRateConv_Setup(h, n, l, 2, 2);
tB.SampRateConv_SetupFP			(12, 6, 32,10, 12, 6);
tB.TestGenerateSpectrum_SetupFP	(12, 6, 32,10, 12, 6);	// 18.12.2002
// -----------------------------------------------------------------------
// normalizes input frequencies
// -----------------------------------------------------------------------
f1=f1*(double)dSR;	f2=f2*(double)dSR;
// -----------------------------------------------------------------------
// source signal generation section
// -----------------------------------------------------------------------
//tB.TestGenerateSpectrum(0.01, 0.10, 0.001, n, tSIR1, tSII1);
tB.TestGenerateSpectrum(dR0, dR1, dStep, n, tSIR1, tSII1);
// -----------------------------------------------------------------------
// Process chain
// -----------------------------------------------------------------------
tB.SampRateConvRATAD(tSIR1, tSOR1, m);
tB.SampRateConvRATAD(tSII1, tSOI1, m);
// -----------------------------------------------------------------------
// ... test ... (used in TestSampRatConvRATAD2.mcd) (18.11.2002)
/*
SampRateConv_Setup(h, m, l);
Setup(dSR, 2, 1);		// setups blocks	(12.11.2002)
SampRateConvIP(tSOR1, tSOR2, m);
SampRateConvIP(tSOI1, tSOI2, m);//*/
// -----------------------------------------------------------------------
// Output
// -----------------------------------------------------------------------
int li1=tSIR1.size();
int lo1=tSOR1.size();
int lo2=tSOR2.size();
// -----------------------------------------------------------------------
_DEBUG_TRACEVECT3("Data\\tSRC3SI1r.txt", tSIR1, li1, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC3SI1i.txt", tSII1, li1, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC3SO1r.txt", tSOR1, lo1, "%9.6e", double);
_DEBUG_TRACEVECT3("Data\\tSRC3SO1i.txt", tSOI1, lo1, "%9.6e", double);
//_DEBUG_TRACEVECT3("Data\\tSRC3SO2r.txt", tSOR2, lo2, "%9.6e", double);
//_DEBUG_TRACEVECT3("Data\\tSRC3SO2i.txt", tSOI2, lo2, "%9.6e", double);
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
CVectorFloat CSDRTest::DataILoadFromFile(char *sName)
{
// -----------------------------------------------------------------------
// Description: loads input data from given file and skips comment started from "*"
//   Parametrs: ...
//      Return: vector
// -----------------------------------------------------------------------
//          MD: 21.11.2002
//          LE: 21.11.2002, 06.01.2003
// -----------------------------------------------------------------------
int nRes;
int i, nIdx, nIdxMax, nSize=0;
double dCoeff;
CVectorFloat tVect;
FILE* fp;
// -----------------------------------------------------------------------
fp=fopen(sName, "rt");
if (fp==NULL) return (tVect);
// -----------------------------------------------------------------------
nIdxMax=0;
while (!feof(fp))
	{ nRes=fscanf(fp, "%d %lf", &nIdx, &dCoeff);
	if (nRes!=-1)
		{
		if (nIdx>=nIdxMax) 
			{ nIdxMax=nIdx; nSize++; }
		else break;			
		}
	}
// -----------------------------------------------------------------------
rewind(fp); tVect=CVectorFloat(nSize);
	#ifdef SDRPDEMO_USEFIX // (06.01.2003)
	CVectConv::SetupFixPointInVector(tVect, 32, 15);
	#endif
for (i=0; i<nSize; i++)
	{ fscanf(fp, "%d %lf", &nIdx, &dCoeff);
	tVect[i]=dCoeff; }
fclose(fp);
// -----------------------------------------------------------------------
return (tVect);
}
// =======================================================================
CVectorFloat CSDRTest::DataOLoadFromFile(char *sName, int nBD, int nBI, int nMaxD, int nMaxI)
{
// -----------------------------------------------------------------------
// Description: loads given block of the output referenced data from given 
//              file and skips comment started from "*"
//   Parametrs: sName	- filename
//				nBD		- number of the decimation block (decimation ratio)
//				nBI		- number of the interpolation block (interpolation ratio)
//				nMaxD	- maximal decimation ratio (number of blocks)
//				nMaxI	- maximal intrepolation ratio (number of blocks)
//      Return: vector
// -----------------------------------------------------------------------
//          MD: 21.11.2002
//          LE: 21.11.2002
// -----------------------------------------------------------------------
BOOL bDone;
char sBuf[64];
int nRes;
int i, nIdx, nIdxMax, nSize;
int nItemsRead, nFirstDataItem, nSkipItems;
int nBDcur, nBIcur;
double dCoeff;
CVectorFloat tVect;
FILE* fp;
// -----------------------------------------------------------------------
fp=fopen(sName, "rt");
if (fp==NULL) return (tVect);
// -----------------------------------------------------------------------
nIdxMax=0;		// current idx
nBDcur=1;		// current decimation block
nBIcur=1;		// current interpolation block
nSize=0;
nItemsRead=0;	// total number of items hev been read
nFirstDataItem=0;
bDone=false;
// -----------------------------------------------------------------------
while (!feof(fp) && !bDone)
	{
	bDone=fgets(sBuf, sizeof(sBuf)-1, fp)==0?true:false;	
	if (!bDone)
		{
		nItemsRead++;
		// ---------------------------------------------------------------
		if (!strncmp(sBuf, "*", 1)) continue;
		nRes=sscanf(sBuf, "%d %lf", &nIdx, &dCoeff);
		if (nRes==-1) continue;
		// ---------------------------------------------------------------		
		bDone=false;
		if (nIdx>=nIdxMax)
			{
			nIdxMax=nIdx;
			nSize++;
			}
		else
			{
			if (nBDcur==nBD && nBIcur==nBI)
				bDone=true;				
			else
				{
				nFirstDataItem=nItemsRead;
				nIdxMax=0;
				nSize=1;
				nBIcur++;
				if (nBIcur>nMaxI)
					{
					nBIcur=1;
					nBDcur++;
					}
				}
			}			
		}
	}
// -----------------------------------------------------------------------
rewind(fp); tVect=CVectorFloat(nSize);
	#ifdef SDRPDEMO_USEFIX // (06.01.2003)
	CVectConv::SetupFixPointInVector(tVect, 32, 15);
	#endif
nSkipItems=nFirstDataItem-1;
for (i=0; i<nSkipItems; i++)
	{
	fgets(sBuf, sizeof(sBuf)-1, fp);
	nRes=sscanf(sBuf, "%d %lf", &nIdx, &dCoeff);	
	}
for (i=0; i<nSize; )
	{ 
	fgets(sBuf, sizeof(sBuf)-1, fp);
	//if (!strncmp(sBuf, "*", 1)) continue;
	nRes=sscanf(sBuf, "%d %lf", &nIdx, &dCoeff);
	tVect[i]=dCoeff; 
	i++;
	}
fclose(fp);
// -----------------------------------------------------------------------
return (tVect);
}
// =======================================================================
CVectorFloat CSDRTest::FilterLoadFromFile(char *sName)
{
// -----------------------------------------------------------------------
// Description: loads filter coefficients from given file
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 21.11.2002
//          LE: 21.11.2002, 06.01.2003
// -----------------------------------------------------------------------
int nRes;
int i, nSize=0;
double dCoeff;
CVectorFloat tVect;
FILE* fp;
// -----------------------------------------------------------------------
fp=fopen(sName, "rt");
if (fp==NULL) return (tVect);
// -----------------------------------------------------------------------
while (!feof(fp))
	{ nRes=fscanf(fp, "%lf", &dCoeff);
	if (nRes!=-1) nSize++; }
// -----------------------------------------------------------------------
rewind(fp); tVect=CVectorFloat(nSize);
	#ifdef SDRPDEMO_USEFIX // (06.01.2003)
	CVectConv::SetupFixPointInVector(tVect, 32, 15);
	#endif
for (i=0; i<nSize; i++)
	{ fscanf(fp, "%lf", &dCoeff);
	tVect[i]=dCoeff; }
fclose(fp);
// -----------------------------------------------------------------------
return (tVect);
}
// =======================================================================
int CSDRTest::SizePow2(int nSize)
{
// returns lower value which is closest to given number and is power of 2
double d=nSize;
double b=2;
double lnd=log(d);
double lnb=log(b);
double dSizeP2=lnd/lnb;
int nSizeP2=(int)pow(2, (int)dSizeP2);
return(nSizeP2);
}
// =======================================================================
