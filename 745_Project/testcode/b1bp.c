#include <stdio.h>

#define getBP(bp) asm volatile("#getbp\n\tmovq %%rbp,%[Var]" : [Var] "=r" (bp))
#define setBP(bp) asm volatile("#setbp\n\tmovq %[Var],%%rbp" :: [Var] "r" (bp))

//void * bp;

int printfunc(int (*f)(), void * bp ){
    printf("Result %d\n", f(bp));
    return 0;
}

int main(){
    void * pbp;
    int a = 10;
    getBP(pbp);

    int child1 (void * mybp) {
        setBP(mybp);
        int b = 5;
        return a + b;
    }


    printfunc(child1, pbp);
    return 0;
}


