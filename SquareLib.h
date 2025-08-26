#include <math.h>

const double EPS = 1e-10; // Error for CompZero function
const double EPS2 = 1e-10; // Error for CompZero in UnitTest

enum Status
{
    INF_SOL = -1,
    ZERO_SOL = 0,
    ONE_SOL = 1,
    TWO_SOL = 2
};

static inline bool CompZero(double x);

static inline void ScanfDoubleWithCheck(double *x);



struct Roots
{
    double Root1 = NAN, Root2 = NAN;
    enum Status NumOfRoots = ZERO_SOL;
};

struct Coefficients
{
    double a = NAN, b = NAN, c = NAN;
};

struct RefSolutions
{
    struct Coefficients coeff = {NAN, NAN, NAN};
    struct Roots RefRoots = {NAN, NAN, INF_SOL};
};


void EnterCoefficients(struct Coefficients *coeff);

struct Roots SolveLinear(struct Coefficients coeff);
struct Roots SolveSqr(struct Coefficients coeff);

void PrintRoots(struct Roots rts);


int EnterTest(struct RefSolutions *sol, const char *FileName, const int MaxSize);

void UnitTest(struct Roots (*FuncUnderTest)(struct Coefficients coeff), struct RefSolutions *sol, int NumOfTests);

bool CheckRoot(struct Coefficients coeff, double PossibleRoot);

void Test1(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
void Test2(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
void Test3(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
void Test4(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
void Test5(struct Roots (*FuncUnderTest)(struct Coefficients coeff));
void Test6(struct Roots (*FuncUnderTest)(struct Coefficients coeff));

void StressTest(struct Roots (*FuncUnderTest)(struct Coefficients coeff));