#ifndef INPUT_H
#define INPUT_H

#include "CommonVar.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>

void EnterDoubleWithCheck(double *x);

int EnterTest(struct RefSolutions **sol, const char *FileName);

void EnterCoefficients(struct Coefficients *coeff);

enum Status NumToStatus(int Num);

#endif