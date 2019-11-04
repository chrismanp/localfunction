#include <stdio.h>

#define getBP(bp) asm volatile("#getbp\n\tmovq %%rbp,%[Var]" : [Var] "=r" (bp))
#define setBP(bp) asm volatile("#setbp\n\tmovq %[Var],%%rbp" :: [Var] "r" (bp))

#define ai __attribute__((always_inline))

void * bp;

void runtest(int a, int b){
    //void * bp;
    a = a + 0;
    b = b + 1;
    getBP(bp);
    
    void myfunc(int a, int b) {
    //void myfunc(void * bp0, ) {
        setBP(bp);
        a = a+1;
        b = b-1;
        printf("a : %d\n", a);
    };
    
    myfunc(a, b);
    //myfunc(bp);
    printf("a outside : %d\n", a);
}

 
int main(int argc, char ** argv) {
    int a = argc+1;
    runtest(argc, a);
    return 0;

}

