#include "SquareSolverTest.h"
int EnterTest(struct RefSolutions* sol, const char* FileName, const int MaxSize)
{
    assert(sol != NULL);
    assert(FileName != "");
    assert(MaxSize >= 1);
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

void UnitTest(struct Roots (*FuncUnderTest) (struct Coefficients coeff), struct RefSolutions *sol, int NumOfTests)
{
    assert(FuncUnderTest != NULL);
    assert(sol != NULL);
    assert(NumOfTests >= 1);
    struct Roots ProbRoots = {NAN, NAN, INF_SOL};
    while(NumOfTests--)
    {
        ProbRoots = FuncUnderTest(sol[NumOfTests].coeff);
        //CheckRoot roots
        if(!((CompZero(sol[NumOfTests].RefRoots.Root1-ProbRoots.Root1) && CompZero(sol[NumOfTests].RefRoots.Root2-ProbRoots.Root2)
        || CompZero(sol[NumOfTests].RefRoots.Root1-ProbRoots.Root2) && CompZero(sol[NumOfTests].RefRoots.Root2-ProbRoots.Root1))
        && ProbRoots.NumOfRoots==sol[NumOfTests].RefRoots.NumOfRoots))
        {
            printf("Error! In test with a=%lg, b=%lg, c=%lg\t"
                "x1ref=%lg, x1=%lg, x2ref=%lg, x2=%lg, NumRootsRef=%d, NumRoots=%d\n",
                sol[NumOfTests].coeff.a, sol[NumOfTests].coeff.b, sol[NumOfTests].coeff.c,
                sol[NumOfTests].RefRoots.Root1, ProbRoots.Root1, sol[NumOfTests].RefRoots.Root2, ProbRoots.Root2,
                sol[NumOfTests].RefRoots.NumOfRoots, ProbRoots.NumOfRoots);
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
    assert(FuncUnderTest != NULL);
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
    assert(FuncUnderTest != NULL);
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
    assert(FuncUnderTest != NULL);
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
    assert(FuncUnderTest != NULL);
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
    assert(FuncUnderTest != NULL);
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
    assert(FuncUnderTest != NULL);
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
    assert(FuncUnderTest != NULL);
    Test1(FuncUnderTest);
    Test2(FuncUnderTest);
    Test3(FuncUnderTest);
    Test4(FuncUnderTest);
    Test5(FuncUnderTest);
    Test6(FuncUnderTest);
    //-------------------------------------------
    printf("If you have no Errors, your function works correctly\n");
}
