#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include "SquareLib.h"

static inline bool CompZero(double x)
{
    return (fabs(x) < EPS);
}

static inline void ScanfDoubleWithCheck(double* x) //TODO сканф с проверкой //TODO assert(x), assert(x != y)
{
    while (scanf("%lg", x) == 0) //TODO 21212asdasdasd || 2121212 sadsadasd
    {
        printf("You entered wrong symbols, try again plz\n");
        while (getchar() != '\n');
    }
}


void EnterCoefficients(struct Coefficients* coeff)
{
    printf("This is the square equation solver\n"
           "Warning! Numbers less than %g are equal to zero in this program\n"
           "The normal view of square equation is:\n"
           "ax^2+bx+c=0\n", EPS);

    printf("Please, enter a:");
    ScanfDoubleWithCheck(&(coeff->a));
    printf("Please, enter b:");
    ScanfDoubleWithCheck(&(coeff->b));
    printf("Please, enter c:");
    ScanfDoubleWithCheck(&(coeff->c));
}

struct Roots SolveLinear(struct Coefficients coeff)
{
    struct Roots rts;
    if (CompZero(coeff.a) && CompZero(coeff.b) && CompZero(coeff.c))
    {
        rts.NumOfRoots =INF_SOL;
        return rts;
    }
    if (CompZero(coeff.b))
    {
        rts.NumOfRoots = ZERO_SOL;
        return rts;
    }
    rts.NumOfRoots = ONE_SOL;
    rts.Root1 = rts.Root2 = -coeff.c / coeff.b;
    return rts;
}
struct Roots SolveSqr(struct Coefficients coeff)
{
    if (CompZero(coeff.a))
        return SolveLinear(coeff);
    struct Roots rts = {NAN, NAN, INF_SOL};
    double Discr = coeff.b * coeff.b - 4 * coeff.a * coeff.c;
    if (Discr > EPS)
    {
        Discr = sqrt(Discr);
        rts.Root1 = (-coeff.b + Discr) / (2 * coeff.a);
        rts.Root2 = (-coeff.b - Discr) / (2 * coeff.a);
        rts.NumOfRoots = TWO_SOL;
        return rts;
    }
    else if (Discr < -EPS)
    {
        rts.NumOfRoots = ZERO_SOL;
        return rts;
    }
    else
    {
        rts.Root1 = rts.Root2 = -coeff.b / (2 * coeff.a);
        rts.NumOfRoots = ONE_SOL;
        return rts;
    }
}

void PrintRoots(struct Roots rts)
{
    switch (rts.NumOfRoots)
    {
    case INF_SOL:
        printf("Has infinity Solutions\n");
        break;
    case ZERO_SOL:
        printf("Doesn't have any Solutions\n");
        break;
    case ONE_SOL:
        printf("One solution, x=%g\n", rts.Root1);
        break;
    case TWO_SOL:
        printf("Two different Solutions, Root1=%g, Root2=%g\n", rts.Root1, rts.Root2);
        break;
    default:
        printf("Invalid value of Number of roots! You can't have %d sol.\n", rts.NumOfRoots);
    }
}


int EnterTest(struct RefSolutions* sol, const char* FileName, const int MaxSize)
{
    FILE *f = fopen(FileName, "r");
    int scanned = 6, i = 0;
    int NumOfRoots = 0;

    for (i = 0; i < MaxSize && scanned == 6;i++)
    {
        scanned = fscanf(f, "%lg %lg %lg %lg %lg %d",
                         &sol[i].coeff.a, &sol[i].coeff.b, &sol[i].coeff.c,
                         &sol[i].RefRoots.Root1, &sol[i].RefRoots.Root2, &NumOfRoots);
        switch(NumOfRoots)
        {
        case -1:
            sol[i].RefRoots.NumOfRoots = INF_SOL;
            break;
        case 0:
            sol[i].RefRoots.NumOfRoots = ZERO_SOL;
            break;
        case 1:
            sol[i].RefRoots.NumOfRoots = ONE_SOL;
            break;
        case 2:
            sol[i].RefRoots.NumOfRoots = TWO_SOL;
            break;
        default:
            assert("Wrong Test File!!!!!!!!11");
        }
    }

    assert(scanned != 6);

    fclose(f);
    return --i;
}

void UnitTest(struct Roots (*FuncUnderTest) (struct Coefficients coeff), struct RefSolutions* sol, int NumOfTests)
{
    struct Roots ProbRoots = {NAN, NAN, INF_SOL};
    while(NumOfTests--)
    {
        ProbRoots = FuncUnderTest(sol[NumOfTests].coeff);
        //CheckRoot roots
        if(!((CompZero(sol[NumOfTests].RefRoots.Root1-ProbRoots.Root1) && CompZero(sol[NumOfTests].RefRoots.Root2-ProbRoots.Root2)
        || CompZero(sol[NumOfTests].RefRoots.Root1-ProbRoots.Root2) && CompZero(sol[NumOfTests].RefRoots.Root2-ProbRoots.Root1))
        && ProbRoots.NumOfRoots==sol[NumOfTests].RefRoots.NumOfRoots))
        {
            printf("Error! In test with a=%lg, b=%lg, c=%lg\nNrtsref=%d, Nrts=%d\nN=%d\n",
                sol[NumOfTests].coeff.a, sol[NumOfTests].coeff.b, sol[NumOfTests].coeff.c,
            sol[NumOfTests].RefRoots.NumOfRoots, ProbRoots.NumOfRoots, NumOfTests);
        }
    }
    printf("If you have no errors your function works correctly\n");
}


