// =======================================================================
// Complex Number ver. 1.0
// -----------------------------------------------------------------------
//       MD: 05.11.2002
//       LE: 05.12.2002
// -----------------------------------------------------------------------
// Compiler: MS VC 6.0
// =======================================================================
// Complex.h: interface for the CComplex class.
// =======================================================================
#if !defined(AFX_COMPLEX_H__D3FAD2FE_0F9A_4F75_9CDA_C64CF0668EBD__INCLUDED_)
#define AFX_COMPLEX_H__D3FAD2FE_0F9A_4F75_9CDA_C64CF0668EBD__INCLUDED_
// =======================================================================
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// =======================================================================
#include <iostream.h>		// ostream (04.12.2002)
#include <math.h>			// sqrt
// =======================================================================
template <class _T>
class CComplext
{
public:
	// -------------------------------------------------------------------
	// extra
	// -------------------------------------------------------------------
	BOOL Setup(int nLen, int nLenFrac)
		{
#ifdef SDRPDEMO_USEFIX	// 18.12.2002
		m_dRe.Setup(nLen, nLenFrac);
		m_dIm.Setup(nLen, nLenFrac);
#endif
		return (true);
		}
	BOOL Setup(int pLens[3])	{
		return(Setup(pLens[0], pLens[2])); }
	// -------------------------------------------------------------------
	CComplext AsComplex(const CComplext& tC)	{
		CComplext tR=*this;
		#ifdef SDRPDEMO_USEFIX	// 06.01.2003
		tR.m_dRe.ConvertTo(tC.m_dRe);
		tR.m_dIm.ConvertTo(tC.m_dIm);
		#endif
		return(tR); }
	// -------------------------------------------------------------------
	CComplext Conj()		// returns conjugated complex
		{ return CComplext(m_dRe, -m_dIm); }
	// -------------------------------------------------------------------
	_T Re() const		// get real part
		{ return(m_dRe); }
	_T real() const		// get real part
		{ return(m_dRe); }
	_T Im()	const		// get imaginary part
		{ return(m_dIm); }		
	_T imag()	const	// get imaginary part
		{ return(m_dIm); }
	// -------------------------------------------------------------------
	// arithmetics
	// -------------------------------------------------------------------
	CComplext operator+(const CComplext& z)	{
		CComplext t(m_dRe+z.Re(), m_dIm+z.Im()); return (t); }
	// -------------------------------------------------------------------
	CComplext operator-(const CComplext& z)	{
		CComplext t(m_dRe-z.Re(), m_dIm-z.Im()); return (t); }
	// -------------------------------------------------------------------
	CComplext operator*(const CComplext& z)	{
		CComplext t(m_dRe * z.Re() - m_dIm * z.Im(), m_dIm * z.Re() + 
		m_dRe * z.Im()); return (t); }
	// -------------------------------------------------------------------
	CComplext operator/(const CComplext& z)	{
		double denom=z.Re()*z.Re() + z.Im() * z.Im();
		CComplext t ((m_dRe * z.Re() + m_dIm * z.Im())/denom,
					(m_dIm * z.Re() - m_dRe * z.Im())/denom); 
		return (t); }
	// -------------------------------------------------------------------
	// HL ari
	// -------------------------------------------------------------------
	CComplext operator+(const _T& a)	{
		CComplext t(m_dRe+a, m_dIm); return (t); }
	CComplext operator-(const _T& a)	{
		CComplext t(m_dRe-a, m_dIm); return (t); }
	CComplext operator*(const _T& a)	{
		CComplext t(m_dRe*a, m_dIm*a); return (t); }
	CComplext operator/(const _T& a)	{
		CComplext t(m_dRe/a, m_dIm/a); return (t); }
	// -------------------------------------------------------------------
	// special function (13.01.2003)
	// -------------------------------------------------------------------
	CComplext e()	{
		CComplext t(exp(m_dRe)*cos(m_dIm), exp(m_dRe)*sin(m_dIm));	return(t); }
	// -------------------------------------------------------------------
	// friends
	// -------------------------------------------------------------------
	friend _T fabs(CComplext z);
	friend _T exp(CComplext z);			// (13.01.2003)
	// -------------------------------------------------------------------
	// Ari & Assign (14.01.2003)
	// -------------------------------------------------------------------
	CComplext& operator+=(const CComplext &tC) {
		*this=operator +(tC); return *this; }
	CComplext& operator/=(const CComplext &tC) {
		*this=operator /(tC); return *this; }
	// -------------------------------------------------------------------
	// Copying
	// -------------------------------------------------------------------
	/*CComplext& operator=(_T &a)
		{ m_dRe=a; m_dIm=0; return *this; }//*/
	CComplext& operator=(const _T &a)
		{ m_dRe=a; m_dIm=0; return *this; }
	// -------------------------------------------------------------------
	const CComplext& operator=(const CComplext& tC)	//	op.=	- standard
		{ m_dRe=tC.m_dRe; m_dIm=tC.m_dIm; return *this; }
	// -------------------------------------------------------------------
	// CONSTRUCTORS
	// -------------------------------------------------------------------
	CComplext (const CComplext &tC)		// copying constructor	- standard
		{
		#ifdef SDRPDEMO_USEFIX
		m_dRe.SetupFrom(tC.m_dRe);
		m_dIm.SetupFrom(tC.m_dIm);
		#endif
		m_dRe=tC.m_dRe; m_dIm=tC.m_dIm; }
	// -------------------------------------------------------------------
	CComplext()							// def. constructor		- standard
		{
		#ifdef SDRPDEMO_USEFIX
		m_dRe.SetupAsInt(32);
		m_dIm.SetupAsInt(32);
		#endif
		m_dRe=0; m_dIm=0;
		}	
	virtual ~CComplext()	{};			// destructor			- standard	
	// -------------------------------------------------------------------
	CComplext (_T Re)
		{
		#ifdef SDRPDEMO_USEFIX
		m_dRe.SetupFrom(Re);
		m_dIm.SetupFrom(Re);
		#endif
		m_dRe=Re; m_dIm=0;
		}
	CComplext (_T Re, _T Im)
		{
		#ifdef SDRPDEMO_USEFIX
		m_dRe.SetupFrom(Re);
		m_dIm.SetupFrom(Im);
		#endif
		m_dRe=Re; m_dIm=Im; }
	// -------------------------------------------------------------------	
private:
	_T m_dRe;		// real part of the number
	_T m_dIm;		// img. part of the number
	// -------------------------------------------------------------------	
};
// =======================================================================
template <class _T>_T exp(CComplext<_T> z)	{
	return CComplext (exp(z.Re())*cos(z.Im()), exp(z.Re())*sin(z.Im()));
	}
// =======================================================================
#endif // !defined(AFX_COMPLEX_H__D3FAD2FE_0F9A_4F75_9CDA_C64CF0668EBD__INCLUDED_)
// =======================================================================
