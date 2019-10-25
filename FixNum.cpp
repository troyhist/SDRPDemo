// =======================================================================
// Fixed Bit Capacity Number ver. 1.0
// -----------------------------------------------------------------------
//       MD: 03.12.2002
//       LE: 16.12.2002
// -----------------------------------------------------------------------
// Compiler: MS VC 6.0
// =======================================================================
// FNumber.cpp: implementation of the CFixNum class.
// =======================================================================
#include "stdafx.h"
#include <string.h>			// stricmp (23.12.2002)
#include <ctype.h>			// isdigit (23.12.2002)
#include <crtdbg.h>			// _ASSERT (03.12.2002)
#include <stdlib.h>			// exit	(20.12.2002)
#include <stdio.h>			// sprintf (16.12.2002) only in DEBUG version
#include <math.h>			// fabs (16.12.2002)
#include "FixNum.h"
// =======================================================================
// Precompile definitions (12.12.2002)
// =======================================================================
//#define CFN_USEDEFAULTS		// uncomment this if you want to use default settings for temporary variables (18.12.2002)
#define CFN_DEBUG_CALCERR		// DEBUG: calculate error between double and fixed point results (19.12.2002)
// -----------------------------------------------------------------------
const double CFN_DEBUG_ERRTHR=0.016;	// DEBUG: notify user is a calculation error is greater than this threshold (20.12.2002)
// =======================================================================
// Features ... Changable 
// =======================================================================
const int nDEFBITLEN=24;		// default: number of bits in a number
const int nDEFFRACBITS=6;		// default: number of fractional bits
// -----------------------------------------------------------------------
// Static features
// -----------------------------------------------------------------------
double CFixNum::m_dRescFactor=1.0;		// Default: initialization rescaling factor
// -----------------------------------------------------------------------
// Saturation types
// -----------------------------------------------------------------------
int CFixNum::m_nHandOVF=
CFN_ovf_saturate
//CFN_ovf_zero_saturate
//CFN_ovf_wrapped
//CFN_ovf_warning
//CFN_ovf_stop
;									// default: ovf handling
// -----------------------------------------------------------------------
// Loss number handling (18.12.2002)
// -----------------------------------------------------------------------
int CFixNum::m_nHandLOS=
CFN_los_min
//CFN_los_zero
//CFN_los_warning
//CFN_los_stop
;
// =======================================================================
// DO NOT CHANGE !!!
// =======================================================================
const int CFN_MAXINTBITS=32;		// maximal number of bits in an integer value
const int CFN_ERROR=-1;				// global error. (06.01.2003)
#define FixMaxLength	(CFN_MAXINTBITS)	// compab. to CFix (23.12.2002)
// -----------------------------------------------------------------------
// from CFix class: 
// -----------------------------------------------------------------------
static char *OverflowDescriptions[] =
	{ "saturate", "zero_saturate", "wrap", "warn" };
// -----------------------------------------------------------------------
// defualt: external error handling function (16.12.2002)
// -----------------------------------------------------------------------
int (*CFixNum::m_pErrHandFunc)(
		int nErrCode,				// err code
		char* sRoutineName,			// subroutine name
		char* sMsg,					// message
		int nOpCode,				// arithmetic operation code
		CFixNum* pA,				// first operand
		CFixNum* pB,				// second operand
		CFixNum* pRes				// result
		)=NULL;
// -----------------------------------------------------------------------
inline int imax(int _a, int _b)	{return (_a-_b>0)?_a:_b; }
// =======================================================================
// I/F part adds compatibility to the CFix class (23.12.2002)
// =======================================================================
void CFixNum::set_ovflow(const char *p)	{
// set overflow using a name
// LE: 23.12.2002
int found = false;
for (int i = 0; i < ovf_n_types; i++ )
	{
	if (stricmp(p, OverflowDescriptions[i]) == 0 )
		{
		found = true;
		set_overflow(i);
		break;
		}
	}
// For backward compatibility, support "wrapped" and "warning"
if (stricmp(p, "wrapped") == 0)
	{
	found = true;
	set_overflow(ovf_wrapped);
	}
else
	{
	if (stricmp(p, "warning") == 0)
		{
		found = true;
		set_overflow(ovf_warning);
		}
	}
if (!found) {
	m_nError |= err_invalid;
	}
}
// =======================================================================
int CFixNum::setPrecision(const char * prec_spec)	{
// -----------------------------------------------------------------------
// parse the precision string and set intBits and length.
// no other fields are changed.  Return TRUE if OK, otherwise
// FALSE.
// -----------------------------------------------------------------------
// MD: 23.12.2002
// LE: 23.12.2002
// -----------------------------------------------------------------------
// JW: undefine precision if empty string is given
if (!*prec_spec) {
	//length = intBits = 0;
	Setup(0, 0);
	return(true);
	}
if (!isdigit(*prec_spec))
	return(false);
int first = atoi(prec_spec);
while (*prec_spec && isdigit(*prec_spec))
	prec_spec++;
if ((*prec_spec != '.' && *prec_spec != '/') || !isdigit(prec_spec[1]))
	return(false);
int flag = (*prec_spec == '.');
prec_spec++;
int second = atoi(prec_spec);
// note that we do not check for extra garbage at the end of prec_spec.
if (flag)  // "intBits.fracBits"
	{
	//intBits = first,
	//length  = second + intBits;
	Setup(second + first, second);	// (23.12.2002)
	}
else       // "fracBits/length"
	{
	//length  = second,
	//intBits = length - first;
	Setup(second, first);			// (23.12.2002)
	}
//if ((intBits <= 0) || (length < intBits) || (length > FixMaxLength))
// (23.12.2002)
if ((GetSizeInt() <= 0) ||
	(GetSize() < GetSizeInt()) ||
	(GetSize() > FixMaxLength))
	return(false);
else
	return(true);
}
// =======================================================================
// Construction/Destruction
// =======================================================================
CFixNum::CFixNum(const CFixNum& tFN)	{
	AutoInit();
	_ASSERT(tFN.m_bInited || (!tFN.m_bInited && tFN.m_nNumber==0));
	m_bInited=tFN.m_bInited;
	m_nError=tFN.m_nError;
	m_nNumber=tFN.m_nNumber;
	m_nBitLen=tFN.m_nBitLen;
	m_nFracBits=tFN.m_nFracBits;
	}
// -----------------------------------------------------------------------
CFixNum::CFixNum(int nLen, int nIntBits)	{
	AutoInit(); Setup(nLen, nLen-nIntBits); }
// -----------------------------------------------------------------------
CFixNum::CFixNum(int nLen, int nIntBits, const CFixNum& tFN)
	{
	AutoInit(); Setup(nLen, nLen-nIntBits); 
	*this=tFN.AsFixNum(nLen, nLen-nIntBits);
	}
