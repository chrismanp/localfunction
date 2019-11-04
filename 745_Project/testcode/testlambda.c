#include <stdio.h>

#define getBP(bp) asm volatile("#getbp\n\tmovq %%rbp,%[Var]" : [Var] "=r" (bp))
#define setBP(bp) asm volatile("#setbp\n\tmovq %[Var],%%rbp" :: [Var] "r" (bp))

//void * bp;

void runtest(){
    void * bp0;
    int a = 4;
    int b = 5;
    getBP(bp0);
    
    void myfunc (void * bp1) {
        setBP(bp1);
        void myfunc2(void * bp2){
            setBP(bp2);
            int t = 4;
            void myfunc3 (void * bp3){
                setBP(bp3);
                void myfunc4 (void * bp4){
                    setBP(bp4);
                    a = a+1;
                    t = t-1;
                    printf("a : %d : t : %d\n", a, t);
                };
                myfunc4(bp3);
            };
            myfunc3(bp2);
        };
        myfunc2(bp1);
    };
    myfunc(bp0);
}

 
int main() {
    
    runtest();
    return 0;

}

