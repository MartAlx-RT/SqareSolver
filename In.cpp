#include "In.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "SquareSolverTest.h"

int EnterTest(struct RefSolutions** sol, const char* FileName)
{
    assert(sol != NULL);
    assert(FileName != "");
    //assert(MaxSize >= 1);
    
    FILE *Utest = fopen(FileName, "r");

    
    int scanned = 6, NumTest = 0; 
    
    int NumOfRoots = 0;
    *sol = NULL;

    for (NumTest = 0; scanned == 6;NumTest++)
    {
        *sol = (struct RefSolutions *)realloc(*sol, (NumTest + 1) * sizeof(struct RefSolutions));
        scanned = fscanf(Utest, "%lg %lg %lg %lg %lg %d",
                         &(*sol)[NumTest].coeff.a, &(*sol)[NumTest].coeff.b, &(*sol)[NumTest].coeff.c,
                         &(*sol)[NumTest].RefRoots.Root1, &(*sol)[NumTest].RefRoots.Root2, &NumOfRoots);

        (*sol)[NumTest].RefRoots.NumOfRoots = NumToStatus(NumOfRoots);
    }
    
    assert(scanned != 6);

    fclose(Utest); 
    return --NumTest; 
}


static inline void ScanfDoubleWithCheck(double* x)
{
    assert(x != NULL);
    char c = 0;
    while(scanf("%lg", x) == 0 || getchar() != '\n')
    {
        printf("You entered wrong symbols or extra space, try again\n");
        while(getchar()!='\n');
    }
}


void EnterCoefficients(struct Coefficients* coeff)
{
    assert(coeff != NULL);

    printf("This is the square equation solver\n"
           "Warning! Numbers less than %g are equal to zero in this program\n"
           "The normal view of square equation is:\n"
           "ax^2+bx+c=0\n", EPS);


    printf("Please, enter a:");
    ScanfDoubleWithCheck(&(coeff->a)); //TODO space str

    printf("Please, enter b:");
    ScanfDoubleWithCheck(&(coeff->b));

    printf("Please, enter c:");
    ScanfDoubleWithCheck(&(coeff->c));
}