#include "stdio.h"

#define getBP(bp) asm volatile("#getbp\n\tmovq %%rbp,%[Var]" : [Var] "=r" (bp))
#define setBP(bp) asm volatile("#setbp\n\tmovq %[Var],%%rbp" :: [Var] "r" (bp))

void * bp;


int foobar();

int main(int argc, char ** argv)
{
    getBP(bp);
    int d = 4;
    
    
    int foo()
    {
        setBP(bp);
        d = d *2;
        
        int bar(){
            setBP(bp);
            d = d*2;
            return d;
        }
        int a = 10;  

        bar();
        return a;
    }
    //foo();
    printf( "foo : %d\n", foo());    
 
    printf("d : %d\n", d);
    return 0;
}


int foobar(){
    int c = 8;
    return c;
}
