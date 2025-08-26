#include "SquareSolverTest.h"
#include "SquareLib.h"
#include <malloc.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(void)
{
    struct RefSolutions refsol[200];
    //tester
    int NumSol = EnterTest(refsol, ".\\.vscode\\UnitTest.txt", 200);

    UnitTest(SolveSqr, refsol, NumSol);
    StressTest(SolveSqr);
    
    //solver
    struct Coefficients coeff = {0, 0, ZERO_SOL};
    
    EnterCoefficients(&coeff);
    PrintRoots(SolveSqr(coeff));

    return 0;
}