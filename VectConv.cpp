// =======================================================================
// VECTor CONVertions class ver. 1.0
// set of functions to convert vector data
// -----------------------------------------------------------------------
//       MD: 09.01.2003
//       LE: 09.01.2003
// -----------------------------------------------------------------------
// Compiler: MS VC 6.0
// =======================================================================
// VectConv.cpp: implementation of the CVectConv class.
// =======================================================================
#include "stdafx.h"
#include "VectConv.h"
// -----------------------------------------------------------------------
#include <crtdbg.h>			// _ASSERT (09.01.2003)
// =======================================================================
// Construction/Destruction
// =======================================================================
CVectConv::CVectConv()
{

}
// =======================================================================
CVectConv::~CVectConv()
{

}
// =======================================================================
BOOL CVectConv::ConvertIntToVectBool(int nNumber, CVectorBool&x, int nBits)	{
// -----------------------------------------------------------------------
// Description: calculates bitmask of given int number and puts it into the given vector
//   Parametrs: nNumber	-	input number
//				x		-	array with bitmask
//				nBits	-	number of bits to convert (size of the output array)
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 09.01.2003
//          LE: 09.01.2003
// -----------------------------------------------------------------------
	_ASSERT(nBits>=1 && nBits<32);
	x=CVectorBool(nBits);
	for (int i=0; i<nBits; i++)
		x[i]=1 && (nNumber & (1<<i));
	return(true);
	}
// =======================================================================
BOOL CVectConv::ConvVectCmplxToFloat(CVectorCmplx&z, CVectorFloat&x, CVectorFloat&y)	{
// -----------------------------------------------------------------------
// Description: converts one complex data stream into two float data streams
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 07.11.2002
//          LE: 07.11.2002, 03.01.2002
// -----------------------------------------------------------------------
	_ASSERT(z.size());				// input vector is empty (09.01.2003)
	_ASSERT(z.size()==x.size());	// wrong sizes (09.01.2003)
	_ASSERT(z.size()==y.size());	// wrong sizes (09.01.2003)
	int nSize=z.size();
	for (int i=0; i<nSize; i++)	{
		CFloat	re=z[i].Re(),
				im=z[i].Im();
	#ifdef SDRPDEMO_USEFIX
		re.ConvertTo(x[i]);
		im.ConvertTo(y[i]);
	#endif 
		x[i]=re;
		y[i]=im;
		}
	return(true);
	}
// =======================================================================
BOOL CVectConv::ConvVectFloatToCmplx(CVectorFloat&x, CVectorFloat&y, CVectorCmplx&z)	{
// -----------------------------------------------------------------------
// Description: converts two float data streams into one complex data stream
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 07.11.2002
//          LE: 07.11.2002, 06.01.2003
// -----------------------------------------------------------------------
	_ASSERT(z.size());				// no space reserved (09.01.2003)
	_ASSERT(z.size()==x.size());	// wrong sizes (09.01.2003)
	_ASSERT(z.size()==y.size());	// wrong sizes (09.01.2003)
	int nSize=x.size();
	#ifdef SDRPDEMO_USEFIX
	SetupFixPointInVector(z, x[0].GetSize(), x[0].GetSizeFrac());
	#endif
	for (int i=0; i<nSize; i++) z[i]=CComplex(x[i], y[i]);
	return(true);
	}
// =======================================================================
BOOL CVectConv::ConvVectBoolToInt(CVectorBool &x, CVectorInt &y)		{
// -----------------------------------------------------------------------
// Description: converts vector of BOOL elements into vector of BYTES (only 8 bits are used)
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 09.01.2003
//          LE: 09.01.2003
// -----------------------------------------------------------------------
	_ASSERT(x.size());				// input vector is empty
	_ASSERT(x.size()==y.size()*8);	// wrong size of the output vector
	int nSizeX=x.size();
	int nSizeY=(nSizeX+7)/8;
	int nIdxY=0;
	for (int i=0; i<nSizeY; i++)
		for (int j=0; j<8; j++)
			y[i]|=(x[i*8 + j] << j);
	return(true);
	}
// =======================================================================
BOOL CVectConv::ConvVectIntToBool(CVectorInt &x, CVectorBool &y, int nBitsPI)		{
// -----------------------------------------------------------------------
// Description: converts vector of BYTES into vector of BOOL elements
//   Parametrs: nBitsPI	- number of bits in the output vector per one word of the input vector
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 09.01.2003
//          LE: 15.01.2003
// -----------------------------------------------------------------------
	_ASSERT(x.size());						// input vector is empty
	_ASSERT(nBitsPI>=8 && nBitsPI<32);		// bits in the output vector per one word of the input vector
	_ASSERT(y.size()==x.size()*nBitsPI);	// wrong size of the output vector
	// -------------------------------------------------------------------
	int nSizeX=x.size();
	int nIdxY=0;
	if (y.size()==0)
		y=CVectorBool(nSizeX*nBitsPI);
	for (int i=0; i<nSizeX; i++)
		for (int j=0; j<nBitsPI; j++)
			y[nIdxY++]=1 && (x[i] & (1<<j));
	return(true);
	}
// =======================================================================
CVectorBool CVectConv::GetWindow(CVectorBool &x, int nBlockSize, int nBlockNum)	{
// -----------------------------------------------------------------------
// Description: returns a vector, which is a copy of window
//   Parametrs: ...
//      Return: vector
// -----------------------------------------------------------------------
//          MD: 16.01.2003
//          LE: 16.01.2003
// -----------------------------------------------------------------------
	_ASSERT(x.size());
	_ASSERT(nBlockSize<=x.size());
	_ASSERT(nBlockSize*nBlockNum+nBlockSize<=x.size());
	// -------------------------------------------------------------------
	int i, j, i0, iN;
	int nSize=x.size();
	CVectorBool y;
	// -------------------------------------------------------------------
	y=CVectorBool(nBlockSize);
	i0=nBlockSize*nBlockNum;
	iN=i0+nBlockSize;
	// -------------------------------------------------------------------
	for (i=i0, j=0; i<iN; i++, j++)	
		y[j]=x[i];
	return(y);
	}
// =======================================================================
BOOL CVectConv::SetupFixPointInVector(CVectorCmplx&tVF, int nL, int nF)	{
// -----------------------------------------------------------------------
// Description: adjusts fix point position in a complex vector
//   Parametrs: ...
//      Return: true - ok
// -----------------------------------------------------------------------
//          MD: 17.12.2002
//          LE: 17.12.2002
// -----------------------------------------------------------------------
	#ifdef SDRPDEMO_USEFIX
	int nSize=tVF.size();
	for (int i=0; i<nSize; i++) tVF[i].Setup(nL, nF);
	#endif
	return(true);
	}
// -----------------------------------------------------------------------
BOOL CVectConv::SetupFixPointInVector(CVectorFloat&tVF, int nL, int nF)	{
	#ifdef SDRPDEMO_USEFIX
	int nSize=tVF.size();
	for (int i=0; i<nSize; i++) tVF[i].Setup(nL, nF);
	#endif
	return(true);
	}
// -----------------------------------------------------------------------
BOOL CVectConv::SetupFixPointInVector(CVectorCmplx&tVF, int pLens[3])	{
	return(SetupFixPointInVector(tVF, pLens[0], pLens[2]));
	}
// -----------------------------------------------------------------------
BOOL CVectConv::SetupFixPointInVector(CVectorFloat&tVF, int pLens[3])	{
	return(SetupFixPointInVector(tVF, pLens[0], pLens[2]));
	}
// =======================================================================
