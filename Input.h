#ifndef INPUT_H
#define INPUT_H

#include "CommonVar.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>

int EnterTest(struct RefSolutions **sol, const char *FileName);

static inline void ScanfDoubleWithCheck(double *x);

void EnterCoefficients(struct Coefficients *coeff); 

enum Status NumToStatus(int Num);

#endif