// -----------------------------------------------------------------------
CFixNum::CFixNum(int nLen, int nIntBits, double a)	{
	AutoInit();	double da=Prescale(a); Setup(nLen, nLen-nIntBits, da); }
// -----------------------------------------------------------------------
CFixNum::CFixNum(int nLen, int nIntBits, int nFracBits, double a)	{
	AutoInit();	double da=Prescale(a);
	Setup(nLen, (nFracBits==CFN_ERROR)?nLen-nIntBits:nFracBits, da); }
// =======================================================================
// default
// =======================================================================
CFixNum::CFixNum()	{
	AutoInit();
	SetupDef(); }
// -----------------------------------------------------------------------
CFixNum::~CFixNum()
	{ }
// =======================================================================
// operators
// =======================================================================
CFixNum& CFixNum::operator += (const CFixNum& tFN)	{
	*this = *this + tFN;
	return *this;
	}
CFixNum& CFixNum::operator -= (const CFixNum& tFN)	{
	*this = *this - tFN;
	return *this;
	}
CFixNum& CFixNum::operator *= (const CFixNum& tFN)	{
	*this = *this * tFN;
	return *this;
	}
// =======================================================================
const CFixNum& CFixNum::operator =(const CFixNum&tFN)
{
// -----------------------------------------------------------------------
// super simple version of the assignment operator
// -----------------------------------------------------------------------
// LE: 03.01.2003
// -----------------------------------------------------------------------
//_ASSERT(IsInited());
_ASSERT(tFN.IsInited());
if(!IsInited())
	{
	AutoInit();
	m_bInited=tFN.m_bInited;
	m_nError=tFN.m_nError;
	m_nNumber=tFN.m_nNumber;
	m_nBitLen=tFN.m_nBitLen;
	m_nFracBits=tFN.m_nFracBits;
	return(*this);
	}
// -----------------------------------------------------------------------
int nIntBitsA=GetSizeInt();
int nIntBitsB=tFN.GetSizeInt();
int nIntBitsBReal=tFN.GetNumOfNZBitsAndSignVS();	// for item
// -----------------------------------------------------------------------
// OVF
if(nIntBitsA<nIntBitsBReal) {
	SetInvalidity(true);
	CFixNum tB=tFN;
	char temp[256];
	sprintf (temp, "tA(%d:%d,%d) <- tB(%d:%d,%d), real (%d:%d,%d) = %lf, %c",
		GetSize(),		GetSizeInt(),		GetSizeFrac(),
		tB.GetSize(),	tB.GetSizeInt(),	tB.GetSizeFrac(),
		nIntBitsBReal+	tB.GetSizeFrac(),	nIntBitsBReal, tB.GetSizeFrac(),
		tB.AsDouble(),	tB.IsInited()?'I':'-');
	ErrHand(CFN_err_ovf, "op.=()", temp, CFN_OC_ASS, this, &tB, this);
	return *this;
	}
// -----------------------------------------------------------------------
// checks number of fractional bits (03.01.2003)
// -----------------------------------------------------------------------
_ASSERT(GetSizeFrac()==tFN.GetSizeFrac());
// -----------------------------------------------------------------------
m_nNumber=tFN.m_nNumber;
// -----------------------------------------------------------------------
return *this;
}
// =======================================================================
CFixNum& CFixNum::operator =(const double &a)	{
	_ASSERT(IsInited());
	RescaleAndSetValue(a); return *this;
	}
CFixNum& CFixNum::operator =(const int &a)		{
	_ASSERT(IsInited());
	RescaleAndSetValue(a); return *this;
	}
CFixNum& CFixNum::operator =(double &a)			{
	_ASSERT(IsInited());
	RescaleAndSetValue(a); return *this;
	}
CFixNum& CFixNum::operator =(int &a)			{
	_ASSERT(IsInited());
	RescaleAndSetValue(a); return *this;
	}
// =======================================================================
// comparsion
// =======================================================================
bool CFixNum::operator==(const CFixNum& a)	{
	return Compare(a) == 0;
	}
bool CFixNum::operator==(const double& a)	{
	return Compare(a) == 0;
	}
bool CFixNum::operator==(const int& a)		{
	return Compare(a) == 0;
	}
bool CFixNum::operator< (const CFixNum& a)	{
	return Compare(a) < 0;
	}
bool CFixNum::operator< (const double& a)	{
	return Compare(a) < 0;
	}
bool CFixNum::operator< (const int& a)		{
	return Compare(a) < 0;
	}
bool CFixNum::operator<=(const CFixNum& a)	{
	return Compare(a) <= 0;
	}
bool CFixNum::operator<=(const double& a)	{
	return Compare(a) <= 0;
	}
bool CFixNum::operator> (const CFixNum& a)	{
	return Compare(a) > 0;
	}
bool CFixNum::operator> (const double& a)	{
	return Compare(a) > 0;
	}
bool CFixNum::operator> (const int& a)		{
	return Compare(a) > 0;
	}
bool CFixNum::operator>=(const CFixNum& a)	{
	return Compare(a) >= 0;
	}
bool CFixNum::operator>=(const double& a)	{
	return Compare(a) >= 0;
	}
bool CFixNum::operator>=(const int& a)		{
	return Compare(a) >= 0;
	}
// =======================================================================
// data conversion
// =======================================================================
CFixNum::operator float()	{
	return((float)AsDouble()); }
CFixNum::operator double()	{
	return(AsDouble()); }
CFixNum::operator int()		{
	return(AsInt()); }
