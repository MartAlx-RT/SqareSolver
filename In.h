#ifndef IN_H
#define IN_H

#include "CommonVar.h"
int EnterTest(struct RefSolutions **sol, const char *FileName);

static inline void ScanfDoubleWithCheck(double *x);
void EnterCoefficients(struct Coefficients *coeff); // TODO input / output / solver

#endif