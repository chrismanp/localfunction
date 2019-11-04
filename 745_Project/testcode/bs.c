#include <stdio.h>

#define getBP(bp) asm volatile("#getbp\n\tmovq %%rbp,%[Var]" : [Var] "=r" (bp))
#define setBP(bp) asm volatile("#setbp\n\tmovq %[Var],%%rbp" :: [Var] "r" (bp))

void * bp;

void runtest(){
    int a = 4;
    getBP(bp);
    
    void myfunc () {
        setBP(bp);
        a=a+1;
    };
    myfunc();
    printf("a:%d\n",a);
}

 
int main() {
    
    runtest();
    return 0;

}

