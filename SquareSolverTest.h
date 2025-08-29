#ifndef SQUARESOLVERTEST_H
#define SQUARESOLVERTEST_H
#include "SquareSolver.h"
#include "CommonVar.h"
#include <stdio.h>
#include <stdlib.h>
#include "Input.h"
#include "SquareSolver.h"

//enum Status NumToStatus(int Num);

//int EnterTest(struct RefSolutions **sol, const char *FileName);
void PrintErrorMsg(struct RefSolutions sol, struct Roots ProbRoots);

void PrintErrorMsg(int TestNumb, struct Coefficients coeff);

void UnitTest(struct Roots (*FuncUnderTest)(struct Coefficients coeff), struct RefSolutions *sol, int NumOfTests);

bool CheckRoot(struct RefSolutions sol, struct Roots ProbRoots);


void RandGeneratePositive(double *a, double *b, double *c);



void Test1(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
void Test2(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
void Test3(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
void Test4(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
void Test5(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
void Test6(struct Roots (*FuncUnderTest)(struct Coefficients coeff));

void StressTest(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
#endif