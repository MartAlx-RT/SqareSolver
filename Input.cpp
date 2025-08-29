#include "Input.h"


//#include "SquareSolverTest.h"


enum Status NumToStatus(int Num)
{
    switch(Num)
    {
        
        case -1:
        return INF_SOL;
        break;
    
        case 0:
        return ZERO_SOL;
        break;
    
        case 1:
        return ONE_SOL;
        break;
    
        case 2:
        return TWO_SOL;
        break;
    
        default:
        assert("Wrong Test File!!!!!!!!11");
        }
    
    return INF_SOL;
}


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


void StrClear(char* str)
{
    assert(str != NULL);

    for (int i = 0; i < BUFF;i++)
        str[i] = 0;
}

int FindDot(char* str, int StrLen)
{
    assert(str != NULL);
    assert(StrLen >= 1);

    StrLen--;

    while(str[StrLen]!='.' && StrLen--);

    if(StrLen>=0)
        return StrLen;

    return -1;
}

double StrToDouble(char* str1, int StrLen)
{
    int MinusFlag = 1;
    char *str = NULL;

    assert(str1 != NULL);
    assert(StrLen >= 1);

    if(str1[0]=='-')
    {
        str = str1 + 1;
        StrLen--;
        MinusFlag = -1;
    }

    else
        str = str1;

    double Num = 0;

    int DotIndx = FindDot(str, StrLen);

    int powr = 0;

    assert(DotIndx != 0 && "Wrong number format!!!!!!!111");
    assert(DotIndx != StrLen - 1 && "Wrong number format!!!!!!!111");
    
    if(DotIndx!=-1)
    {
        powr = DotIndx + 1 - StrLen;

        for (int i = StrLen-1; i > DotIndx; i--, powr++)
            Num += (double)(str[i] - '0') * pow(10, powr);
    
    }

    assert(powr == 0);
    
    if(DotIndx==-1)
        DotIndx = StrLen;
    //powr--;
    for (int i = DotIndx - 1; i >= 0; i--, powr++)
        Num += (double)(str[i] - '0') * pow(10, powr);

    return MinusFlag * Num;
}

bool EnterStrOfNum(char* str)
{

    StrClear(str);

    int i = 0;
    bool DotFlag = true;

    char c = getchar();
    
    if(c=='-')
    {
        str[i++] = '-';
        c = getchar();
    }

    while (i < BUFF && ('0'<=c && c<='9' || c=='.' && DotFlag))
    {
        str[i++] = c;
        
        if(c=='.')
            DotFlag = false;

        c = getchar();
    }

    assert(i < BUFF && "Too big number!");

    if(c=='\n')
        return true;

    StrClear(str);
    
    return false;
}

void EnterDoubleWithCheck(double* x)
{
    char str[BUFF] = "";
    
    while(EnterStrOfNum(str)!=true)
    {
        printf("You're silly, I'm too, so try again plz\n");
        while(getchar()!='\n');
    }

    *x = StrToDouble(str, strlen(str));
}


void EnterCoefficients(struct Coefficients* coeff)
{
    assert(coeff != NULL);

    printf("This is the square equation solver\n"
           "Warning! Numbers less than %g are equal to zero in this program\n"
           "The normal view of square equation is:\n"
           "ax^2+bx+c=0\n", EPS);


    printf("Please, enter a:");
    EnterDoubleWithCheck(&(coeff->a));

    printf("Please, enter b:");
    EnterDoubleWithCheck(&(coeff->b));

    printf("Please, enter c:");
    EnterDoubleWithCheck(&(coeff->c));
}