// =======================================================================
// arithmetics
// =======================================================================
CFixNum CFixNum::operator +(const CFixNum &tFN)	{
// -----------------------------------------------------------------------
// Description: performs fixed point addition
//   Parametrs: ...
//      Return: f.p. number
// -----------------------------------------------------------------------
//          MD: 11.12.2002
//          LE: 06.01.2003
// -----------------------------------------------------------------------
	//*
	int nBitsIntA=GetNumOfNZBitsAndSignVS();		// int bits in *this
	int nBitsIntB=tFN.GetNumOfNZBitsAndSignVS();	// int bits in tFN
	int nBitsIntMax=imax(nBitsIntA, nBitsIntB)+1;	// desired number of int bits
	int nBitsFrac;
	CFixNum tA=*this;
	CFixNum tB=tFN;
	CFixNum tR;
// -----------------------------------------------------------------------
_ASSERT(IsInited());					// ERROR (20.12.2002)
_ASSERT(tFN.IsInited());				// ERROR (20.12.2002)
// -----------------------------------------------------------------------
// It's not possible to add numbers with different size of the fractional
// part (06.01.2003)
// -----------------------------------------------------------------------
_ASSERT(GetSizeFrac() == tFN.GetSizeFrac());	// ERROR: (06.01.2003)
// -----------------------------------------------------------------------
// No any shifting required
// -----------------------------------------------------------------------
if (GetSizeFrac() == tFN.GetSizeFrac())
	{
	nBitsFrac=GetSizeFrac();
	_ASSERT(nBitsIntMax + nBitsFrac <= CFN_MAXINTBITS);	// exceed of limits
	tR.Setup(CFN_MAXINTBITS, nBitsFrac);
	tR.m_nNumber=m_nNumber+tFN.m_nNumber;
	// -------------------------------------------------------------------
	}
/*
else
	{
	// -------------------------------------------------------------------
	// Tries to shift second operand
	// -------------------------------------------------------------------
	if (GetSizeFrac() > tFN.GetSizeFrac())
		{
		nBitsFrac=GetSizeFrac();
		_ASSERT(nBitsIntMax + nBitsFrac <= CFN_MAXINTBITS);	// exceed of limits
		tB.ConvertTo(nBitsIntMax + nBitsFrac, nBitsFrac);
		}
	// -------------------------------------------------------------------
	// Tries to shift first operand
	// -------------------------------------------------------------------
	if (GetSizeFrac() < tFN.GetSizeFrac())
		{
		nBitsFrac=tFN.GetSizeFrac();
		_ASSERT(nBitsIntMax + nBitsFrac <= CFN_MAXINTBITS);	// exceed of limits
		tA.ConvertTo(nBitsIntMax + nBitsFrac, nBitsFrac);
		}
	// -------------------------------------------------------------------
	_ASSERT(nBitsIntMax + nBitsFrac <= CFN_MAXINTBITS);	// exceed of limits
	tR.Setup(nBitsIntMax + nBitsFrac, nBitsFrac);
	tR.m_nNumber=tA.m_nNumber+tB.m_nNumber;
	// -------------------------------------------------------------------
	}
// -----------------------------------------------------------------------
if (m_bUseAlignADD)									// 19.12.2002
		tR.ConvertTo(m_nFORMADD[0], m_nFORMADD[2]);
// -----------------------------------------------------------------------
#ifdef CFN_USEDEFAULTS // (18.12.2002)
tR.ConvertTo(m_nDEFBITLEN, m_nDEFFRACBITS);
#endif
//*/
// -----------------------------------------------------------------------
// checks precission error (19.12.2002)
// -----------------------------------------------------------------------
#ifdef CFN_DEBUG_CALCERR
	double dA=tA.AsDouble();
	double dB=tB.AsDouble();
	double dR=tR.AsDouble();
	double dRes=dA+dB;
	double dErr=dR-dRes;
	//_ASSERT(dErr<=0.01);				// error is too great
	if (fabs(dErr)>CFN_DEBUG_ERRTHR)
		cout << "E" << flush;
#endif
// -----------------------------------------------------------------------
return (tR);
}
// =======================================================================
const CFixNum& CFixNum::operator ++()		{
	// MD: 20.12.2002
	// prefix increment. For integer numbers only.
	_ASSERT(IsInited());						// ERROR (20.12.2002)
	_ASSERT(GetSizeFrac()==0);
	m_nNumber++;
	return(*this);
	}
// =======================================================================
const CFixNum CFixNum::operator ++(int)	{
	// MD: 20.12.2002
	// postfix increment. For integer numbers only.
	_ASSERT(IsInited());						// ERROR (20.12.2002)
	_ASSERT(GetSizeFrac()==0);
	CFixNum tFN=*this;
	m_nNumber++;
	return(tFN);
	}
// =======================================================================
CFixNum CFixNum::operator -(const CFixNum &tFN)	{
	_ASSERT(IsInited());						// ERROR (20.12.2002)
	CFixNum tB=tFN;
	tB.m_nNumber*=(-1);
	return(*this+tB);
	}
// =======================================================================
CFixNum CFixNum::operator *(const CFixNum &tFN)	{
// -----------------------------------------------------------------------
// Description: performs fixed point multiplication
//   Parametrs: ...
//      Return: f.p. number
// -----------------------------------------------------------------------
//          MD: 11.12.2002
//          LE: 16.12.2002
// -----------------------------------------------------------------------
	int nBitsIntA, nBitsIntB, nBitsInt;
	int nBitsFrac;
	int nTotalBits;
	int nSign=GetSign()*tFN.GetSign();
	CFixNum tR;
	// -------------------------------------------------------------------
	_ASSERT(IsInited());						// ERROR (20.12.2002)
	_ASSERT(tFN.IsInited());					// ERROR (20.12.2002)
	// -------------------------------------------------------------------
	// check min number of int bits !!!
	nBitsIntA=GetNumOfNZBitsAndSignVS();		// int bits in *this
	nBitsIntB=tFN.GetNumOfNZBitsAndSignVS();	// int bits in tFN
	nBitsInt=nBitsIntA+nBitsIntB-1;				// new value of int bits plus sign
	// -------------------------------------------------------------------
	nBitsFrac=GetSizeFrac()+tFN.GetSizeFrac();
	nTotalBits=nBitsInt+nBitsFrac;				// calculates number of bits in the result
	_ASSERT(nBitsFrac<CFN_MAXINTBITS);			// constrain: frac. part
	_ASSERT(nTotalBits<=CFN_MAXINTBITS);		// constrain: total size
	// -------------------------------------------------------------------
	tR.Setup(nTotalBits, nBitsFrac);			// prepares space for the result, reduced space (16.12.2002)
	tR.m_nNumber=GetAbsNumber()*tFN.GetAbsNumber();
	_ASSERT(tR.m_nNumber>=0);					// algorithm overflow !!!
	tR.m_nNumber*=nSign;						// restores sign
	// -------------------------------------------------------------------
	/*
	// REM: (06.01.2003)
	if (m_bUseAlignMUL)							// 19.12.2002
		tR.ConvertTo(m_nFORMMUL[0], m_nFORMMUL[2]);
	// -------------------------------------------------------------------
	#ifdef CFN_USEDEFAULTS // (18.12.2002)
	tR.ConvertTo(m_nDEFBITLEN, m_nDEFFRACBITS);
	#endif
	//*/
	// -------------------------------------------------------------------
	// this code checks a precission error (11.12.2002)
	// -------------------------------------------------------------------
#ifdef CFN_DEBUG_CALCERR
	double dA=AsDouble();
	double dB=tFN.AsDouble();
	double dR=tR.AsDouble();
	double dRes=dA*dB;
	double dErr=dR-dRes;
	//_ASSERT(dErr<=0.01);				// error is too great
	if (fabs(dErr)>CFN_DEBUG_ERRTHR)
		cout << "E" << flush;
#endif
	// -------------------------------------------------------------------
	return (tR);
	}
