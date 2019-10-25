// =======================================================================
// SDRPPDemo.cpp : Defines the entry point for the console application.
// =======================================================================
#include "stdafx.h"
// -----------------------------------------------------------------------
#include "DataTypes.h"	// 04.12.2002
#include "SDRPrims.h"	// 05.11.2002
#include "SDRBlock.h"	// 07.11.2002
#include "SDRTest.h"	// 21.11.2002
#include "AutoBuild.h"	// 11.12.2002	- auto build number
//#include "Parser.h"		// 19.11.2002
// -----------------------------------------------------------------------
#include "stdio.h"		// printf
// =======================================================================
// CFixNum error handler
// =======================================================================
int ExtErrHand(
		int nErrCode,					// err code
		char* sRoutineName,				// subroutine name
		char* sMsg,						// message
		int nOpCode,					// arithmetic operation code
		CFixNum* pA,					// first operand
		CFixNum* pB,					// second operand
		CFixNum* pRes					// result
		)
{
// MD: 16.12.2002
// external call back function test
// -----------------------------------------------------------------------
// example of overflow error handling
// -----------------------------------------------------------------------
if (nErrCode==1)	// err_ovf
	{
	printf ("EEH: External Overflow handling - ", sRoutineName, sMsg, nOpCode);
	int nSizeIntA=pA->intb();
	int nSizeIntB=pB->intb();
	int nSizeB=pB->len();
	if (nSizeIntA<nSizeIntB)
		{
		int nSizeFracB=pB->fracb();
		pRes->Setup(nSizeB, nSizeFracB);
		*pRes=CFixNum(*pB);
		printf ("ok\n");
		return(0);
		}
	}
printf ("EEH: %s: %s, nOpCode=%d\n", sRoutineName, sMsg, nOpCode);
// -----------------------------------------------------------------------
return(0);
}
// =======================================================================
int main(int argc, char* argv[])
{
// -----------------------------------------------------------------------
printf ("Software Defined Radio Primitives Demo ver. 1.0\n"
		"Build number: %d\n\n", AUTO_BUILDNUMBER);
// -----------------------------------------------------------------------
//CFixNum::SetRescalingFactor(1);			// 06.12.2002
CFixNum::SetErrHandFunc(&ExtErrHand);	// 16.12.2002
// -----------------------------------------------------------------------
int n=5, k=3;
CFloat tDotp, tSqrSum, tSum, dVMean;
CVectorFloat tVF(n), tH(k),
			tFIR(n), 
			tFIRSE(n),
			tFIRSO(n),
			tCWP(n),
			tCWS(n), tCWD(n), tCWQ(n), 
			tScaled(n), 
			tABS(n), tAbsSq(n), tSWA(k);
// -----------------------------------------------------------------------
CVectorFloat tDCOR(n);
CVectorInt tPhase(n);
CVectorCmplx tVC(n), tCCPLX(n);
// -----------------------------------------------------------------------
CComplex tACFPNT;
CSDRPrims tPrim;	// set of functional primitives
CSDRBlock tBlck;	// set of functional blocks
CSDRTest tTest;		// tester (21.11.2002)
// -----------------------------------------------------------------------
tTest.Setup();
// -----------------------------------------------------------------------
double a=2.75, b=3.875;
CFixNum tA(8, 0, 3, a);
CFixNum tB(8, 0, 3, b);
CFixNum tC=tA*tB;
printf ("Test: CFixNum::operator* (...): tC = %lf (double = %lf)\n", (double)tC, a*b);
// -----------------------------------------------------------------------
/*
// 1 1001 1111 0101 0000
// 1 , 9    F    5    0   = 106320 (32:16)
//
// 1100 1111 1010 1000    = 1, 1001 1111 0101 000
//  C    F    A    8      = 53160  (32:17)
CFixNum tX(32, 16,  1.6223144531250);
CFixNum tY(32, 16, -1.6223144531250);
CFixNum tZ=tX*tY;
printf ("Test: CFixNum::operator* (...): tZ = %lf\n", (double)tZ);
*/
// -----------------------------------------------------------------------
#ifndef SDRPDEMO_USEFIX
tVC[0]=CComplex(1,2);
tVC[1]=CComplex(3,4);
tVC[2]=CComplex(5,6);
tVC[3]=CComplex(7,8);
tVC[4]=CComplex(9,10);
// -----------------------------------------------------------------------
tVF[0]=1;
tVF[1]=2;
tVF[2]=3;
tVF[3]=4;
tVF[4]=5;
// -----------------------------------------------------------------------
for (int i=0; i<tVF.size(); i++)
	printf("tVF[%d]=%lf\n", i, (double)tVF[i]);
// -----------------------------------------------------------------------
tH[0]=1;
tH[1]=2;
tH[2]=3;
// -----------------------------------------------------------------------
// Setup section
// -----------------------------------------------------------------------
tPrim.Setup(1);
tBlck.Setup(10);
// -----------------------------------------------------------------------
// f.p. setup
// -----------------------------------------------------------------------
tPrim.CWP_SetupFP		(16, 8, 12, 6);
tPrim.CWS_SetupFP		(16, 8, 12, 6);
tPrim.CWD_SetupFP		(16, 8, 12, 6);
tPrim.FIR_SetupFP		(16, 8, 12, 6);
tPrim.FIRSE_SetupFP		(16, 8, 12, 6);
tPrim.FIRSO_SetupFP		(16, 8, 12, 6);
tPrim.CWSQR_SetupFP		(12, 6, 12, 6);
tPrim.CWSC_SetupFP		(12, 6, 12, 6);
tPrim.ABS_SetupFP		(12, 6, 12, 6);
tPrim.VMEAN_SetupFP		(12, 6, 12, 6);
tPrim.SQRSUM_SetupFP	(16, 6, 12, 6);
tPrim.VSUM_SetupFP		(20, 6, 12, 6);
tPrim.SWA_SetupFP		(20, 6, 12, 6);
tPrim.PHASE_SetupFP		(32, 15, 12, 6);
// -----------------------------------------------------------------------
tBlck.DCOffRem_SetupFP	(12, 6, 16, 8, 12, 6);
// -----------------------------------------------------------------------
tPrim.DOTP2_Setup	(tCWS.size(), tCWP.size());
tPrim.ACFPNT_Setup	(tVC.size(), 4);
tPrim.FIR_Setup		(tH, tVF.size(), tH.size());
tPrim.FIRSE_Setup	(tH, tVF.size(), tH.size());
tPrim.FIRSO_Setup	(tH, tVF.size(), tH.size());
tPrim.CWP_Setup		(tCWS.size(), tScaled.size());
tPrim.CWS_Setup		(tVF.size(), tScaled.size());
tPrim.CWD_Setup		(tCWS.size(), tScaled.size());
tPrim.CWQ_Setup		(tCWP.size(), tScaled.size());
tPrim.CWSQR_Setup	(tVF.size());
tPrim.CWSC_Setup	(tVF.size());
tPrim.ABS_Setup		(tVF.size());
tPrim.SQRSUM_Setup	(tVF.size());
tPrim.PHASE_Setup	(tVC.size());
tPrim.CCPLX_Setup	(tVC.size());
tPrim.VSUM_Setup	(tVF.size());
tPrim.SWA_Setup		(tVF.size()+1-tSWA.size(), tVF.size());
tPrim.VMEAN_Setup	(tVF.size());
// -----------------------------------------------------------------------
// Block setup section
// -----------------------------------------------------------------------
tBlck.DCOffRem_Setup(n);
// -----------------------------------------------------------------------
// Process section ... Functional primitives
// -----------------------------------------------------------------------
//tPrim.ACFPNT	(tVC, tACFPNT);
tPrim.FIR		(tVF, tFIR);
tPrim.FIRSE		(tVF, tFIRSE);
tPrim.FIRSO		(tVF, tFIRSO);
// -----------------------------------------------------------------------
tPrim.CWSQR		(tVF, tAbsSq);
tPrim.CWSC		(tVF, 1.52, tScaled);
tPrim.ABS		(tVF, tABS);
tPrim.SQRSUM	(tVF, tSqrSum);
tPrim.PHASE		(tVC, tPhase);
tPrim.CCPLX		(tVC, tCCPLX);
tPrim.VSUM		(tVF, tSum);
// -----------------------------------------------------------------------
tPrim.CWS		(tVF, tScaled, tCWS);
tPrim.CWD		(tCWS, tScaled, tCWD);
tPrim.CWP		(tCWS, tScaled, tCWP);
tPrim.DOTP2		(tCWS, tCWP, tDotp);	// too many overflows (16.12.2002)
tPrim.CWQ		(tCWP, tScaled, tCWQ);	// too many overflows (16.12.2002)
tPrim.SWA		(tVF, tSWA);
tPrim.VMEAN		(tVF, dVMean);
// -----------------------------------------------------------------------
// Process section ... Functional blocks
// -----------------------------------------------------------------------
//tBlck.DCOffRem(tVF, tDCOR);
tBlck.DCOffRem(tFIR, tDCOR);
// -----------------------------------------------------------------------
/*
printf ("\n"
		"Input vector: "); tVF.Print();
printf ("           H: "); tH.Print(); printf ("\n");
printf ("         FIR: "); tFIR.Print();
printf ("       FIRSE: "); tFIRSE.Print();
printf ("       FIRSO: "); tFIRSO.Print();
printf ("      Scaled: "); tScaled.Print();
printf ("Absolute val: "); tABS.Print();
printf ("     Squares: "); tAbsSq.Print();
printf ("      Phases: "); tPhase.Print();
printf ("  Conjugated: "); tCCPLX.Print();
printf ("CW  VectProd: "); tCWP.Print();
printf ("CW VectorSum: "); tCWS.Print();
printf ("CW VectorDif: "); tCWD.Print();
printf ("CW VectorQuo: "); tCWQ.Print();
printf ("  SWA (mean): "); tSWA.Print();
// -----------------------------------------------------------------------
printf ("    DCOffRem: "); tDCOR.Print();
//*/
// -----------------------------------------------------------------------
printf ("\n"
		//"ACFPNT = %s\n"
		" DOTP2 = %g\n"
		"SQRSUM = %g\n"
		"  VSUM = %g\n"
		" VMEAN = %g\n"		
		//, tACFPNT.Text()
		, (double)tDotp, (double)tSqrSum, (double)tSum, (double)dVMean
		);
#endif
// -----------------------------------------------------------------------
//tTest.Test80211a();
//tTest.TestDCOffRem();				// commented for better perfomance - CFBP (22.11.2002)
//tTest.TestFreqPhaseCorr();		// CFBP (22.11.2002)
//tTest.TestSRCFIR();				// CFBP (19.11.2002)
//tTest.TestSRCIPandDE();			// CFBP (22.11.2002)
//tTest.TestSRCIP2DE();				// CFBP (22.11.2002)
//tTest.TestSRCRATAD();				// CFBP (22.11.2002)
//tTest.TestRef();					// CFBP (22.11.2002)
tTest.TestChain();				// CFBP (22.11.2002)
//CParser tP;	tP.Init(); tP.Test();
// -----------------------------------------------------------------------
return 0;
}
// =======================================================================
