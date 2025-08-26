#ifndef SQUARELIB_H
#define SQUARELIB_H
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

const double EPS = 1e-10; // Error for CompZero function
const double EPS2 = 1e-10; // Error for CompZero in UnitTest


enum Status
{
    INF_SOL = -1,
    ZERO_SOL = 0,
    ONE_SOL = 1,
    TWO_SOL = 2
};

struct Roots
{
    double Root1 = 0, Root2 = 0;
    enum Status NumOfRoots = ZERO_SOL;
};

struct Coefficients
{
    double a = NAN, b = NAN, c = NAN;
};


bool CompZero(double x);

static inline void ScanfDoubleWithCheck(double *x);



void EnterCoefficients(struct Coefficients *coeff);

struct Roots SolveLinear(struct Coefficients coeff);
struct Roots SolveSqr(struct Coefficients coeff);

void PrintRoots(struct Roots rts);

#endif
