#include "stdio.h"

#define getBP(bp) asm volatile("#getbp\n\tmovq %%rbp,%[Var]" : [Var] "=r" (bp))
#define setBP(bp) asm volatile("#setbp\n\tmovq %[Var],%%rbp" :: [Var] "r" (bp))

void * bp;

int main()
{
    int d = 4;
    int k = 10;
    int t = 4;
    int r;
    r = 4;
    d = 100;
    k = 100;
    t = 100;

    getBP(bp);
    
    int foo()
    {
        setBP(bp);
        r =2;
        int c = 20;
        int a = 12;
        int b = 10;
        d = d+10;
        k = k+100;
        t = t+1000;
        return d;
    }
    foo();
    printf( "d|k|t : %d|%d|%d\n", d,k,t);    
    return d;
}


