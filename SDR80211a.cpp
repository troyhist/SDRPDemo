// =======================================================================
// SDR 802.11a blocks ver. 1.0
// set of functions to process signals in the IEEE 802.11a standart
// -----------------------------------------------------------------------
//       MD: 09.01.2003
//       LE: 09.01.2003
// -----------------------------------------------------------------------
// Compiler: MS VC 6.0
// =======================================================================
// SDR80211a.cpp: implementation of the CSDR80211a class.
// =======================================================================
#include "stdafx.h"
#include "SDR80211a.h"
// -----------------------------------------------------------------------
#include "_DEBUG.H"			// debug file output (10.01.2003)
#include <crtdbg.h>			// _ASSERT (09.01.2003)
#include "VectConv.h"		// vector convertions
#include "SDRPrims.h"		// primitives: CONVENC, PUNCT, INTLEAV, etc.
// =======================================================================
// Construction/Destruction
// =======================================================================
CSDR80211a::CSDR80211a()
{

}
// =======================================================================
CSDR80211a::~CSDR80211a()
{

}
// =======================================================================
// public functions
// =======================================================================
BOOL CSDR80211a::Conv64FDToTD(CVectorFloat &pFDr, CVectorFloat &pFDi, CVectorFloat &pTDr, CVectorFloat &pTDi)	{
// -----------------------------------------------------------------------
// Description: performs IFFT and returns a cyclically extended signal in the time domain
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 16.01.2003
//          LE: 16.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	_ASSERT(pFDr.size()==64);	// wrong size of the input vector
	_ASSERT(pFDi.size());		// empty input vector
	_ASSERT(pFDr.size()==pFDi.size());		// empty input vector
	// -------------------------------------------------------------------
	CVectorFloat pFD1r, pFD1i;
	CVectorFloat pTD0r, pTD0i;
	// -------------------------------------------------------------------
	int nSize=pFDr.size();
	pTD0r=CVectorFloat(nSize);	pTD0i=CVectorFloat(nSize);
	// -------------------------------------------------------------------
	ReorderVector64(pFDr, pFD1r);
	ReorderVector64(pFDi, pFD1i);
	// -------------------------------------------------------------------
	CSDRPrims::IFFT(pFD1r, pFD1i, pTD0r, pTD0i);
	// -------------------------------------------------------------------
	CyclExt(pTD0r, pTDr, 16, 81);
	CyclExt(pTD0i, pTDi, 16, 81);
	// -------------------------------------------------------------------
	CSDRPrims::WindowW(pTDr, pTDr, 81);
	CSDRPrims::WindowW(pTDi, pTDi, 81);
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
CVectorBool CSDR80211a::CreateFieldSIGNALbin(int nDataRate, int nLen)	{
// -----------------------------------------------------------------------
// Description: creates field SIGNAL with given parametrs
//   Parametrs: nDataRate	- one of the data rates: 6, 9, 12, 18, 24, 36, 48, 54
//				nLen		- size of data in octets (bytes)
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 09.01.2003
//          LE: 10.01.2003, 14.01.2003
// -----------------------------------------------------------------------
	CVectorBool pSIGNALepi;		// encoded and converted to serial and interleaved (2 steps) signal (before #ifndef (30.01.2003))
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	CVectorBool pSIGNALue;		// unencoded signal
	CVectorBool pSIGNALe[2];	// encoded signal
	CVectorBool pSIGNALep;		// encoded and converted to serial signal
//	CVectorBool pSIGNALepi;		// encoded and converted to serial and interleaved (2 steps) signal
	// -------------------------------------------------------------------
	CVectorBool pMX(1), pMY(1);	// puncturing masks
	pMX[0]=1;	pMY[0]=1;		// it passes all bits (rate 1/2)
	// -------------------------------------------------------------------
	// encoding chain
	// -------------------------------------------------------------------
	pSIGNALue=CreateUnencodedFieldSIGNAL(GetRateBitsByDataRate(nDataRate), nLen);
	CSDRPrims::CONVENC(pSIGNALue, pSIGNALe[0], pSIGNALe[1]);
	CSDRPrims::PUNCT(pSIGNALe[0], pSIGNALe[1], pSIGNALep, pMX, pMY);
	CSDRPrims::INTLEAV(pSIGNALep, pSIGNALepi, 48, 1);
	// -------------------------------------------------------------------
	// debug section
	// -------------------------------------------------------------------
	_DEBUG_TRACEVECT3("Data\\p802Sue.txt", pSIGNALue, pSIGNALue.size(), "%d", int);
	_DEBUG_TRACEVECT3("Data\\p802Se0.txt", pSIGNALe[0], pSIGNALe[0].size(), "%d", int);
	_DEBUG_TRACEVECT3("Data\\p802Se1.txt", pSIGNALe[1], pSIGNALe[1].size(), "%d", int);
	_DEBUG_TRACEVECT3("Data\\p802Sep.txt", pSIGNALep, pSIGNALep.size(), "%d", int);
	_DEBUG_TRACEVECT3("Data\\p802Sepi.txt", pSIGNALepi, pSIGNALepi.size(), "%d", int);
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(pSIGNALepi);
	}
// =======================================================================
BOOL CSDR80211a::CreateFieldSIGNALfd(int nDataRate, int nLen, CVectorFloat& pSI, CVectorFloat& pSQ)	{
// -----------------------------------------------------------------------
// Description: creates field SIGNAL with given parametrs
//   Parametrs: nDataRate	- one of the rates: 6, 9, 12, 18, 24, 36, 48, 54
//				nLen		- size of data in octets (bytes)
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 14.01.2003
//          LE: 14.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	CVectorBool pSIGNALbin;		// unencoded signal
	CVectorFloat pSI0, pSQ0;	// modulated signals (I, Q)
	// -------------------------------------------------------------------
	// encoding chain
	// -------------------------------------------------------------------
	pSIGNALbin=CreateFieldSIGNALbin(nDataRate, nLen);
	CSDRPrims::MODUL_BPSK(pSIGNALbin, pSI0, pSQ0);
	InsertPilotsAndZero(pSI0, pSQ0, pSI, pSQ, 1);
	// -------------------------------------------------------------------
	// debug section
	// -------------------------------------------------------------------
	/*
	CVectorFloat pTempI; ReorderVector64(pSI, pTempI);	// reordered for MathCAD (15.01.2003)
	_DEBUG_TRACEVECT3("Data\\p802SFDI_.txt", pTempI, pTempI.size(), "%9.3lf", double);//*/
	// -------------------------------------------------------------------
	_DEBUG_TRACEVECT3("Data\\p802SFDI.txt", pSI, pSI.size(), "%9.3lf", double);
	_DEBUG_TRACEVECT3("Data\\p802SFDQ.txt", pSQ, pSQ.size(), "%9.3lf", double);
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDR80211a::CreateFieldSIGNALtd(int nDataRate, int nLen, CVectorFloat& pTDr, CVectorFloat& pTDi)	{
// -----------------------------------------------------------------------
// Description: creates field SIGNAL with given parametrs
//   Parametrs: nDataRate	- one of the rates: 6, 9, 12, 18, 24, 36, 48, 54
//				nLen		- size of data in octets (bytes)
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 09.01.2003
//          LE: 10.01.2003, 15.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	CVectorBool pSIGNALbin;		// unencoded signal
	CVectorFloat pFDr, pFDi;	// modulated signals (I, Q)
	// -------------------------------------------------------------------
	// encoding chain
	// -------------------------------------------------------------------
	CreateFieldSIGNALfd(nDataRate, nLen, pFDr, pFDi);
	Conv64FDToTD(pFDr, pFDi, pTDr, pTDi);
	// -------------------------------------------------------------------
	// debug section
	// -------------------------------------------------------------------
	_DEBUG_TRACEVECT3("Data\\p802STDr.txt", pTDr, pTDr.size(), "%9.3lf", double);
	_DEBUG_TRACEVECT3("Data\\p802STDi.txt", pTDi, pTDi.size(), "%9.3lf", double);
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDR80211a::CreatePacket(int nDataRate, int nLen, CVectorBool &pData, CVectorFloat &pPackR, CVectorFloat &pPackI)	{
// -----------------------------------------------------------------------
// Description: creates a data packet inhalted several data symbols
//   Parametrs: nDataRate	- one of the allowed data rates: 6, 9, 12, 18, 24, 36, 48, 54
//				nLen		- length of DATA field in Bytes (w/o first 16 SERVICE bits and 6 tail)
//				pData		- input data (with SERVICE field and tail)
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 20.01.2003
//          LE: 22.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	int i;
	int nDataSymb;				// number of DATA symbols in the packet
	int nDataSize=pData.size();	// len
	int nEncDataSize;			// encoded data size
	int nSymbSize;				// size of one DATA symbol
	int nModulType;				// modulation type
	int nNdbps=GetNdbpsByDataRate(nDataRate);	// Data bits / OFDM symb.
	// -------------------------------------------------------------------
	int c0=nLen*8+16;			// tail bits start
	int c1=c0+6;				// tail bits end
	// -------------------------------------------------------------------
	_ASSERT(!(pData.size()%nNdbps));	// size of input array has to be a multiply of Ndbps
	_ASSERT(16+6+nLen*8<pData.size());	// space for "tail" bits is not reserved
	// -------------------------------------------------------------------
	CVectorFloat pSST[2];	// Short sequence in TD
	CVectorFloat pLST[2];	// Long sequence in TD
	CVectorFloat pST[2];	// field SIGNAL in TD
	// -------------------------------------------------------------------
	CVectorBool pD1, pD2, pD3, pWnd;
	CVectorFloat pD4[2];	// spectrum (modulated signal)
	CVectorFloat pSymbOFDM[2];
	// -------------------------------------------------------------------
	nModulType=GetModulTypeByDataRate(nDataRate);	// modulation type
	nSymbSize=GetNcbpsByDataRate(nDataRate);		// symbol size in bits
	// -------------------------------------------------------------------
	// standart sequences generation
	// -------------------------------------------------------------------
	GenerateShortSequenceTD(pSST[0], pSST[1]);
	GenerateLongSequenceTD(pLST[0], pLST[1]);
	CreateFieldSIGNALtd(nDataRate, nLen, pST[0], pST[1]);
	// -------------------------------------------------------------------
	// adds standart sequences in the beginning of the chain
	// -------------------------------------------------------------------
	AppendDataSymbolToChain(pPackR, pSST[0]);	AppendDataSymbolToChain(pPackI, pSST[1]);
	AppendDataSymbolToChain(pPackR, pLST[0]);	AppendDataSymbolToChain(pPackI, pLST[1]);
	AppendDataSymbolToChain(pPackR, pST[0]);	AppendDataSymbolToChain(pPackI, pST[1]);
	// -------------------------------------------------------------------
	// processing chain
	// -------------------------------------------------------------------
	DataScramble(pData, pD1);					// scrambling
	for (i=c0; i<c1; i++) pD1[i]=0;				// clears tail bits (22.01.2003)
	DateEncode(pD1, pD2, nDataRate);			// conv. encoding and puncturing
	DataIntleav(pD2, pD3, nDataRate);			// interleaving
	// -------------------------------------------------------------------
	// block processing
	// -------------------------------------------------------------------
	nEncDataSize=pD2.size();
	nDataSymb=nEncDataSize/nSymbSize;
	_ASSERT(!(nEncDataSize%nSymbSize));	// size of data array has to be a multiply of nSymbSize
	// -------------------------------------------------------------------
	for (i=0; i<nDataSymb; i++)
		{
		pWnd=CVectConv::GetWindow(pD3, nSymbSize, i);
		DataConvToFD(pWnd, pD4[0], pD4[1], nModulType, GetPilotPolarity(i+1));
		Conv64FDToTD(pD4[0], pD4[1], pSymbOFDM[0], pSymbOFDM[1]);
		// ---------------------------------------------------------------
		// append data symbols to the whole chain
		// ---------------------------------------------------------------
		AppendDataSymbolToChain(pPackR, pSymbOFDM[0]);
		AppendDataSymbolToChain(pPackI, pSymbOFDM[1]);
		// ---------------------------------------------------------------
		}
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return (true);
	}
// =======================================================================
BOOL CSDR80211a::DataConvToFD(CVectorBool &x, CVectorFloat &pSr, CVectorFloat &pSi, int nModulType, int pPilPolar)	{
// -----------------------------------------------------------------------
// Description: modulates input vector
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 16.01.2003
//          LE: 21.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	// TODO: test the support of different modulation types, except 16QAM (20.01.2003)
	// -------------------------------------------------------------------
	_ASSERT(x.size());		// empty input vector
	_ASSERT((nModulType==CSDR_MODULBPSK && x.size()==48) ||
			(nModulType==CSDR_MODULQPSK && x.size()==96) ||
			(nModulType==CSDR_MODUL16QAM && x.size()==192) ||
			(nModulType==CSDR_MODUL64QAM && x.size()==288));
	// -------------------------------------------------------------------
	CVectorFloat pSI0, pSQ0;
	// -------------------------------------------------------------------
	switch(nModulType)
		{
		case CSDR_MODULBPSK:	CSDRPrims::MODUL_BPSK(x, pSI0, pSQ0); break;
		case CSDR_MODULQPSK:	CSDRPrims::MODUL_QPSK(x, pSI0, pSQ0); break;
		case CSDR_MODUL16QAM:	CSDRPrims::MODUL_16QAM(x, pSI0, pSQ0); break;
		case CSDR_MODUL64QAM:	CSDRPrims::MODUL_64QAM(x, pSI0, pSQ0); break;
		default: _ASSERT(0); break;
		};
	// -------------------------------------------------------------------
	//pSI0=CVectorFloat(59);	pSQ0=CVectorFloat(59); // test: leave pilots only
	InsertPilotsAndZero(pSI0, pSQ0, pSr, pSi, pPilPolar);
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDR80211a::DataIntleav(CVectorBool &x, CVectorBool &y, int nDataRate)	{
// -----------------------------------------------------------------------
// Description: interleaves data of the input vector
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 16.01.2003
//          LE: 16.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	_ASSERT(x.size());		// empty input vector
	// -------------------------------------------------------------------
	int Ncbps=GetNcbpsByDataRate(nDataRate),
		Nbpsc=GetNbpscByDataRate(nDataRate);
	CSDRPrims::INTLEAV(x, y, Ncbps, Nbpsc);
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDR80211a::DataScramble(CVectorBool &x, CVectorBool &y)	{
// -----------------------------------------------------------------------
// Description: scrambles input array with predefined scrambling key
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 15.01.2003
//          LE: 16.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	_ASSERT(x.size());		// empty input vector
	// -------------------------------------------------------------------
	CVectorBool pState(7);
	// -------------------------------------------------------------------
	y=CVectorBool(x.size());
	pState[0]=1;	pState[1]=0;	pState[2]=1;	pState[3]=1;
	pState[4]=1;	pState[5]=0;	pState[6]=1;
	CSDRPrims::SCRAMBL(x, y, pState);
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDR80211a::DataScramble(CVectorBool &x, CVectorBool &y, CVectorBool& pState)	{
// -----------------------------------------------------------------------
// Description: scrambles input array with user-defined scrambling key
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 24.01.2003
//          LE: 24.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	_ASSERT(x.size());			// empty input vector
	_ASSERT(pState.size()==7);	// empty input vector
	// -------------------------------------------------------------------
	y=CVectorBool(x.size());
	CSDRPrims::SCRAMBL(x, y, pState);
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDR80211a::DateEncode(CVectorBool &x, CVectorBool &y, int nDataRate)	{
// -----------------------------------------------------------------------
// Description: encodes input data with a requested rate convolituion code
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 16.01.2003
//          LE: 20.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	_ASSERT(x.size());			// empty input vector
	// -------------------------------------------------------------------
	int nCodeRate;
	CVectorBool pXE[2];			// encoded data
	CVectorBool pMX, pMY;		// puncturing masks
	// -------------------------------------------------------------------
	nCodeRate=GetCodeRateByDataRate(nDataRate);
	GetPunctMaskByCodeRate(nCodeRate, pMX, pMY);
	// -------------------------------------------------------------------
	// encoding chain
	// -------------------------------------------------------------------
	CSDRPrims::CONVENC(x, pXE[0], pXE[1]);
	CSDRPrims::PUNCT(pXE[0], pXE[1], y, pMX, pMY);
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDR80211a::GenerateLongSequenceFD(CVectorFloat &pLSr, CVectorFloat& pLSi)	{
// -----------------------------------------------------------------------
// Description: generates a long sequence in a frequency domain
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 14.01.2003
//          LE: 14.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	int nSize=64;
	pLSr=CVectorFloat(nSize);
	pLSi=CVectorFloat(nSize);
	// -------------------------------------------------------------------
	pLSr[32-26]= 1;		pLSr[32-25]= 1;		pLSr[32-24]=-1;
	pLSr[32-23]=-1;		pLSr[32-22]= 1;		pLSr[32-21]= 1;
	pLSr[32-20]=-1;		pLSr[32-19]= 1;		pLSr[32-18]=-1;
	pLSr[32-17]= 1;

	pLSr[32-16]= 1;		pLSr[32-15]= 1;		pLSr[32-14]= 1;
	pLSr[32-13]= 1;		pLSr[32-12]= 1;		pLSr[32-11]=-1;
	pLSr[32-10]=-1;		pLSr[32-9]= 1;		pLSr[32-8]= 1;
	pLSr[32-7]=-1;		pLSr[32-6]= 1;		pLSr[32-5]=-1;
	pLSr[32-4]= 1;		pLSr[32-3]= 1;		pLSr[32-2]= 1;
	pLSr[32-1]= 1;
	// -------------------------------------------------------------------
	pLSr[32+0]= 0;		pLSr[32+1]= 1;		pLSr[32+2]=-1;
	pLSr[32+3]=-1;		pLSr[32+4]= 1;		pLSr[32+5]= 1;
	pLSr[32+6]=-1;		pLSr[32+7]= 1;		pLSr[32+8]=-1;
	pLSr[32+9]= 1;		pLSr[32+10]=-1;		pLSr[32+11]=-1;
	pLSr[32+12]=-1;		pLSr[32+13]=-1;		pLSr[32+14]=-1;
	pLSr[32+15]= 1;	
	
	pLSr[32+16]= 1;		pLSr[32+17]=-1;		pLSr[32+18]=-1;
	pLSr[32+19]= 1;		pLSr[32+20]=-1;		pLSr[32+21]= 1;
	pLSr[32+22]=-1;		pLSr[32+23]= 1;		pLSr[32+24]= 1;
	pLSr[32+25]= 1;		pLSr[32+26]= 1;
	// -------------------------------------------------------------------
	CVectorFloat pLS1r;
	ReorderVector64(pLSr, pLS1r);
	pLSr=pLS1r;
	// -------------------------------------------------------------------
	// debug section
	// -------------------------------------------------------------------
	_DEBUG_TRACEVECT3("Data\\p802LSFDr.txt", pLSr, pLSr.size(), "%9.3lf", double);
	_DEBUG_TRACEVECT3("Data\\p802LSFDi.txt", pLSi, pLSi.size(), "%9.3lf", double);
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDR80211a::GenerateLongSequenceTD(CVectorFloat& pLSr, CVectorFloat& pLSi)	{
// -----------------------------------------------------------------------
// Description: generates a short sequence in a frequency domain
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 14.01.2003
//          LE: 15.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	CVectorFloat pFDr, pFDi;
	CVectorFloat pTDr, pTDi;
	GenerateLongSequenceFD(pFDr, pFDi);
	// -------------------------------------------------------------------
	pTDr=CVectorFloat(pFDr.size());
	pTDi=CVectorFloat(pFDi.size());
	// -------------------------------------------------------------------
	CSDRPrims::IFFT(pFDr, pFDi, pTDr, pTDi);
	// -------------------------------------------------------------------
	CyclExt(pTDr, pLSr, 32, 161);
	CyclExt(pTDi, pLSi, 32, 161);
	// -------------------------------------------------------------------
	CSDRPrims::WindowW(pLSr, pLSr, 161);
	CSDRPrims::WindowW(pLSi, pLSi, 161);
	// -------------------------------------------------------------------
	_DEBUG_TRACEVECT3("Data\\p802LSTDr_.txt", pTDr, pTDr.size(), "%9.3lf", double);
	_DEBUG_TRACEVECT3("Data\\p802LSTDi_.txt", pTDi, pTDi.size(), "%9.3lf", double);
	_DEBUG_TRACEVECT3("Data\\p802LSTDr.txt", pLSr, pLSr.size(), "%9.3lf", double);
	_DEBUG_TRACEVECT3("Data\\p802LSTDi.txt", pLSi, pLSi.size(), "%9.3lf", double);
	// -----------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDR80211a::GenerateShortSequenceFD(CVectorFloat& pSSr, CVectorFloat& pSSi)	{
// -----------------------------------------------------------------------
// Description: generates a short sequence in a frequency domain
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 13.01.2003
//          LE: 13.01.2003
// -----------------------------------------------------------------------
#ifndef SDRPDEMO_USEFIX
// -----------------------------------------------------------------------
int nSize=64;
const double dNormFact=sqrt(13./6.);
pSSr=CVectorFloat(nSize);
pSSi=CVectorFloat(nSize);
// -----------------------------------------------------------------------
pSSr[64-24]= 1;	pSSi[64-24]= 1;
pSSr[64-20]=-1;	pSSi[64-20]=-1;
pSSr[64-16]= 1;	pSSi[64-16]= 1;
pSSr[64-12]=-1;	pSSi[64-12]=-1;
pSSr[64-8]= -1;	pSSi[64-8]= -1;
pSSr[64-4]=  1;	pSSi[64-4]=  1;
// -----------------------------------------------------------------------
pSSr[4]= -1;	pSSi[4]= -1;
pSSr[8]= -1;	pSSi[8]= -1;
pSSr[12]= 1;	pSSi[12]= 1;
pSSr[16]= 1;	pSSi[16]= 1;
pSSr[20]= 1;	pSSi[20]= 1;
pSSr[24]= 1;	pSSi[24]= 1;
// -----------------------------------------------------------------------
for (int i=0; i<nSize; i++)
	{
	pSSr[i]*=dNormFact;
	pSSi[i]*=dNormFact;
	}
// -----------------------------------------------------------------------
// debug section
// -----------------------------------------------------------------------
_DEBUG_TRACEVECT3("Data\\p802SSFDr.txt", pSSr, pSSr.size(), "%9.3lf", double);
_DEBUG_TRACEVECT3("Data\\p802SSFDi.txt", pSSi, pSSi.size(), "%9.3lf", double);
// -----------------------------------------------------------------------
#else
_ASSERT(0);					// FxP is not supported (30.01.2003)
#endif // SDRPDEMO_USEFIX
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CSDR80211a::GenerateShortSequenceTD(CVectorFloat& pSTr, CVectorFloat& pSTi)	{
// -----------------------------------------------------------------------
// Description: generates a short sequence in a frequency domain
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 14.01.2003
//          LE: 15.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	CVectorFloat pFDr, pFDi;
	CVectorFloat pTDr, pTDi;
	GenerateShortSequenceFD(pFDr, pFDi);
	// -------------------------------------------------------------------
	pTDr=CVectorFloat(pFDr.size());
	pTDi=CVectorFloat(pFDi.size());
	// -------------------------------------------------------------------
	CSDRPrims::IFFT(pFDr, pFDi, pTDr, pTDi);
	// -------------------------------------------------------------------
	CyclExt(pTDr, pSTr, 16, 161);
	CyclExt(pTDi, pSTi, 16, 161);
	// -------------------------------------------------------------------
	CSDRPrims::WindowW(pSTr, pSTr, 161);
	CSDRPrims::WindowW(pSTi, pSTi, 161);
	// -------------------------------------------------------------------
	_DEBUG_TRACEVECT3("Data\\p802SSTDr_.txt", pTDr, pTDr.size(), "%9.3lf", double);
	_DEBUG_TRACEVECT3("Data\\p802SSTDi_.txt", pTDi, pTDi.size(), "%9.3lf", double);
	_DEBUG_TRACEVECT3("Data\\p802SSTDr.txt", pSTr, pSTr.size(), "%9.3lf", double);
	_DEBUG_TRACEVECT3("Data\\p802SSTDi.txt", pSTi, pSTi.size(), "%9.3lf", double);
	// -----------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
CVectorBool CSDR80211a::GetDummyData()	{
// -----------------------------------------------------------------------
// Description: generates dummy data array (as a binary vector)
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 09.01.2003
//          LE: 15.01.2003
// -----------------------------------------------------------------------
CVectorBool tResBool(108*8);	// before #ifndef (30.01.2003)
#ifndef SDRPDEMO_USEFIX
// -----------------------------------------------------------------------
int i=0;
CVectorInt tRes(108);
//CVectorBool tResBool(108*8);
tRes[i++]=0x00;	tRes[i++]=0x00;	// Service 16 bits
tRes[i++]=0x04;	tRes[i++]=0x02;	tRes[i++]=0x00;	tRes[i++]=0x2e;	tRes[i++]=0x00;
tRes[i++]=0x60;	tRes[i++]=0x08;	tRes[i++]=0xcd;	tRes[i++]=0x37;	tRes[i++]=0xa6;
tRes[i++]=0x00;	tRes[i++]=0x20;	tRes[i++]=0xd6;	tRes[i++]=0x01;	tRes[i++]=0x3c;
tRes[i++]=0xf1;	tRes[i++]=0x00;	tRes[i++]=0x60;	tRes[i++]=0x08;	tRes[i++]=0xad;
tRes[i++]=0x3b;	tRes[i++]=0xaf;	tRes[i++]=0x00;	tRes[i++]=0x00;	tRes[i++]='J';

tRes[i++]='o';	tRes[i++]='y';	tRes[i++]=',';	tRes[i++]=' ';	tRes[i++]='b';
tRes[i++]='r';	tRes[i++]='i';	tRes[i++]='g';	tRes[i++]='h';	tRes[i++]='t';
tRes[i++]=' ';	tRes[i++]='s';	tRes[i++]='p';	tRes[i++]='a';	tRes[i++]='r';
tRes[i++]='k';	tRes[i++]=' ';	tRes[i++]='o';	tRes[i++]='f';	tRes[i++]=' ';
tRes[i++]='d';	tRes[i++]='i';	tRes[i++]='v';	tRes[i++]='i';	tRes[i++]='n';

tRes[i++]='i';	tRes[i++]='t';	tRes[i++]='y';	tRes[i++]=',';	tRes[i++]=0x0a;
tRes[i++]='D';	tRes[i++]='a';	tRes[i++]='u';	tRes[i++]='g';	tRes[i++]='h';
tRes[i++]='t';	tRes[i++]='e';	tRes[i++]='r';	tRes[i++]=' ';	tRes[i++]='o';
tRes[i++]='f';	tRes[i++]=' ';	tRes[i++]='E';	tRes[i++]='l';	tRes[i++]='y';
tRes[i++]='s';	tRes[i++]='i';	tRes[i++]='u';	tRes[i++]='m';	tRes[i++]=',';

tRes[i++]=0x0a;	tRes[i++]='F';	tRes[i++]='i';	tRes[i++]='r';	tRes[i++]='e';
tRes[i++]='-';	tRes[i++]='i';	tRes[i++]='n';	tRes[i++]='s';	tRes[i++]='i';
tRes[i++]='r';	tRes[i++]='e';	tRes[i++]='d';	tRes[i++]=' ';	tRes[i++]='w';
tRes[i++]='e';	tRes[i++]=' ';	tRes[i++]='t';	tRes[i++]='r';	tRes[i++]='e';
tRes[i++]='a';	tRes[i++]=0xda;	tRes[i++]=0x57;	tRes[i++]=0x99;	tRes[i++]=0xed;
tRes[i++]=0x00;	// tail (only 6 bits)
tRes[i++]=0x00;	tRes[i++]=0x00;	tRes[i++]=0x00; tRes[i++]=0x00;	tRes[i++]=0x00;
// -----------------------------------------------------------------------
CVectConv::ConvVectIntToBool(tRes, tResBool, 8);
// -----------------------------------------------------------------------
// debug section
// -----------------------------------------------------------------------
//_DEBUG_TRACEVECT3("Data\\p802Data0_.txt", tRes, tRes.size(), "%02x\n", int);
_DEBUG_TRACEVECT4("Data\\p802Data0_.txt", tRes, tRes.size(), "%02x\n", int, 5);
_DEBUG_TRACEVECT3("Data\\p802Data0.txt", tResBool, tResBool.size(), "%d\n", int);
// -----------------------------------------------------------------------
#else
_ASSERT(0);					// FxP is not supported (30.01.2003)
#endif // SDRPDEMO_USEFIX
// -----------------------------------------------------------------------
return(tResBool);
}
// =======================================================================
BOOL CSDR80211a::ReorderVector64(CVectorFloat &x, CVectorFloat &y)	{
// -----------------------------------------------------------------------
// Description: changes order of elements in input vector to make it suitable
//				for IFFT
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 15.01.2003
//          LE: 16.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	_ASSERT(x.size()==64);			// constrain
	_ASSERT(y.size()==0);			// let it be for simplification
 	_ASSERT(&x!=&y);				// it's not possible to use the same vector
	// -------------------------------------------------------------------
	y=CVectorFloat(64);
	// -------------------------------------------------------------------
	for (int i=0; i<32; i++)
		{
		y[i]=x[i+32];
		y[i+32]=x[i];
		}
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
// protected
// =======================================================================
CVectorBool CSDR80211a::CreateUnencodedFieldSIGNAL(int nRate, int nLen)	{
// -----------------------------------------------------------------------
// Description: creates unencoded field SIGNAL with given parametrs
//   Parametrs: nRate	- ENCODED value of the data rate
//				nLen	- size of data in octets (bytes)
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 09.01.2003
//          LE: 15.01.2003
// -----------------------------------------------------------------------
	_ASSERT(nRate>=0 && nRate<16);		// only 4 bits ar possible
	_ASSERT(nLen>=1 && nLen< 4096);		// maximal size is 2^12
	// -------------------------------------------------------------------
	int i;
	int nOnes=0;
	CVectorBool pRate, pLen;
	CVectorBool pSIGNAL(24);
	CVectConv::ConvertIntToVectBool(nRate, pRate, 4);
	CVectConv::ConvertIntToVectBool(nLen, pLen, 12);
	pSIGNAL[4]=0;
	for (i=0; i<4; i++)		pSIGNAL[i+0]=pRate[i];
	for (i=0; i<12; i++)	pSIGNAL[i+5]=pLen[i];
	for (i=0; i<6; i++)		pSIGNAL[i+18]=0;
	// -------------------------------------------------------------------
	// calculates parity (15.01.2003)
	// -------------------------------------------------------------------
	for (i=0; i<17; i++) if (pSIGNAL[i])	nOnes++;
	pSIGNAL[17]=nOnes&1;			// parity
	// -------------------------------------------------------------------
	return(pSIGNAL);
	}
// =======================================================================
BOOL CSDR80211a::CyclExt(CVectorFloat &x, CVectorFloat &y, int nTailSize, int nNewSize)	{
// -----------------------------------------------------------------------
// Description: cyclically extends a signal in the time domain
//   Parametrs: x			- input vector (vector after IFFT)
//				y			- output vector
//				nTailSize	- number of the last elements to copy in the beginning
//				nNewSize	- number of elements in the new vector
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 14.01.2003
//          LE: 15.01.2003
// -----------------------------------------------------------------------
	_ASSERT(x.size());							// empty input vector
	_ASSERT(nNewSize>=(x.size()+nTailSize));	// incorrect new size
	// -------------------------------------------------------------------
	int nSize=x.size();
	int i, j;
	// -------------------------------------------------------------------
	y=CVectorFloat(nNewSize);
	// -------------------------------------------------------------------
	// copies a tail
	// -------------------------------------------------------------------
	for (i=0; i<nTailSize; i++)
		y[i]=x[nSize-nTailSize+i];
	// -------------------------------------------------------------------
	// extends cyclically
	// -------------------------------------------------------------------
	for (i=nTailSize, j=0; i<nNewSize; i++, j++)
		{
		if (j>=nSize) j=0;
		y[i]=x[j];
		}
	// -------------------------------------------------------------------
	return(true);
	// -------------------------------------------------------------------
	}
// =======================================================================
BOOL CSDR80211a::InsertPilotsAndZero(CVectorFloat &iI, CVectorFloat &iQ, CVectorFloat &oI, CVectorFloat &oQ, int pPilPolar)	{
// -----------------------------------------------------------------------
// Description: inserts 4 pilot subcarriers into the specified location
//				and inserts zero frequency at (0, 0)
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 10.01.2003
//          LE: 10.01.2003, 16.01.2003
// -----------------------------------------------------------------------
	#ifndef SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	_ASSERT(iI.size());				// empty input vector
	_ASSERT(iQ.size());				// empty input vector
	_ASSERT(iI.size()==59);			// wrong size of an input vector
	_ASSERT(iI.size()==iQ.size());	// wrong size of the input vectors
	// -------------------------------------------------------------------
	int i;
	int nSizeX=iI.size();
	int nSizeY=nSizeX+5;
	int nShift=0;
	oI=CVectorFloat(nSizeY);
	oQ=CVectorFloat(nSizeY);
	// -------------------------------------------------------------------
	CVectorFloat pPI(5), pPQ(5);	// pilot signals
	// -------------------------------------------------------------------
	pPI[0]=1.0;		pPQ[0]=0.0;
	pPI[1]=1.0;		pPQ[1]=0.0;
	pPI[2]=0.0;		pPQ[2]=0.0;		// zero at position zero
	pPI[3]=1.0;		pPQ[3]=0.0;
	pPI[4]=-1.0;	pPQ[4]=0.0;
	// -------------------------------------------------------------------
	// calculates pilot signals polarity (16.01.2003)
	// -------------------------------------------------------------------
	for (i=0; i<5; i++)	{
		pPI[i]*=pPilPolar;	pPQ[i]*=pPilPolar;	
		//printf("pPI[%d] = %f, ", i, float(pPI[i]));	// test (16.01.2003)
		}
	// -------------------------------------------------------------------
	for (i=0; i<nSizeY; i++)
		{
		if (i==(32-21) || i==(32-7) || i==(32+0) || i==(32+7) || i==(32+21))
			{
			oI[i]=pPI[nShift];	oQ[i]=pPQ[nShift]; nShift++;
			continue;
			}
		oI[i]=iI[i-nShift];
		oQ[i]=iQ[i-nShift];
		}
	// -------------------------------------------------------------------
	#else
	_ASSERT(0);					// FxP is not supported (30.01.2003)
	#endif // SDRPDEMO_USEFIX
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
BOOL CSDR80211a::AppendDataSymbolToChain(CVectorFloat &pChain, CVectorFloat &pSymbol)	{
// -----------------------------------------------------------------------
// Description: appends an OFDM data symbol to the whole packet chain
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 20.01.2003
//          LE: 20.01.2003
// -----------------------------------------------------------------------
	_ASSERT(pSymbol.size()>0);
	// -------------------------------------------------------------------
	int i;
	int nSymbSize=pSymbol.size();
	int nChSize=pChain.size();
	int nNewSize;
	CVectorFloat pTemp;
	// -------------------------------------------------------------------
	nNewSize=nSymbSize+nChSize-1;
	pTemp=CVectorFloat(nNewSize);
	// -------------------------------------------------------------------
	if (nChSize==0) { pChain=pSymbol; return(true); }
	// -------------------------------------------------------------------
	for (i=0; i<nChSize-1; i++) pTemp[i]=pChain[i];
	for (i=1; i<nSymbSize; i++) pTemp[i+nChSize-1]=pSymbol[i];
	pTemp[nChSize-1]=pChain[nChSize-1]+pSymbol[0];	// avg. value
	// -------------------------------------------------------------------
	pChain=pTemp;
	// -------------------------------------------------------------------
	return(true);
	}
// =======================================================================
int CSDR80211a::GetCodeRateByDataRate(int nDataRate)	{
	int nRes;
	switch(nDataRate)
		{
		case 6:		case 12:	case 24:		nRes=CSDR_CRATE12; break;
		case 9:		case 18:	case 36:		nRes=CSDR_CRATE34; break;
		case 48:								nRes=CSDR_CRATE23; break;
		default:								_ASSERT(0);	// wrong Data Rate
			nRes=GLOBAL_ERROR; break;
		}
	return(nRes);
	}
// =======================================================================
int CSDR80211a::GetModulTypeByDataRate(int nDataRate)	{
	int nRes;
	switch(nDataRate)
		{
		case 6:		case 9:		nRes=CSDR_MODULBPSK; break;
		case 12:	case 18:	nRes=CSDR_MODULQPSK; break;
		case 24:	case 36:	nRes=CSDR_MODUL16QAM; break;
		case 48:	case 54:	nRes=CSDR_MODUL64QAM; break;
		default:				_ASSERT(0);	// wrong Data Rate
			nRes=GLOBAL_ERROR; break;
		}
	return(nRes);
	}
// =======================================================================
int CSDR80211a::GetNbpscByDataRate(int nDataRate)	{
	int nRes;
	switch(nDataRate)
		{
		case 6:		case 9:		nRes=1; break;
		case 12:	case 18:	nRes=2; break;
		case 24:	case 36:	nRes=4; break;
		case 48:	case 54:	nRes=6; break;
		default:				_ASSERT(0);	// wrong Data Rate
			nRes=GLOBAL_ERROR; break;
		}
	return(nRes);
	}
// =======================================================================
int CSDR80211a::GetNcbpsByDataRate(int nDataRate)	{
	int nRes;
	switch(nDataRate)
		{
		case 6:		case 9:		nRes=48; break;
		case 12:	case 18:	nRes=96; break;
		case 24:	case 36:	nRes=192; break;
		case 48:	case 54:	nRes=288; break;
		default:				_ASSERT(0);	// wrong Data Rate
			nRes=GLOBAL_ERROR; break;
		}
	return(nRes);
	}
// =======================================================================
int CSDR80211a::GetNdbpsByDataRate(int nDataRate)	{
	int nRes;
	switch(nDataRate)
		{
		case 6:		nRes=24; break;
		case 9:		nRes=36; break;
		case 12:	nRes=48; break;
		case 18:	nRes=72; break;
		case 24:	nRes=96; break;
		case 36:	nRes=144; break;
		case 48:	nRes=192; break;
		case 54:	nRes=216; break;
		default:	_ASSERT(0);	// wrong Data Rate
			nRes=GLOBAL_ERROR; break;
		}
	return(nRes);
	}
// =======================================================================
int CSDR80211a::GetPilotPolarity(int nIdx)	{
	_ASSERT(nIdx>=0);
int pPilot[]={1,1,1,1, -1,-1,-1,1, -1,-1,-1,-1, 1,1,-1,1, -1,-1,1,1, -1,1,1,-1, 1,1,1,1, 1,1,-1,1,
1,1,-1,1, 1,-1,-1,1, 1,1,-1,1, -1,-1,-1,1, -1,1,-1,-1, 1,-1,-1,1, 1,1,1,1, -1,-1,1,1,
-1,-1,1,-1, 1,-1,1,1, -1,-1,-1,1, 1,-1,-1,-1, -1,1,-1,-1, 1,-1,1,1, 1,1,-1,1, -1,1,-1,1,
-1,-1,-1,-1, -1,1,-1,1, 1,-1,1,-1, 1,1,1,-1, -1,1,-1,-1, -1,1,1,1, -1,-1,-1,-1, -1,-1,-1};
	int nK=nIdx%127;
	int nPilot=pPilot[nK];
	return(nPilot);
	}
// =======================================================================
BOOL CSDR80211a::GetPunctMaskByCodeRate(int nCodeRate, CVectorBool &pMX, CVectorBool &pMY)	{
// -----------------------------------------------------------------------
// Description: returns puncturing masks for differen code rates
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 20.01.2003
//          LE: 20.01.2003
// -----------------------------------------------------------------------
switch(nCodeRate)
	{
	case CSDR_CRATE12:
		// ---------------------------------------------------------------
		pMX=CVectorBool(1);	pMY=CVectorBool(1);	pMX[0]=1;	pMY[0]=1;
		// ---------------------------------------------------------------
		break;
	case CSDR_CRATE23:
		// ---------------------------------------------------------------
		pMX=CVectorBool(6);	pMY=CVectorBool(6);
		pMX[0]=1;	pMX[1]=1;	pMX[2]=1;	pMX[3]=1;	pMX[4]=1;	pMX[5]=1;
		pMY[0]=1;	pMY[1]=0;	pMY[2]=1;	pMY[3]=0;	pMY[4]=1;	pMY[5]=0;
		// ---------------------------------------------------------------
		break;
	case CSDR_CRATE34:
		// ---------------------------------------------------------------
		pMX=CVectorBool(9);	pMY=CVectorBool(9);
		pMX[0]=1;	pMX[1]=1;	pMX[2]=0;	pMX[3]=1;	pMX[4]=1;
		pMX[5]=0;	pMX[6]=1;	pMX[7]=1;	pMX[8]=0;
		pMY[0]=1;	pMY[1]=0;	pMY[2]=1;	pMY[3]=1;	pMY[4]=0;
		pMY[5]=1;	pMY[6]=1;	pMY[7]=0;	pMY[8]=1;
		// ---------------------------------------------------------------
		break;
	default:	_ASSERT(0);	// wrong Code Rate
		break;
	}
return(true);
}
// =======================================================================
int CSDR80211a::GetRateBitsByDataRate(int nDataRate)	{
	int nRes;
	switch(nDataRate)
		{
		case 6:		nRes=11;	break;
		case 9:		nRes=15;	break;
		case 12:	nRes=10;	break;
		case 18:	nRes=14;	break;
		case 24:	nRes=9;		break;
		case 36:	nRes=13;	break;
		case 48:	nRes=8;		break;
		case 54:	nRes=12;	break;
		default:	_ASSERT(0);	// wrong Data Rate
			nRes=GLOBAL_ERROR; break;
		}
	return(nRes);
	}
// =======================================================================
