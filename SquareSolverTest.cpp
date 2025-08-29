#include "SquareSolverTest.h"


bool CheckRoot(struct RefSolutions sol, struct Roots ProbRoots)
{
    if(sol.RefRoots.NumOfRoots > ZERO_SOL)
    {
    return ((CompZero(sol.RefRoots.Root1 - ProbRoots.Root1) && CompZero(sol.RefRoots.Root2 - ProbRoots.Root2)
    || CompZero(sol.RefRoots.Root1 - ProbRoots.Root2) && CompZero(sol.RefRoots.Root2 - ProbRoots.Root1))
    && ProbRoots.NumOfRoots == sol.RefRoots.NumOfRoots);
    }
    return (sol.RefRoots.Root1 != sol.RefRoots.Root1 && sol.RefRoots.Root2 != sol.RefRoots.Root2
    && ProbRoots.NumOfRoots==ProbRoots.NumOfRoots);
}

void PrintErrorMsg(struct RefSolutions sol, struct Roots ProbRoots)
{
    printf("Error! In test with a=%lg, b=%lg, c=%lg\t"
                "x1ref=%lg, x1=%lg, x2ref=%lg, x2=%lg, NumRootsRef=%d, NumRoots=%d\n",
                sol.coeff.a, sol.coeff.b, sol.coeff.c,
                sol.RefRoots.Root1, ProbRoots.Root1, sol.RefRoots.Root2, ProbRoots.Root2,
                sol.RefRoots.NumOfRoots, ProbRoots.NumOfRoots);
}
void PrintErrorMsg(int TestNumb, struct Coefficients coeff)
{
    printf("Error! In test%d with a=%lg, b=%lg, c=%lg\n", TestNumb,
                coeff.a, coeff.b, coeff.c);
}

void UnitTest(struct Roots (*FuncUnderTest) (struct Coefficients coeff), struct RefSolutions *sol, int NumOfTests)
{
    assert(FuncUnderTest != NULL);
    assert(sol != NULL);
    assert(NumOfTests >= 1);

    struct Roots ProbRoots = {NAN, NAN, INF_SOL};
    //struct Roots RefRoots = {NAN, NAN, INF_SOL};

    while(NumOfTests--)
    {
        ProbRoots = FuncUnderTest(sol[NumOfTests].coeff);
        //RefRoots = sol[NumOfTests].RefRoots;

        if(!CheckRoot(sol[NumOfTests], ProbRoots))
        {
            PrintErrorMsg(sol[NumOfTests], ProbRoots);
        }
    }
    
    printf("\nIf you have no errors (see above) your function works correctly\n");
}


void RandGeneratePositive(double* a, double* b, double* c)
{
    double x, y, z;
    x = y = z = 0;

    x = rand() + 1;
    y = rand() + 1;
    z = rand() + 1;

    *a = x / y;
    *b = y / z;
    *c = x / z;
}



void Test1(struct Roots (*FuncUnderTest) (struct Coefficients coeff)) //D>0, two roots
{
    assert(FuncUnderTest != NULL);
    
    struct Coefficients coeff = { NAN, NAN, NAN };
    struct Roots roots = { NAN, NAN, INF_SOL };
    
    double a = 0, b = 0, c = 0;
    
    //test1 (two roots)
    for (int i = 0; i < 100; i++)
    {
        RandGeneratePositive(&a, &b, &c);

        coeff.a = a;
        coeff.b = b;
        coeff.c = -c;

        if (CompZero(coeff.b * coeff.b - 4 * coeff.a * coeff.c))
        {
            i--; 
            continue;
        }
        
        roots = FuncUnderTest(coeff);
        
        if (!(SubstituteRoot(coeff, roots.Root1) && SubstituteRoot(coeff, roots.Root2)
            && roots.NumOfRoots == TWO_SOL && !CompZero(fabs(roots.Root1-roots.Root2))))
            PrintErrorMsg(1, coeff);
    }
}
void Test2(struct Roots (*FuncUnderTest) (struct Coefficients coeff)) //D=0
{
    assert(FuncUnderTest != NULL);
    
    struct Coefficients coeff = { NAN, NAN, NAN };
    struct Roots roots = { NAN, NAN, INF_SOL };
    
    double a = 0, b = 0, c = 0;
    
    for (int i = 0; i < 100; i++)
    {
        RandGeneratePositive(&a, &b, &c);

        coeff.a = a;
        coeff.b = b;

        coeff.c = coeff.b * coeff.b / (4 * coeff.a);
        
        roots = FuncUnderTest(coeff);
        
        if(!(SubstituteRoot(coeff, roots.Root1) && SubstituteRoot(coeff, roots.Root2) && roots.NumOfRoots == ONE_SOL))
            PrintErrorMsg(2, coeff);
    }
}
void Test3(struct Roots (*FuncUnderTest) (struct Coefficients coeff)) //a=0
{
    assert(FuncUnderTest != NULL);

    struct Coefficients coeff = { NAN, NAN, NAN };
    struct Roots roots = { NAN, NAN, INF_SOL };
    
    double a = 0, b = 0, c = 0;
    
    coeff.a = 0;
    
    for (int i = 0; i < 100; i++)
    {
        RandGeneratePositive(&a, &b, &c);
        
        coeff.b = b;
        coeff.c = c;
        
        roots = FuncUnderTest(coeff);
        
        if (!(SubstituteRoot(coeff, roots.Root1) && SubstituteRoot(coeff, roots.Root2) && roots.NumOfRoots == ONE_SOL))
            PrintErrorMsg(3, coeff);
    }
}
void Test4(struct Roots (*FuncUnderTest) (struct Coefficients coeff)) //a=0, b=0, c!=0
{
    assert(FuncUnderTest != NULL);
    
    struct Coefficients coeff = { NAN, NAN, NAN };
    struct Roots roots = { NAN, NAN, INF_SOL };
    
    double a = 0, b = 0, c = 0;
    
    coeff.a = 0;
    coeff.b = 0;
    coeff.c = rand() + 1;
    
    roots = FuncUnderTest(coeff);
    
    if(roots.NumOfRoots!=ZERO_SOL)
        PrintErrorMsg(4, coeff);
}
void Test5(struct Roots (*FuncUnderTest) (struct Coefficients coeff)) //a=b=c=0
{
    assert(FuncUnderTest != NULL);
    
    struct Coefficients coeff = { NAN, NAN, NAN };
    struct Roots roots = { NAN, NAN, INF_SOL };
    
    double a = 0, b = 0, c = 0;
    
    coeff.a = 0;
    coeff.b = 0;
    coeff.c = 0;
    
    roots = FuncUnderTest(coeff);
    
    if(roots.NumOfRoots!=INF_SOL)
        PrintErrorMsg(5, coeff);
}
void Test6(struct Roots (*FuncUnderTest) (struct Coefficients coeff)) //D<0, no roots
{
    assert(FuncUnderTest != NULL);
    
    struct Coefficients coeff = { NAN, NAN, NAN };
    struct Roots roots = { NAN, NAN, INF_SOL };
    
    double a = 0, b = 0, c = 0;
    
    for (int i = 0; i < 100; i++)
    {
        RandGeneratePositive(&a, &b, &c);
        
        coeff.a = a;
        coeff.b = b;
        coeff.c = coeff.b * coeff.b / (4 * coeff.a) + rand();
        
        roots = FuncUnderTest(coeff);
        
        if(roots.NumOfRoots!=ZERO_SOL)
            PrintErrorMsg(6, coeff);
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