// =======================================================================
CFixNum CFixNum::operator /(const CFixNum &tFN)		{
	_ASSERT(IsInited());				// ERROR (20.12.2002)
	_ASSERT(tFN.IsInited());			// ERROR (20.12.2002)
	if (tFN.IsEqualToZero())
		{
		CFixNum tB=tFN;
		ErrHand(CFN_err_dbz, "operator /", "DBZ", CFN_OC_DIV, this, &tB, this);
		}
	_ASSERT(IsEqualToOne());			// divident should be equal to 1.0
	double dVal=AsDouble();
	double dVal2=tFN.AsDouble();
	double dRes=dVal/dVal2;
	int nSizeInt=GetOptNumOfBitsForIntPartAndSign(dRes);
	int nSizeFrac=GetOptNumOfBitsForFracPart(dRes);
	CFixNum tR(nSizeInt + nSizeFrac, nSizeInt, nSizeFrac, dRes);	// (06.01.2003)
	//CFixNum tR(m_nFORMDIV[0], -1, m_nFORMDIV[2], dRes);
	return (tR);
	}
// =======================================================================
CFixNum CFixNum::operator -()					{
	_ASSERT(IsInited());				// ERROR (20.12.2002)
	CFixNum tR(*this);
	tR.m_nNumber*=-1;
	return (tR);
	}
// =======================================================================
// Public functions
// =======================================================================
CFixNum& CFixNum::ConvertTo(int nLen, int nLenFrac)	{
// -----------------------------------------------------------------------
// Description: converts current value into another representation
//   Parametrs: ...
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 18.12.2002
//          LE: 20.12.2002
// -----------------------------------------------------------------------
	_ASSERT(nLen<=CFN_MAXINTBITS);
	_ASSERT(nLenFrac<CFN_MAXINTBITS);
	_ASSERT(nLenFrac<nLen);
	int nRealIntLen=GetNumOfNZBitsAndSignVS();
	if (nRealIntLen>nLen-nLenFrac)
		{
		SetInvalidity(true);
		char temp[256];
		CFixNum tB(nLen, CFN_ERROR, nLenFrac, 0);
		sprintf(temp, "(%d:%d,%d) <== (%d:%d,%d) = %lf real (%d:%d,%d)",
			nLen, nLen-nLenFrac, nLenFrac, 
			GetSize(), GetSizeInt(), GetSizeFrac(),
			AsDouble(),
			nRealIntLen+nLenFrac, nRealIntLen, nLenFrac);
		ErrHand(CFN_err_invalid, "ConvertTo()", temp, -1, this, &tB, this);
		return(*this);
		}
	int nSign=GetSign();
	int nBitMapInt=GetBitMapIntWOSign(nLen-nLenFrac-1);
	int nBitMapFrac=GetBitMapFracWOSign(nLenFrac);
	m_nNumber=(nBitMapInt<<nLenFrac) | nBitMapFrac;
	m_nNumber*=nSign;
	Setup(nLen, nLenFrac);
	return(*this);
	}
// -----------------------------------------------------------------------
CFixNum& CFixNum::ConvertTo(const CFixNum& tFN)	{
	_ASSERT(tFN.IsInited());	// initialization check: (29.01.2003)
	return(ConvertTo(tFN.GetSize(), tFN.GetSizeFrac()));
	}
// =======================================================================
BOOL CFixNum::SetErrHandFunc(int (__cdecl *pErrHand)(
	int nErrCode,					// err code
	char* sRoutineName,				// subroutine name
	char* sMsg,						// message
	int nOpCode,					// arithmetic operation code
	CFixNum* pA,					// first operand
	CFixNum* pB,					// second operand
	CFixNum* pRes					// result
	))	{
	// MD: 16.12.2002
	m_pErrHandFunc=pErrHand;
	return(true);
	}
// =======================================================================
BOOL CFixNum::Setup(int nBitLen, int nFracBits)	{
	_ASSERT(nBitLen>=0);		// negative number of bits !!! (17.12.2002)
	_ASSERT(nFracBits>=0);		// negative number of bits !!! (17.12.2002)
	m_bInited=true;				// 16.12.2002
	//m_nNumber=0;				// rem 16.12.2002
	m_nBitLen=nBitLen;
	m_nFracBits=nFracBits;
	//_ASSERT(m_nBitLen-m_nFracBits>=4 );	// test only (12.12.2002)
	if (nBitLen>CFN_MAXINTBITS)
		{
		SetInvalidity(true);
		ErrHand(CFN_err_invalid, "Setup(int, int)", "invalid bit length (>32)",CFN_OC_SETUP, this, NULL, this);
		return(false);
		}
	if (nFracBits>= CFN_MAXINTBITS)
		{
		SetInvalidity(true);
		ErrHand(CFN_err_invalid, "Setup(int, int)", "wrong number of fractional bits (>=32)",CFN_OC_SETUP, this, NULL, this);
		return(false);
		}
	if (nFracBits>=nBitLen)
		{
		SetInvalidity(true);
		ErrHand(CFN_err_invalid, "Setup(int, int)", "fractional part is large than the total length (>=32)",CFN_OC_SETUP, this, NULL, this);
		return(false);
		}
	return(true);
	}
// -----------------------------------------------------------------------
BOOL CFixNum::Setup(int pLens[3])	{
	return(Setup(pLens[0], pLens[2]));
	}
// =======================================================================
BOOL CFixNum::SetupAsInt(int nLenInt)	{
	return(Setup(nLenInt, 0));
	}
// -----------------------------------------------------------------------
BOOL CFixNum::SetupFrom(const CFixNum &tFN)	{
	_ASSERT(tFN.IsInited());	// initialization check (29.01.2003)
	return(Setup(tFN.GetSize(), tFN.GetSizeFrac()));
	}
// =======================================================================
// Private functions
// =======================================================================
CFixNum CFixNum::AsFixNum(int nLen, int nLenFrac)	const{
// -----------------------------------------------------------------------
// Description: returns converted current value as FixNum with given parametrs
//   Parametrs: ...
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 11.12.2002
//          LE: 16.12.2002
// -----------------------------------------------------------------------
	_ASSERT(nLen<=CFN_MAXINTBITS);
	_ASSERT(nLenFrac<CFN_MAXINTBITS);
	_ASSERT(nLenFrac<nLen);
	CFixNum tFN(nLen, CFN_ERROR, nLenFrac, 0);
	int nSign=GetSign();
	int nBitMapInt=GetBitMapIntWOSign(nLen-nLenFrac-1);
	int nBitMapFrac=GetBitMapFracWOSign(nLenFrac);
	tFN.m_nNumber=(nBitMapInt<<nLenFrac) | nBitMapFrac;
	tFN.m_nNumber*=nSign;
	//tFN=*this;
	return(tFN);
	}
// -----------------------------------------------------------------------
CFixNum CFixNum::AsFixNum(const CFixNum& tFN) const{
	_ASSERT(tFN.IsInited());	// initialization check: (29.01.2003)
	return(AsFixNum(tFN.GetSize(), tFN.GetSizeFrac()));
	}
