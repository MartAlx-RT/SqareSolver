#include "CommonVar.h"
#include "Out.h"


void PrintRoots(struct Roots roots)
{

    switch (roots.NumOfRoots)
    {

        case INF_SOL:
        printf("Has infinity Solutions\n");
        break;

        case ZERO_SOL:
        printf("Doesn't have any Solutions\n");
        break;

        case ONE_SOL:
        printf("One solution, x=%g\n", roots.Root1);
        break;

        case TWO_SOL:
        printf("Two different Solutions, Root1=%g, Root2=%g\n", roots.Root1, roots.Root2);
        break;

        default:
        printf("Invalid value of Number of roots! You can't have %d sol.\n", roots.NumOfRoots);
    }
}

