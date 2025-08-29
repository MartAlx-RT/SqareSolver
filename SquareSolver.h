#ifndef SquareSolver_H
#define SquareSolver_H

//#include <stdio.h>
//#include <stdlib.h>
//#include <malloc.h>
#include "CommonVar.h"
#include <math.h>
#include <assert.h>


bool CompZero(double x);

static inline void ScanfDoubleWithCheck(double *x);


//void EnterCoefficients(struct Coefficients *coeff);

struct Roots SolveLinear(struct Coefficients coeff);
struct Roots SolveSqr(struct Coefficients coeff);

//void PrintRoots(struct Roots roots);

#endif
