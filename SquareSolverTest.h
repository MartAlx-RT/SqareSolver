#include "SquareLib.h"
#ifndef SQUARESOLVERTEST_H
#define SQUARESOLVERTEST_H


struct RefSolutions
{
    struct Coefficients coeff = {NAN, NAN, NAN};
    struct Roots RefRoots = {0, 0, ZERO_SOL};
};

const size_t RefSolSize = sizeof(struct RefSolutions);

int EnterTest(struct RefSolutions *sol, const char *FileName, const int MaxSize);

void UnitTest(struct Roots (*FuncUnderTest)(struct Coefficients coeff), struct RefSolutions *sol, int NumOfTests);

bool CheckRoot(struct Coefficients coeff, double PossibleRoot);

void Test1(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
void Test2(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
void Test3(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
void Test4(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
void Test5(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
void Test6(struct Roots (*FuncUnderTest)(struct Coefficients coeff));

void StressTest(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
#endif