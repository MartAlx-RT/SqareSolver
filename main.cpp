#include "SquareSolverTest.h"
#include "SquareSolver.h"
#include "In.h"
#include "Out.h"

int main(void) //TODO argc argv
{
    struct RefSolutions* refsol;
    
    //tester
    int NumSol = EnterTest(&refsol, "SquareSolver\\UnitTest.txt");

    UnitTest(SolveSqr, refsol, NumSol);
    StressTest(SolveSqr);
    printf("\n\n%d\n\n", NumSol);

    //solver
    struct Coefficients coeff = {0, 0, ZERO_SOL};
    
    EnterCoefficients(&coeff);
    PrintRoots(SolveSqr(coeff));


    return 0;
}