#include "stdio.h"

#define getBP(bp) asm volatile("#getbp\n\tmovq %%rbp,%[Var]" : [Var] "=r" (bp))
#define setBP(bp) asm volatile("#setbp\n\tmovq %[Var],%%rbp" :: [Var] "r" (bp))

void * bp;


int main(int argc, char ** argv)
{
    int d = 4;
    getBP(bp);
    
    int test(){
        foo();
    }

    int foo()
    {
        setBP(bp);
        d = d*2;
        int a = 1;
        int b = 10;        
        void bar(){
            d = d*2;
            a = 16;
        }
        bar();
        return d;
    }
    test();
    foo();
    bar();
    printf( "foo : %d\n", d);    
    return 0;
}


