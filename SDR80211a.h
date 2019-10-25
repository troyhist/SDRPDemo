// =======================================================================
// SDR 802.11a blocks ver. 1.0
// set of functions to process signals in the IEEE 802.11a standart
// -----------------------------------------------------------------------
//       MD: 09.01.2003
//       LE: 09.01.2003
// -----------------------------------------------------------------------
// Compiler: MS VC 6.0
// =======================================================================
// SDR80211a.h: interface for the CSDR80211a class.
// =======================================================================
#if !defined(AFX_SDR80211A_H__AF342B87_6450_4EB1_97AC_718EB5C967AE__INCLUDED_)
#define AFX_SDR80211A_H__AF342B87_6450_4EB1_97AC_718EB5C967AE__INCLUDED_
// =======================================================================
#include "DataTypes.h"
// -----------------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// =======================================================================
// CONSTANTS ... DO NOT CHANGE (20.01.2003)
// =======================================================================
// modulation types
// -----------------------------------------------------------------------
const int CSDR_MODULBPSK=1;
const int CSDR_MODULQPSK=2;
const int CSDR_MODUL16QAM=3;
const int CSDR_MODUL64QAM=4;
// -----------------------------------------------------------------------
// code rates (20.01.2003)
// -----------------------------------------------------------------------
const int CSDR_CRATE12=1;	// code rate 1/2
const int CSDR_CRATE23=2;	// code rate 2/3
const int CSDR_CRATE34=3;	// code rate 3/4
// =======================================================================
class CSDR80211a  
{
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
public:
	static BOOL CreatePacket(int nDataRate, int nLen, CVectorBool& pData, CVectorFloat &pPackR, CVectorFloat &pPackI);
	static BOOL Conv64FDToTD(CVectorFloat& pFDr, CVectorFloat& pFDi, CVectorFloat& pTDr, CVectorFloat& pTDi);	// performs IFFT and returns a cyclically extended signal in the time domain
	static BOOL DataConvToFD(CVectorBool&x, CVectorFloat& pSr, CVectorFloat& pSi, int nModulType, int pPilPolar);	// modulates a block of values (16.01.2003)
	static BOOL DataIntleav(CVectorBool&x, CVectorBool&y, int nDataRate);
	static BOOL DateEncode(CVectorBool&x, CVectorBool&y, int nDataRate);
	static BOOL DataScramble(CVectorBool&x, CVectorBool&y);							// scrambles input array with predefined scrambling key (16.01.2003)
	static BOOL DataScramble(CVectorBool &x, CVectorBool &y, CVectorBool& pState);	// scrambles input array with predefined scrambling key (24.01.2003)
	static BOOL ReorderVector64(CVectorFloat&x, CVectorFloat&y);
	static BOOL GenerateLongSequenceFD(CVectorFloat& pLSr, CVectorFloat& pLSi);		// generates a long sequence in a time domain (14.01.2003)
	static BOOL GenerateLongSequenceTD(CVectorFloat& pLSr, CVectorFloat& pLSi);		// generates a long sequence in a frequency domain (14.01.2003)
	static BOOL GenerateShortSequenceFD(CVectorFloat& pSSr, CVectorFloat& pSSi);	// generates a short sequence in a frequency domain
	static BOOL GenerateShortSequenceTD(CVectorFloat& pSTr, CVectorFloat& pSTi);	// generates a short sequence in a time domain
	static CVectorBool CreateFieldSIGNALbin(int nDataRate, int nLen);					// creates field SIGNAL as a binary vector
	static BOOL CreateFieldSIGNALfd(int nDataRate, int nLen, CVectorFloat& pSI, CVectorFloat& pSQ);		// creates field SIGNAL in freq domain with given parametrs
	static BOOL CreateFieldSIGNALtd(int nDataRate, int nLen, CVectorFloat& pTDr, CVectorFloat& pTDi);	// creates field SIGNAL in time domain with given parametrs
	static CVectorBool GetDummyData();		// generates dummy data array (as a binary vector)
	CSDR80211a();
	virtual ~CSDR80211a();
private:
	static CVectorBool CreateUnencodedFieldSIGNAL(int nRate, int nLen);								// creates unencoded field SIGNAL with given parametrs (09.01.2003)
	static BOOL InsertPilotsAndZero(CVectorFloat &iI, CVectorFloat &iQ, CVectorFloat &oI, CVectorFloat &oQ, int pPilPolar);	// inserts 4 pilot subcarriers and a zero at (0) (10.01.2003)
	static BOOL CyclExt(CVectorFloat &x, CVectorFloat &y, int nTailSize, int nNewSize);				// cyclically extends a signal in the time domain (15.01.2003)
	static int GetRateBitsByDataRate(int nDataRate);	// returns code to represent given data rate in the SIGNAL field (20.01.2003)
protected:
	static BOOL AppendDataSymbolToChain(CVectorFloat& pChain, CVectorFloat& pSymbol);	// appends an OFDM data symbol to the whole packet chain (20.01.2003)
	static int GetCodeRateByDataRate(int nDataRate);	// returns code rate for given Rate value (20.01.2003)
	static int GetModulTypeByDataRate(int nDataRate);	// returns modulation type for given Rate value (20.01.2003)
	static int GetNbpscByDataRate(int nDataRate);		// returns Nbpsc for given Rate value (20.01.2003)
	static int GetNcbpsByDataRate(int nDataRate);		// returns Ncbps for given Rate value (20.01.2003)
	static int GetNdbpsByDataRate(int nDataRate);		// returns Ndbps for given Rate value (20.01.2003)
	static int GetPilotPolarity(int nIdx);				// returns polarity of the pilot signal with given idx (20.01.2003)
	static BOOL GetPunctMaskByCodeRate(int nCodeRate, CVectorBool& pMX, CVectorBool& pMY);	// returns puncturing masks for differen code rates (20.01.2003)
};
// =======================================================================
#endif // !defined(AFX_SDR80211A_H__AF342B87_6450_4EB1_97AC_718EB5C967AE__INCLUDED_)
// =======================================================================