// =======================================================================
double CFixNum::AsDouble() const	{
	int nSign=GetSign();
	double dPartInt=CalcPartInt();
	double dPartFrac=CalcPartFrac();
	double dRes=dPartInt+dPartFrac;
	dRes*=nSign;
	return(dRes*m_dRescFactor);
	}
// -----------------------------------------------------------------------
int CFixNum::AsInt() const			{
	double da=AsDouble();
	int nRes=GetPartIntOf(da);
	//if (GetPartFracOf(da)>=0.5)	nRes++;	// rounding, REM 19.12.2002
	return(nRes);
	}
// =======================================================================
BOOL CFixNum::AutoInit()
{
// -----------------------------------------------------------------------
// Description: inits internal data of the class
//   Parametrs: ...
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 09.12.2002
//          LE: 16.12.2002, 07.01.2003
// -----------------------------------------------------------------------
// ERROR: Call back function is not defined (16.12.2002)
// -----------------------------------------------------------------------
_ASSERT((m_nHandOVF!=CFN_ovf_warning)||
		((m_nHandOVF==CFN_ovf_warning)&&(m_pErrHandFunc!=NULL)));	// (16.12.2002)
// -----------------------------------------------------------------------
_ASSERT(nDEFBITLEN<=CFN_MAXINTBITS);	// wrong initialisation of the default variables
//_ASSERT(CFN_DEFINTBITS>=CFN_MININTBITS);
m_bInited=false;
m_nError=0;
m_nNumber=0;		// 16.12.2002
roundFlag=false;	// DUMMY - only for compability (07.01.2003)
return(true);
}
// =======================================================================
BOOL CFixNum::AutoSetupFromNumber(double a)
{
// -----------------------------------------------------------------------
// Description: adjusts class parametrs for a given number
//   Parametrs: ...
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 09.12.2002
//          LE: 16.12.2002
// -----------------------------------------------------------------------
int nSign=GetSignOf(a);
double dUA=a*nSign;
int nFracBits;
int nIntBits=GetOptNumOfBitsForIntPartAndSign(dUA);
// -----------------------------------------------------------------------
_ASSERT(nIntBits<=CFN_MAXINTBITS);				// max 31 bits + sign;
_ASSERT(nIntBits+nDEFFRACBITS<=CFN_MAXINTBITS);	// checks size of integer and fractional parts
// -----------------------------------------------------------------------
//nFracBits=CFN_IMFRACBITS;						// sets default value
nFracBits=GetOptNumOfBitsForFracPart(dUA);		// calculates optimal
if (nFracBits<nDEFFRACBITS)
	nFracBits=nDEFFRACBITS;
_ASSERT(nFracBits<12);						// test only
nIntBits=CFN_MAXINTBITS-nFracBits;
_ASSERT(nIntBits>8);						// test only
// -----------------------------------------------------------------------
int nValInt=GetPartIntOf(dUA);
int nValFrac=GetPartFracBitOf(dUA, nFracBits);
// -----------------------------------------------------------------------
m_nNumber=(nValInt<<nFracBits) | nValFrac;
m_nNumber*=nSign;
m_nBitLen=CFN_MAXINTBITS;
m_nFracBits=nFracBits;
m_bInited=true;								// inited (16.12.2002)
return(true);
}
// =======================================================================
double CFixNum::CalcPartFrac() const	{
// -----------------------------------------------------------------------
// Description: calculates fractional part of the current number as a double value
//   Parametrs: ...
//      Return: value
// -----------------------------------------------------------------------
//          MD: 09.12.2002
//          LE: 09.12.2002
// -----------------------------------------------------------------------
int nFracBits=GetSizeFrac();
int nSign=GetSign();
int nNumber=GetAbsNumber();		// unsigned number
int nCompVal;
double dRes=0;
// -----------------------------------------------------------------------
if(!nFracBits) return(0);
// -----------------------------------------------------------------------
for (int i=0; i<nFracBits; i++)
	{
	int nCurPos=nFracBits-i-1;
	nCompVal=1<<nCurPos;
	if (nNumber&nCompVal)
		{
		int nPow2=1<<(i+1);
		double dInv=1.0/nPow2;
		dRes+=dInv;
		}
	}
return(dRes);
}
// =======================================================================
int CFixNum::CalcPartInt() const {
// -----------------------------------------------------------------------
// Description: calculates integer part of the current number as a double value
//   Parametrs: ...
//      Return: value
// -----------------------------------------------------------------------
//          MD: 09.12.2002
//          LE: 09.12.2002
// -----------------------------------------------------------------------
	int nFracBits=GetSizeFrac();
	int nSign=GetSign();
	int nNumber=GetAbsNumber();
	int nPartInt=(nNumber>>nFracBits);
	return(nPartInt);
	}
// =======================================================================
BOOL CFixNum::Compare(const CFixNum &tFN)
{
// -----------------------------------------------------------------------
// Description: compares current fixed point number with given number
//   Parametrs: ...
//      Return: value <0: -1, value=0: 0, value >0: 1
// -----------------------------------------------------------------------
//          MD: 06.12.2002
//          LE: 11.12.2002
// -----------------------------------------------------------------------
int nBitsIntA=GetNumOfNZBitsAndSignVS();		// int bits in *this
int nBitsIntB=tFN.GetNumOfNZBitsAndSignVS();	// int bits in tFN
int nMaxBitsInt=imax(nBitsIntA, nBitsIntB);		// max
nMaxBitsInt++;									// to prevent overflow
CFixNum tR(CFN_MAXINTBITS, nMaxBitsInt, CFN_ERROR, 0);	// (WARNING) (06.01.2003)
CFixNum tA=AsFixNum(CFN_MAXINTBITS, CFN_MAXINTBITS-nMaxBitsInt);		//	corrected a bug
CFixNum tB=tFN.AsFixNum(CFN_MAXINTBITS, CFN_MAXINTBITS-nMaxBitsInt);	//	corrected a bug
// -----------------------------------------------------------------------
int diff=tA.m_nNumber-tB.m_nNumber;
if (diff < 0) return -1;
return (diff > 0);
}
// -----------------------------------------------------------------------
BOOL CFixNum::Compare(const double &a)
	{ double diff = AsDouble() - a; if (diff < 0) return -1;
	return (diff > 0);}
// -----------------------------------------------------------------------
BOOL CFixNum::Compare(const int &a)
	{ double diff = AsInt() - a; if (diff < 0) return -1;
	return (diff > 0); }
