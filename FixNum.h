// =======================================================================
// Fixed Bit Capacity Number ver. 1.0
// -----------------------------------------------------------------------
//       MD: 03.12.2002
//       LE: 16.12.2002
// -----------------------------------------------------------------------
// Compiler: MS VC 6.0
// =======================================================================
// FixNum.h: interface for the CFixNum class.
// =======================================================================
#if !defined(AFX_FNUMBER_H__085DA7E5_6506_40E3_B8DB_6A96595324D0__INCLUDED_)
#define AFX_FNUMBER_H__085DA7E5_6506_40E3_B8DB_6A96595324D0__INCLUDED_
// =======================================================================
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// =======================================================================
#include <iostream.h>			// (04.12.2002)
// =======================================================================
// some constants (10.12.2002)
// -----------------------------------------------------------------------
// codes of handling of "overflow"
// -----------------------------------------------------------------------
const int CFN_ovf_saturate = 0;
const int CFN_ovf_zero_saturate = 1;
const int CFN_ovf_wrapped = 2;
const int CFN_ovf_warning = 3;
const int CFN_ovf_stop    = 4;
// -----------------------------------------------------------------------
// codes of handling of "loss number"
// -----------------------------------------------------------------------
const int CFN_los_min		= 0;
const int CFN_los_zero		= 1;
const int CFN_los_warning	= 3;
const int CFN_los_stop		= 4;
// -----------------------------------------------------------------------
// arithmetic operation codes (16.12.2002)
// -----------------------------------------------------------------------
const int CFN_OC_SETUP = 0;		// setup function
const int CFN_OC_ASS = 1;		// assignment operator
const int CFN_OC_ADD = 2;		// add
const int CFN_OC_SUB = 3;		// sub
const int CFN_OC_MUL = 4;		// mul
const int CFN_OC_DIV = 5;		// div
// -----------------------------------------------------------------------
// error fields (10.12.2002)
// -----------------------------------------------------------------------
const int CFN_err_ovf = 1;
const int CFN_err_dbz = 2;
const int CFN_err_loss = 4;
const int CFN_err_invalid = 8;
// =======================================================================
class CFixNum
	{
public:
	// -------------------------------------------------------------------
	// from CFix class: codes for overflow types, how to handle (23.12.2002)
	// -------------------------------------------------------------------
	enum { ovf_saturate = 0,
	ovf_zero_saturate = 1,
	ovf_wrapped = 2,
	ovf_warning = 3,
	ovf_n_types = 4
	};
	// -------------------------------------------------------------------
	// from CFix class: error fields (23.12.2002)
	// -------------------------------------------------------------------
	enum errorcode { err_ovf = 1, err_dbz = 2, err_invalid = 4 };
	// -------------------------------------------------------------------
	// from CFix class: truncation-rounding codes, for backward compatibility
    enum mask { mask_truncate = 0, mask_truncate_round = 1 };
	// -------------------------------------------------------------------	
	CFixNum AsFixNum(const CFixNum& tFN) const;		// returns converted current value as a FixNum with given parametrs (03.01.2003)
	CFixNum AsFixNum(int nLen, int nLenFrac) const;	// returns converted current value as a FixNum with given parametrs (11.12.2002)
inline int GetSize() const { return m_nBitLen;}			// returns size of an integer and fractional parts
inline int GetSizeFrac() const { return m_nFracBits;}	// returns number of bits of the fractional part
inline int GetSizeInt() const  { return m_nBitLen - m_nFracBits; }		// bits to left of binary point
	static BOOL SetErrHandFunc(int (*pErrHand)(	// sets error handling function (16.12.2002)
		int nErrCode,					// err code
		char* sRoutineName,				// subroutine name
		char* sMsg,						// message
		int nOpCode,					// arithmetic operation code
		CFixNum* pA,					// first operand
		CFixNum* pB,					// second operand
		CFixNum* pRes					// result
		));	// sets error handling function (16.12.2002)
	BOOL Setup(int nBitLen, int nFracBits);				// resets current class preferences and set new preferences
	BOOL Setup(int pLens[3]);							// resets current class preferences and set new preferences
	BOOL SetupAsInt(int nLen);							// adjust class parameters to represent integer numbers only (19.12.2002)
	BOOL SetupFrom(const CFixNum& tFN);					// sets to the current number the same parametrs as the given number has (20.12.2002)
	// -------------------------------------------------------------------
	CFixNum& ConvertTo(int nLen, int nLenFrac);			// converts current value into another representation (18.12.2002)
	CFixNum& ConvertTo(const CFixNum& tFN);				// converts current value into another representation (03.01.2003)
	// -------------------------------------------------------------------
	// Interface (had been copied from CFix class)
	// -------------------------------------------------------------------
	int dbz() const { return (m_nError & CFN_err_dbz) != 0;} // from CFix class: returns true, if DBZ is occurred
	int fracb() const { return GetSizeFrac();}	// from CFix class: bits to left of binary point (23.12.2002)
	void initialize() { SetupDef(); }			// from CFix class: discard precision information and zero
	int intb() const { return GetSizeInt(); }	// from CFix class: bits to right of binary point (23.12.2002)
	int invalid() const { return (m_nError & (CFN_err_dbz|CFN_err_invalid)) != 0;} // from CFix class: returns true, if current number is invalid
	int is_zero() const { return IsEqualToZero(); }	// from CFix class: return TRUE iff zero value
	int len() const { return GetSize(); }		// from CFix class: length in bits (23.12.2002)
	double max() const	{ return GetMax(); }	// from CFix class: max value representable in this format
    double min() const	{ return GetMin(); }	// from CFix class: min value representable in this format
    int overflow() const { return m_nHandOVF;}	// return overflow type (one of the codes above) (07.01.2003)
	int ovf_occurred() const{ return (m_nError & CFN_err_ovf) != 0;}	// from CFix class: returns true, if overflow is occurred
	int precision() const { return fracb(); }	// from CFix class: obsolete
    void set_ovflow (const char*);				// from CFix class: set overflow using a name
	void set_overflow(int value) { m_nHandOVF = value;}	// from CFix class: set the overflow type
	int setPrecision(const char * prec_spec);	// from CFix class: sets new precission
	void setToZero() { m_nNumber=0; }			// from CFix class: set to zero (equivalent to assigning zero)
	int signBit() const { return GetSign()<0; }	// from CFix class: return TRUE for negative, false for + or 0
	double value() const {return AsDouble(); }	// from CFix class: value as a double
    // -------------------------------------------------------------------
	// dummy functions (copied from Fix.cpp only for compability) (07.01.2003)
	// -------------------------------------------------------------------
    void set_rounding(int value) { roundFlag = (value != 0);}	// DUMMY - set the rounding type: true for rounding, false for truncation (07.01.2003)
    void Set_MASK(int value) { set_rounding(value);}			// DUMMY - set the rounding type: synonym for backward compatibility (07.01.2003)
    int roundMode() const { return roundFlag;}					// DUMMY - return rounding mode (1 for rounding, 0 for truncation) (07.01.2003)
    void complement() {m_nNumber*=-1;}							// DUMMY - replace arg by its negative (07.01.2003)
	friend void	printFix(const CFixNum&);						// DUMMY - debug-style printer (07.01.2003)
	// -------------------------------------------------------------------
	// comparing
	// -------------------------------------------------------------------
	bool operator==(const CFixNum& tFN);	// op. ==
	bool operator==(const double& a);		// op. ==
	bool operator==(const int& a);			// op. ==
	bool operator< (const CFixNum& tFN);	// op. <
	bool operator< (const double& a);		// op. <
	bool operator< (const int& a);			// op. <
	bool operator<=(const CFixNum& tFN);	// op. <=
	bool operator<=(const double& a);		// op. <=
	bool operator> (const CFixNum& tFN);	// op. >
	bool operator> (const double& a);		// op. >
	bool operator> (const int& a);			// op. >
	bool operator>=(const CFixNum& tFN);	// op. >=
	bool operator>=(const double& a);		// op. >=
	bool operator>=(const int& a);			// op. >=
	// -------------------------------------------------------------------
	operator float();						// op. convert to float
	operator double();						// op. convert to double
	operator int();							// op. convert to int
	// -------------------------------------------------------------------
	// arithmetic: friends -!-
	// -------------------------------------------------------------------
	friend CFixNum operator/(const double& a,	const CFixNum& tFN);	// op. /
	friend CFixNum operator/(const int& a,		const CFixNum& tFN);	// op. /
	// -------------------------------------------------------------------
	friend double fabs(CFixNum tFN);
	friend ostream& operator<< (ostream& os, const CFixNum& tFN);		// DUMMY - print on ostream in form (value, precision) (07.01.2003)
	// -------------------------------------------------------------------
	// arithmetic
	// -------------------------------------------------------------------
	const CFixNum& operator++();			// prefix increment. For integer numbers only. (20.12.2002)
	const CFixNum operator++(int);			// postfix increment. For integer numbers only. (20.12.2002)
	CFixNum operator+(const CFixNum& tFN);	// op. +
	CFixNum operator-(const CFixNum& tFN);	// op. -
	CFixNum operator-();					// op. unary -
	CFixNum operator*(const CFixNum& tFN);	// op. *
	CFixNum operator/(const CFixNum& tFN);	// op. /
	// -------------------------------------------------------------------
	// assignment arithmetic (03.01.2002)
	// -------------------------------------------------------------------
	CFixNum& operator += (const CFixNum&);	// op. +=
	CFixNum& operator -= (const CFixNum&);	// op. -=
	CFixNum& operator *= (const CFixNum&);	// op. *=
	// -------------------------------------------------------------------
	// copying
	// -------------------------------------------------------------------
	CFixNum& operator =(const double &a);	// op. =
	CFixNum& operator =(const int &a);		// op. =
	CFixNum& operator =(double &a);			// op. =
	CFixNum& operator =(int &a);			// op. =
	// -------------------------------------------------------------------
	const CFixNum& operator =(const CFixNum&tFN);		// op. =	- standard	
	// -------------------------------------------------------------------
	CFixNum(int nLen, int nIntBits);							// initialising: bit capacity, number of int bits
	CFixNum(int nLen, int nIntBits, double a);					// initialising: len, intb, value
	CFixNum(int nLen, int nIntBits, const CFixNum& tFN);		// init: len, intb, ref to a CFixNum (06.01.2003)
	CFixNum(int nLen, int nIntBits, int nFracBits, double a);	// initialising: len, intb, fracb, value
	CFixNum(const CFixNum& tFN);	// copying constructor		- standard	
	// -------------------------------------------------------------------
	CFixNum();						// constructors (default)	- standard
	virtual ~CFixNum();				//							- standard
	// -------------------------------------------------------------------
private:
	double AsDouble() const;			// returns stored value as double
	int AsInt() const;					// returns stored value as integer
inline BOOL AutoInit();					// default initialisation
	BOOL AutoSetupFromNumber(double a);	// automatically setups class from a given number
	double CalcPartFrac() const;		// calculates fractional part of the current number as a double value
	int CalcPartInt() const;			// calculates integer part of the current number as a double value
inline void ClearErrors() { m_nError = 0; }				// clears error flag (10.12.2002)
	BOOL Compare(const CFixNum& tFN);	// compares current fixed point number with given number
	BOOL Compare(const double& a);		// compares current fixed point number with given number
	BOOL Compare(const int& a);			// compares current fixed point number with given number
	BOOL ErrHand(int nErrCode,			// error handler (10.12.2002)
		char* sRoutine,
		char* sMsg,
		int nOpCode,
		CFixNum* pA,
		CFixNum* pB,
		CFixNum* pRes);
inline double FindMax(int ln, int ib) const;	// calculates max legal value
inline double FindMin(int ln, int ib) const;	// calculates min legal value
	int GetAbsNumber() const;					// returns absolute value of internal integer number (11.12.2002)
unsigned int GetBitMapFracWOSign(int nLen)const;	// returns a bitmap of given length of a fractional part
unsigned int GetBitMapIntWOSign() const;			// returns a bitmap of an integer part
unsigned int GetBitMapIntWOSign(int nLen) const;	// returns a bitmap of given length of an integer part (16.12.2002)
unsigned int GetBitMask(int nSize) const;		// returns a sequence of "one"s bits of given length (20.12.2002)
	int GetOptNumOfBitsForFracPart(double a);		// returns optimal number of bits to represent a fractional part of a given number
	int GetOptNumOfBitsForIntPartAndSign(double a);	// returns optimal number of bits to represent a integer part of a given number
    double GetMax() const;							// max value representable in this format
    double GetMin() const;							// min value representable in this format
	int GetNumOfNZBitsAndSignVS() const;	// returns number of non-zero bits in integer part (plus one more bit for a sign)
	int GetPartFracBitOf(double a, int n);	// returns n bits for the fractional part
	double GetPartFracOf(double a) const;	// returns fractional part of a given number
	int GetPartIntOf(double a) const;		// returns integer part of a given number
	int GetSign() const;				// returns +1 if value >=0, otherwise -1
	int GetSignOf(double a);			// returns a sign of given number
	int GetSignOf(int a);				// returns a sign of given number
	double GetStep();					// returns minimal difference (step) between two closest numbers
	BOOL IsEqualToOne();				// returns true, if an internal value is equal to 1.0 or -1.0 (12.12.2002)
	BOOL IsEqualToZero() const;			// returns true, if an internal value is equal to 0.0 (zero) (12.12.2002)
	inline BOOL IsFitInRange(double dNumber);	// returns true, if given value is fit in the range
	BOOL IsInited() const;				// returns true, if class has been inited manually (16.12.2002)
	double Prescale(double a);			// prescales input values
	BOOL SetInvalidity(BOOL bInv);		// sets or resets invalidity flag (06.01.2003)
	BOOL SetSaturation(int nSign);		// sets maximal or minimal saturation
	BOOL SetSaturationZero();			// sets zero saturation
	BOOL Setup(int nBitLen, int nFracBits, double a);	// initialising: len, intb, value
	BOOL SetupDef();					// setups internal data with default values	
	BOOL RescaleAndSetValue(double a);	// sets current value
	// -------------------------------------------------------------------
	// data
	// -------------------------------------------------------------------
	int m_bInited;						// true, if a number has been inited manually, e.g. Initialization or Copy constructor (16.12.2002)
	// -------------------------------------------------------------------
	int m_nNumber;						// fixed (point) number
	int m_nBitLen;						// length of the current f.p. number in bits
	int m_nFracBits;					// number of bits of a fractional part
	int m_nError;						// error flag (10.12.2002)
	// -------------------------------------------------------------------
	static double m_dRescFactor;		// rescaling factor
	static int m_nHandOVF;				// overflow handling (10.12.2002)
	static int m_nHandLOS;				// "loss number" handling (18.12.2002)
	// -------------------------------------------------------------------
	static int (*m_pErrHandFunc)(		// pointer to the external error handling function (16.12.2002)
		int nErrCode,					// err code
		char* sRoutineName,				// subroutine name
		char* sMsg,						// message
		int nOpCode,					// arithmetic operation code
		CFixNum* pA,					// first operand
		CFixNum* pB,					// second operand
		CFixNum* pRes					// result
		);
	// -------------------------------------------------------------------
	BOOL roundFlag;						// DUMMY - only for compability (07.01.2003)
	// -------------------------------------------------------------------
};
// =======================================================================
#endif // !defined(AFX_FNUMBER_H__085DA7E5_6506_40E3_B8DB_6A96595324D0__INCLUDED_)
// =======================================================================