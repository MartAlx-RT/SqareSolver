#include "SquareSolver.h"

bool SubstituteRoot(struct Coefficients coeff, double PossibleRoot)
{
    if (fabs(coeff.a * PossibleRoot * PossibleRoot + coeff.b * PossibleRoot + coeff.c)<EPS2)
        return true;
    return false;
}

bool CompZero(double x)
{
    return (fabs(x) < EPS);
}

void CorrectSolution(struct Roots* roots)
{
    if(CompZero(roots->Root1))
        roots->Root1 = 0;

    if(CompZero(roots->Root2))
        roots->Root2 = 0;
    
}

struct Roots SolveLinear(struct Coefficients coeff) //TODO struct Coefficients* coeff && not return struct
{
    struct Roots roots = {NAN, NAN, INF_SOL};

    if (CompZero(coeff.a) && CompZero(coeff.b) && CompZero(coeff.c))
    {
        roots.NumOfRoots =INF_SOL;
        roots.Root1 = NAN;
        roots.Root2 = NAN;
        return roots;
    }

    if (CompZero(coeff.b))
    {
        roots.NumOfRoots = ZERO_SOL;
        roots.Root1 = NAN;
        roots.Root2 = NAN;
        return roots;
    }

    roots.NumOfRoots = ONE_SOL;
    roots.Root1 = roots.Root2 = -coeff.c / coeff.b;

    CorrectSolution(&roots);
    return roots;
}
struct Roots SolveSqr(struct Coefficients coeff)
{
    if (CompZero(coeff.a))
    {
        return SolveLinear(coeff);
    }

    struct Roots roots = {NAN, NAN, ZERO_SOL};

    double Discr = coeff.b * coeff.b - 4 * coeff.a * coeff.c;


    if (Discr > EPS)
    {
        Discr = sqrt(Discr);

        roots.Root1 = (-coeff.b + Discr) / (2 * coeff.a);
        roots.Root2 = (-coeff.b - Discr) / (2 * coeff.a);
        roots.NumOfRoots = TWO_SOL;
        CorrectSolution(&roots);
        return roots;
    }

    else if (Discr < -EPS)
    {
        roots.NumOfRoots = ZERO_SOL;
        CorrectSolution(&roots);
        return roots;
    }

    else
    {
        roots.Root1 = roots.Root2 = -coeff.b / (2 * coeff.a);
        roots.NumOfRoots = ONE_SOL;
        CorrectSolution(&roots);
        return roots;
    }
}