// =======================================================================
BOOL CFixNum::ErrHand(int nErrCode, char* sRoutine, char *sMsg, 
					  int nOpCode,
					  CFixNum* pA,
					  CFixNum* pB,
					  CFixNum* pRes)
{
// -----------------------------------------------------------------------
// Description: errors handler
//   Parametrs: nErrCode	- error code
//				sRoutine	- sub routine name
//				sMsg		- optional msg
//				nOpCode		- arithmetic operation code
//				tA, tB		- rreferences to operands
//				tRes		- reference to the result
//      Return: value
// -----------------------------------------------------------------------
//          MD: 10.12.2002
//          LE: 16.12.2002, 18.12.2002
// -----------------------------------------------------------------------
m_nError|=nErrCode;
// -----------------------------------------------------------------------
switch (nErrCode)
	{
case CFN_err_ovf:
	// -------------------------------------------------------------------
	switch(m_nHandOVF)
		{
		cout << "^" << flush;
		case CFN_ovf_saturate:
			cout << "OVF: " << sRoutine << ": "<< sMsg << endl;
			pRes->SetSaturation(pB->GetSign());
			break;
		case CFN_ovf_zero_saturate:
			pRes->SetSaturationZero();
			break;
		case CFN_ovf_wrapped:
			*pRes=pB->AsFixNum(pA->GetSize(), pA->GetSizeFrac());
			break;
		case CFN_ovf_warning:
			m_pErrHandFunc(nErrCode, sRoutine, sMsg, nOpCode, pA, pB, pRes);
			break;
		case CFN_ovf_stop:
			cout << "OVF: " << sRoutine << ": "<< sMsg << endl;
			_ASSERT(0);
			break;
		default:
			_ASSERT(0);
			break;
		};
	break;
	// -------------------------------------------------------------------
case CFN_err_dbz:
	if (m_pErrHandFunc)
		m_pErrHandFunc(nErrCode, sRoutine, sMsg, nOpCode, pA, pB, pRes);
	_ASSERT(0);		// not ready yet
	break;
// -----------------------------------------------------------------------
case CFN_err_loss:
	// -------------------------------------------------------------------
	switch(m_nHandLOS)
		{
		cout << "!" << flush;
		case CFN_los_min:
			// MIN: set minimal possible positive number
			//cout << "LOSS: " << sRoutine << ": "<< sMsg << endl;
			pRes->m_nNumber=1;				// sets minimal positive value
			break;
		case CFN_los_zero:
			// ZERO: keep data loss As Is
			//cout << "LOSS: " << sRoutine << ": "<< sMsg << endl;
			pRes->m_nNumber=0;
			break;
		case CFN_los_warning:
			m_pErrHandFunc(nErrCode, sRoutine, sMsg, nOpCode, pA, pB, pRes);
			break;
		case CFN_los_stop:
			cout << "LOSS: " << sRoutine << ": "<< sMsg << endl; 
			_ASSERT(0);
			break;
		default:
			_ASSERT(0);
			break;
		};
	break;
// -----------------------------------------------------------------------
case CFN_err_invalid:
	if (pA->m_nBitLen>CFN_MAXINTBITS)
		pRes->m_nBitLen=CFN_MAXINTBITS;
	if (pA->m_nFracBits>=CFN_MAXINTBITS)
		pRes->m_nFracBits=CFN_MAXINTBITS-1;
	pRes->m_nError=0;
	pRes->m_bInited=0;
	pRes->m_nNumber=0;	// is it necessary ??? (16.12.2002)
	cout << "INV: " << sRoutine << ": "<< sMsg << endl; 
	_ASSERT(0);			// !!!
	break;
default:
	_ASSERT(0);			// unknown error !
	break;
	}
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
double CFixNum::FindMax(int ln, int ib) const	{
	double dP1=(unsigned)(1<<(ib-1));
	double dP2=1<<(ln-ib);
	return(dP1-1.0/dP2);
    //return twoRaisedTo[ib-1] - 1.0 / twoRaisedTo[ln - ib];
	}
// =======================================================================
double CFixNum::FindMin(int , int ib) const		{
	double dP1=unsigned(1<<(ib-1));
	return (-dP1);
    //return -twoRaisedTo[ib-1];
	}
// =======================================================================
int CFixNum::GetAbsNumber()	const {
	return(m_nNumber>=0?m_nNumber:-m_nNumber);
	}
// =======================================================================
unsigned int CFixNum::GetBitMapFracWOSign(int nLen) const	{
// -----------------------------------------------------------------------
// Description: returns bitmap of given length of the fractional part
//   Parametrs: ...
//      Return: value
// -----------------------------------------------------------------------
//          MD: 11.12.2002
//          LE: 18.12.2002
// -----------------------------------------------------------------------
	unsigned int nNumber;
	int nDiff;
	int nLenBInt=GetSizeInt();
	int nLenBFrac=GetSizeFrac();
	//int nShiftInt=CFN_MAXINTBITS-nLenBFrac;
	nNumber=GetAbsNumber();
	//nNumber=(nNumber<<nShiftInt)>>nShiftInt;	// BUG: (20.12.2002)
	nNumber=nNumber&GetBitMask(nLenBFrac);
	nDiff=nLen-nLenBFrac;
	if (nDiff>0)
		nNumber=nNumber<<nDiff;		
	if (nDiff<0)
		nNumber=nNumber>>-nDiff;
	return(nNumber);
	}
// =======================================================================
unsigned int CFixNum::GetBitMapIntWOSign() const	{
	unsigned int nNumber;
	nNumber=GetAbsNumber();
	nNumber=nNumber>>GetSizeFrac();
	return(nNumber);
	}
// =======================================================================
unsigned int CFixNum::GetBitMapIntWOSign(int nLen) const	{
	_ASSERT(nLen<=CFN_MAXINTBITS);
	unsigned int nBitMask=0;
	unsigned int nNumber;
	nNumber=GetAbsNumber();
	nNumber=nNumber>>GetSizeFrac();
	for (int i=0; i<nLen; i++) nBitMask|= (1<<i);
	nNumber=nNumber&nBitMask;
	return(nNumber);
	}
// =======================================================================
unsigned int CFixNum::GetBitMask(int nSize) const	{
// -----------------------------------------------------------------------
// Description: returns a sequence of "one"s bits of given length
//   Parametrs: ...
//      Return: value
// -----------------------------------------------------------------------
//          MD: 20.12.2002
//          LE: 20.12.2002
// -----------------------------------------------------------------------
	_ASSERT(nSize<=CFN_MAXINTBITS);
	unsigned int nBitMask=0;
	for (int i=0; i<nSize; i++) nBitMask|= (1<<i);
	return(nBitMask);
	}
// =======================================================================
double CFixNum::GetMax() const {
	return(FindMax(m_nBitLen, GetSizeInt()));
	}
double CFixNum::GetMin() const {
	return(FindMin(m_nBitLen, GetSizeInt()));
	}
// =======================================================================
int CFixNum::GetNumOfNZBitsAndSignVS() const
{
// -----------------------------------------------------------------------
// ...VS - version for signed (with signum bit) numbers
// -----------------------------------------------------------------------
// Description: returns number of non-zero bits in integer part (includes sign bit)
//   Parametrs: ...
//      Return: ...
// -----------------------------------------------------------------------
//          MD: 10.12.2002
//          LE: 11.12.2002
// -----------------------------------------------------------------------
int nNum=GetAbsNumber()>>GetSizeFrac();
// -----------------------------------------------------------------------
int nStart=GetSizeInt()-1;		// excludes sign bit
int nZeroStartBits=0;
for (int i=nStart; i>=0; i--)
	{
	int nPow2=1<<i;
	int nVal=nNum&nPow2;
	if (nVal) break;
	nZeroStartBits++;
	}
//return(m_nIntBits-nZeroStartBits+1);
return(GetSizeInt()-nZeroStartBits+1);
}
// =======================================================================
int CFixNum::GetOptNumOfBitsForFracPart(double dNum)	{
// -----------------------------------------------------------------------
// Description: returns number of bits to represent a fractional part of a given number
//   Parametrs: ...
//      Return: value
// -----------------------------------------------------------------------
//          MD: 09.12.2002
//          LE: 09.12.2002
// -----------------------------------------------------------------------
double dfa=GetPartFracOf(dNum);
double dVal=0;
double dInv;
int nFracBits=0;
int nPow2;
// -----------------------------------------------------------------------
if (dfa==0.0) return(0);
// -----------------------------------------------------------------------
for (int i=0; i<CFN_MAXINTBITS-1; i++)
	{
	nPow2=1<<(CFN_MAXINTBITS-i-2);
	dInv=1.0/(double)nPow2;
	dVal=dVal+dInv;
	if (dVal>dfa)
		{
		nFracBits=CFN_MAXINTBITS-i-2;
		break;
		}
	}
// -----------------------------------------------------------------------
return(nFracBits);
}
// =======================================================================
int CFixNum::GetOptNumOfBitsForIntPartAndSign(double dNum)	{
// -----------------------------------------------------------------------
// Description: returns number of bits to represent an integer part of a given number
//   Parametrs: ...
//      Return: value
// -----------------------------------------------------------------------
//          MD: 09.12.2002
//          LE: 09.12.2002
// -----------------------------------------------------------------------
int nNum=(int)dNum;
// -----------------------------------------------------------------------
int nStart=CFN_MAXINTBITS-1;		// excludes sign bit
int nZeroStartBits=0;
for (int i=nStart; i>=0; i--)
	{
	int nPow2=1<<i;
	int nVal=nNum&nPow2;
	if (nVal) break;
	nZeroStartBits++;
	}
return(CFN_MAXINTBITS-nZeroStartBits+1);
}
// =======================================================================
int CFixNum::GetPartFracBitOf(double a, int n)	{
// -----------------------------------------------------------------------
// Description: returns n bits for the fractional part
//   Parametrs: ...
//      Return: value
// -----------------------------------------------------------------------
//          MD: 09.12.2002
//          LE: 09.12.2002
// -----------------------------------------------------------------------
double dfa=GetPartFracOf(a);
double dVal=0;
double dTemp, dInv;
int nRes=0;
int nCurPos;
int nPow2;
// -----------------------------------------------------------------------
for (int i=0; i<n; i++)
	{
	nCurPos=n-1-i;
	nPow2=1<<(i+1);
	dInv=1.0/nPow2;
	dTemp=dVal+dInv;
	if (dTemp<=dfa)
		{
		nRes=nRes | (1<<nCurPos);
		dVal=dTemp;
		}
	}
// -----------------------------------------------------------------------
return(nRes);
}
// =======================================================================
double CFixNum::GetPartFracOf(double a)	const	{
	int na=(int)a;
	double da=na;
	return(a-da);
	}
int CFixNum::GetPartIntOf(double a)	const		{
	int na=(int)a; return(na);
	}
// =======================================================================
int CFixNum::GetSign() const		{
	return(m_nNumber>=0)?1:-1;
	}
int CFixNum::GetSignOf(double a)	{
	return(a>=0)?1:-1;
	}
int CFixNum::GetSignOf(int a)		{
	return(a>=0)?1:-1;
	}
// =======================================================================
double CFixNum::GetStep()			{
// -----------------------------------------------------------------------
// Description: returns minimal difference (step) between two closest numbers
//   Parametrs: ...
//      Return: ...
// -----------------------------------------------------------------------
//          MD: 13.12.2002
//          LE: 13.12.2002
// -----------------------------------------------------------------------
	return (double) (1.0/(1<<GetSizeFrac()));
	}
// =======================================================================
BOOL CFixNum::IsEqualToOne()	{
// -----------------------------------------------------------------------
// Description: returns true, if an internal value is equal to 1.0 or -1.0
//   Parametrs: ...
//      Return: ...
// -----------------------------------------------------------------------
//          MD: 12.12.2002
//          LE: 12.12.2002
// -----------------------------------------------------------------------
	if (GetBitMapFracWOSign(GetSizeFrac())) return(false);
	return(GetBitMapIntWOSign()==1);
	}
// =======================================================================
BOOL CFixNum::IsEqualToZero() const	{
	return(m_nNumber==0);
	}
// =======================================================================
BOOL CFixNum::IsFitInRange(double dNumber)	{
// -----------------------------------------------------------------------
// Description: returns true, if given value is fit in the range
//   Parametrs: ...
//      Return: ...
// -----------------------------------------------------------------------
//          MD: 04.12.2002
//          LE: 09.12.2002
// -----------------------------------------------------------------------
double dMax=GetMax();
double dMin=GetMin();
// -----------------------------------------------------------------------
if (dNumber<dMin || dNumber>dMax) 
	{
	GetMax();
	GetMin();
	return(false);
	}
return(true);
}
// =======================================================================
BOOL CFixNum::IsInited() const		{
	return(m_bInited);
	}
// =======================================================================
double CFixNum::Prescale(double a)	{
	return(a/m_dRescFactor);
	}
// =======================================================================
BOOL CFixNum::SetInvalidity(BOOL bInv)	{
// -----------------------------------------------------------------------
// Description: sets or resets invalidity flag
//   Parametrs: ...
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 06.01.2003
//          LE: 06.01.2003
// -----------------------------------------------------------------------
if (bInv)
	m_nError|=err_invalid;
else
	m_nError&=(~err_invalid);
return(true);
}
// =======================================================================
BOOL CFixNum::SetSaturation(int nSign)	{
// -----------------------------------------------------------------------
// Description: sets maximal or minimal value 
//   Parametrs: nSign	- signum (1 or -1)
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 10.12.2002
//          LE: 10.12.2002
// -----------------------------------------------------------------------
m_nNumber=0;
// -----------------------------------------------------------------------
for (int i=0; i<m_nBitLen-1; i++)
	m_nNumber|= (1<<i);
m_nNumber*=nSign;
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CFixNum::SetSaturationZero()	{
	m_nNumber=0;
	return(true);
	}
// =======================================================================
BOOL CFixNum::Setup(int nLen, int nFracBits, double a)
{
// -----------------------------------------------------------------------
// Description: setups class
//   Parametrs: nLen, nInteBits	- no comments
//				a				- signed rescaled value
//      Return: true - success, false - error
// -----------------------------------------------------------------------
//          MD: 09.12.2002
//          LE: 16.12.2002, 18.12.2002, 06.01.2003
// -----------------------------------------------------------------------
int nSign=GetSignOf(a);
double dUA=a*nSign;
int nIntBits=nLen-nFracBits;			// number of 'int' bits (18.12.2002)
int nRealIntBits=GetOptNumOfBitsForIntPartAndSign(dUA);
//int nRealFracBits=GetOptNumOfBitsForFracPart(dUA);	// (18.12.2002)
// -----------------------------------------------------------------------
_ASSERT(nLen<=CFN_MAXINTBITS);			// max 31 bits + sign;
_ASSERT(nFracBits<nLen);				// checks # of fractional bits;
// -----------------------------------------------------------------------
//_ASSERT(nRealIntBits<=nIntBits);		// overflow !!! (18.12.2002), replaced by the following code:
if (nRealIntBits>nIntBits)				// OVF: (06.01.2003)
	{
	char temp[256];
	int nRealFracBits=GetOptNumOfBitsForFracPart(dUA);
	sprintf (temp, "(%d:%d,%d) = %lf (%d:%d,%d)",
		nLen, nIntBits, nFracBits, a,
		nRealIntBits+nRealFracBits, nRealIntBits, nRealFracBits);
	ErrHand(CFN_err_ovf, "Setup(..)", temp, CFN_OC_SETUP, this, this, this);
	return(false);
	}
// -----------------------------------------------------------------------
//_ASSERT(nRealFracBits<=nFracBits);	// test: digit is lost (18.12.2002)
_ASSERT(nRealIntBits+nFracBits<=nLen);	// checks necessary # of integer bits
// -----------------------------------------------------------------------
//_ASSERT(nLen-nFracBits>=4);			// test only (12.12.2002)
int nBitmapInt=GetPartIntOf(dUA);
int nBitmapFrac=GetPartFracBitOf(dUA, nFracBits);
// -----------------------------------------------------------------------
m_nNumber=(nBitmapInt<<nFracBits) | nBitmapFrac;
m_nNumber*=nSign;
m_nBitLen=nLen;
m_nFracBits=nFracBits;
m_bInited=true;							// 16.12.2002
// -----------------------------------------------------------------------
// number is lost (18.12.2002)
if (dUA!=0 && m_nNumber==0)
	{
	char temp[256];
	int nRealFracBits=GetOptNumOfBitsForFracPart(dUA);
	sprintf (temp, "(%d:%d,%d) = %lf (%d:%d,%d)",
		nLen, nIntBits, nFracBits, a,
		nRealIntBits+nRealFracBits, nRealIntBits, nRealFracBits);
	ErrHand(CFN_err_loss, "Setup(..)", temp, CFN_OC_SETUP, this, NULL, this);
	}
// -----------------------------------------------------------------------
return(true);
}
// =======================================================================
BOOL CFixNum::SetupDef()	{
	m_bInited=false;					// 16.12.2002
	m_nError=0;
	m_nNumber=0;
	m_nBitLen=nDEFBITLEN;
	m_nFracBits=nDEFFRACBITS;
	return(true);
	}
// =======================================================================
BOOL CFixNum::RescaleAndSetValue(double a)	{
	double da=Prescale(a);
	//_ASSERT(IsFitInRange(da));	// replaced bz the following code (06.01.2003)
	if (!IsFitInRange(da))
		{
		char temp[256];
		double dUA=da*GetSignOf(da);
		int nOptSizeFrac=GetOptNumOfBitsForFracPart(dUA);
		int nOptSizeInt=GetOptNumOfBitsForIntPartAndSign(dUA);
		sprintf (temp, "(%d:%d,%d) = %lf (%d:%d,%d) (size doesn't fit)",
			GetSize(), GetSizeInt(), GetSizeFrac(), a,
			nOptSizeInt+nOptSizeFrac, nOptSizeInt, nOptSizeFrac);
		ErrHand(CFN_err_ovf, "RescaleAndSetValue(..)", temp, CFN_OC_ASS, this, this, this);
		return(false);
		}
	Setup(m_nBitLen, GetSizeFrac(), da);
	return(true);
	}
// =======================================================================
// Friend functions
// =======================================================================
double fabs(CFixNum tFN)
	{ return(tFN.AsDouble()*tFN.GetSign()); }
// =======================================================================
ostream& operator<< (ostream& s, const CFixNum& x)	{
	// DUMMY: copied from Fix.cpp
	// LE: 07.01.2003
	if (x.invalid()) {
	s << "(Invalid:";
	if ((x.m_nError & CFixNum::err_dbz) != 0) s << " DBZ";
	if ((x.m_nError & CFixNum::err_invalid) != 0) s << " Bad Params";
	s << ")";
    }
    else {
	s << "(" << x.value() << ", "
	  << x.intb() << "." << x.precision() << ")";
    }
    return s;}
// =======================================================================
// Arithmetic: friends
// =======================================================================
// Operators: friend
// =======================================================================
CFixNum operator/ (const double& a, const CFixNum& tFN)	{
	return(CFixNum(32, 32, 0, a)/tFN);
	}
CFixNum operator/ (const int& a, const CFixNum& tFN)	{
	return(CFixNum(32, 32, 0, a)/tFN);
	}
// =======================================================================
void printFix(const CFixNum& x)							{
	// DUMMY: copied from Fix.cpp
	// LE: 07.01.2003
	cout << "Bits(hex) = ";
  
  cout << "\nlength = " << x.len() << ", ";
  cout << "intBits = " << x.intb() << ", ";
  cout << (x.roundMode() ? "round, " : "truncate, ");
  cout << "errors = ";
  if (x.invalid()) cout << "bad params, ";
  else if (x.dbz()) cout << "divide by zero, ";
  else if (x.ovf_occurred()) cout << "overflow occurred, ";
  else cout << "none, ";
  char *overflowStr;
  int overflowType = x.overflow();
  if ( overflowType < 0 || overflowType >= CFixNum::ovf_n_types )
    overflowStr = "not valid";
  else
    overflowStr = OverflowDescriptions[overflowType];
  cout << "overflow  = " << overflowStr << "\n";

  cout << "value     = " << x.value() << "\n";
	}
// =======================================================================
