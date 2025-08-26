#include <math.h>
#include <malloc.h>
#include <stdio.h>
#include "SquareLib.h"
int main(void)
{
    struct Coefficients coeff = {NAN, NAN, NAN};
    //EnterCoefficients(&coeff);
    //PrintRoots(SolveSqr(coeff));
    struct RefSolutions* refsol = (struct RefSolutions *)calloc(10, sizeof(struct RefSolutions));
    int NumTests = 0;
    NumTests = (refsol, "UnitTest.txt", 10); //Не читает!!!!!!
    printf("%d\t%lg\n", refsol[0].RefRoots.NumOfRoots, refsol[0].coeff.a);

    return 0;
}