bool CheckRoot(struct Coefficients coeff, double PossibleRoot)
{
    if (fabs(coeff.a * PossibleRoot * PossibleRoot + coeff.b * PossibleRoot + coeff.c)<EPS2)
        return true;
    return false;
}

void Test1(struct Roots (*FuncUnderTest) (struct Coefficients coeff)) //D>0, two roots
{
    struct Coefficients coeff = { NAN, NAN, NAN };
    struct Roots rts = { NAN, NAN, INF_SOL };
    double a = 0, b = 0, c = 0;
    //test1 (two roots)
    for (int i = 0; i < 100; i++)
    {
        a = rand() + 1;
        b = rand() + 1;
        c = rand() + 1;
        coeff.a = a / b;
        coeff.b = b / c;
        coeff.c = -a / c;
        if (CompZero(coeff.b * coeff.b - 4 * coeff.a * coeff.c))
        {
            i--;
            continue;
        }
        rts = FuncUnderTest(coeff);
        if (!(CheckRoot(coeff, rts.Root1) && CheckRoot(coeff, rts.Root2)
            && rts.NumOfRoots == TWO_SOL && !CompZero(fabs(rts.Root1-rts.Root2))))
            printf("Error! In test1 with a=%lg, b=%lg, c=%lg\n",
                coeff.a, coeff.b, coeff.c);
    }
}
void Test2(struct Roots (*FuncUnderTest) (struct Coefficients coeff)) //D=0
{
    struct Coefficients coeff = { NAN, NAN, NAN };
    struct Roots rts = { NAN, NAN, INF_SOL };
    double a = 0, b = 0, c = 0;
    for (int i = 0; i < 100; i++)
    {
        a = rand() + 1;
        b = rand() + 1;
        c = rand() + 1;
        coeff.a = a / b;
        coeff.b = b / c;
        coeff.c = coeff.b * coeff.b / (4 * coeff.a);
        rts = FuncUnderTest(coeff);
        if(!(CheckRoot(coeff, rts.Root1) && CheckRoot(coeff, rts.Root2) && rts.NumOfRoots == ONE_SOL))
            printf("Error! In test2 with a=%lg, b=%lg, c=%lg\n",
                coeff.a, coeff.b, coeff.c);
    }
}
void Test3(struct Roots (*FuncUnderTest) (struct Coefficients coeff)) //a=0
{
    struct Coefficients coeff = { NAN, NAN, NAN };
    struct Roots rts = { NAN, NAN, INF_SOL };
    double a = 0, b = 0, c = 0;
    coeff.a = 0;
    for (int i = 0; i < 100; i++)
    {
        a = rand() + 1;
        b = rand() + 1;
        c = rand() + 1;
        coeff.b = b / c;
        coeff.c = a / c;
        rts = FuncUnderTest(coeff);
        if (!(CheckRoot(coeff, rts.Root1) && CheckRoot(coeff, rts.Root2) && rts.NumOfRoots == ONE_SOL))
            printf("Error! In test3 with a=%lg, b=%lg, c=%lg\n",
                coeff.a, coeff.b, coeff.c);
    }
}
void Test4(struct Roots (*FuncUnderTest) (struct Coefficients coeff)) //a=0, b=0, c!=0
{
    struct Coefficients coeff = { NAN, NAN, NAN };
    struct Roots rts = { NAN, NAN, INF_SOL };
    double a = 0, b = 0, c = 0;
    coeff.a = 0;
    coeff.b = 0;
    coeff.c = rand() + 1;
    rts = FuncUnderTest(coeff);
    if(rts.NumOfRoots!=ZERO_SOL)
        printf("Error! In test4 with a=%lg, b=%lg, c=%lg\n",
            coeff.a, coeff.b, coeff.c);
}
void Test5(struct Roots (*FuncUnderTest) (struct Coefficients coeff)) //a=b=c=0
{
    struct Coefficients coeff = { NAN, NAN, NAN };
    struct Roots rts = { NAN, NAN, INF_SOL };
    double a = 0, b = 0, c = 0;
    coeff.a = 0;
    coeff.b = 0;
    coeff.c = 0;
    rts = FuncUnderTest(coeff);
    if(rts.NumOfRoots!=INF_SOL)
        printf("Error! In test5 with a=%lg, b=%lg, c=%lg\n",
            coeff.a, coeff.b, coeff.c);
}
void Test6(struct Roots (*FuncUnderTest) (struct Coefficients coeff)) //D<0, no roots
{
    struct Coefficients coeff = { NAN, NAN, NAN };
    struct Roots rts = { NAN, NAN, INF_SOL };
    double a = 0, b = 0, c = 0;
    for (int i = 0; i < 100; i++)
    {
        a = rand() + 1;
        b = rand() + 1;
        c = rand() + 1;
        coeff.a = a / b;
        coeff.b = b / c;
        coeff.c = coeff.b * coeff.b / (4 * coeff.a) + rand();
        rts = FuncUnderTest(coeff);
        if(rts.NumOfRoots!=ZERO_SOL)
            printf("Error! In test6 with a=%lg, b=%lg, c=%lg\n",
                coeff.a, coeff.b, coeff.c);
    }
}

void StressTest(struct Roots (*FuncUnderTest) (struct Coefficients coeff))
{
    Test1(FuncUnderTest);
    Test2(FuncUnderTest);
    Test3(FuncUnderTest);
    Test4(FuncUnderTest);
    Test5(FuncUnderTest);
    Test6(FuncUnderTest);
    //-------------------------------------------
    printf("If you have no Errors, your function works correctly\n");
}
