
#include "SquareLib.h"

bool CompZero(double x)
{
    return (fabs(x) < EPS);
}

static inline void ScanfDoubleWithCheck(double* x) //TODO сканф с проверкой //TODO assert(x), assert(x != y)
{
    assert(x != NULL);
    char c = 0;
    while((scanf("%lg", x) == 0 || (c = getchar()) != '\n' ) && c != ' ' && c != '\t')
    {
        printf("You silly\n");
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
    ScanfDoubleWithCheck(&(coeff->a));
    printf("Please, enter b:");
    ScanfDoubleWithCheck(&(coeff->b));
    printf("Please, enter c:");
    ScanfDoubleWithCheck(&(coeff->c));
}

struct Roots SolveLinear(struct Coefficients coeff)
{
    struct Roots rts = {0, 0, ZERO_SOL};
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
    struct Roots rts = {0, 0, ZERO_SOL};
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

