#include "SquareSolverTest.h"
#include "SquareSolver.h"
#include "Input.h"
#include "Output.h"

void RunProgram(int argc, char** argv)
{
    assert(argv != NULL);
    assert(*argv != NULL);

    struct RefSolutions *refsol = NULL;
    
    int NumOfTests = 0;
    
    struct Coefficients coeff = {NAN, NAN, ZERO_SOL};
    
    int FlagIndx = 0;

    if(argc>1)
    {
        while(argv[1][FlagIndx]!='-' && argv[1][FlagIndx]!='\n')
            FlagIndx++;

        if(argv[1][FlagIndx]!='\n')
            FlagIndx++;

        switch(argv[1][FlagIndx])
        {
            case 'h':
                printf("-s: Start Square equation solver\n-t: Start Testing\n");

                break;

            case 't':
            case '\n':
                NumOfTests = EnterTest(&refsol, "UnitTest.txt");

                UnitTest(SolveSqr, refsol, NumOfTests);
                StressTest(SolveSqr);

                break;

            case 's':
                EnterCoefficients(&coeff);
                PrintRoots(SolveSqr(coeff));

                break;

            default:
                printf("-h: Flag Helps Information\n-s: Start Square equation solver\n-t: Start Testing\n");

        }
    }
    else
    {
        EnterCoefficients(&coeff);
        PrintRoots(SolveSqr(coeff));
    }
}   

int main(int argc, char** argv)
{
    
    RunProgram(argc, argv);

    return 0;
}