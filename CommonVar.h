#ifndef COMMONVAR_H
#define COMMONVAR_H

#include <math.h>

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
    double Root1 = NAN, Root2 = NAN;
    enum Status NumOfRoots = ZERO_SOL;
};

struct Coefficients
{
    double a = NAN, b = NAN, c = NAN;
};

struct RefSolutions
{
    struct Coefficients coeff = {NAN, NAN, NAN};
    struct Roots RefRoots = {0, 0, ZERO_SOL};
};

#endif  //CAMMINVAR_H