#include <stdio.h>

#define getBP(bp) asm volatile("#getbp\n\tmovq %%rbp,%[Var]" : [Var] "=r" (bp))
#define setBP(bp) asm volatile("#setbp\n\tmovq %[Var],%%rbp" :: [Var] "r" (bp))

void * bp;


int main(){
    int a = 10;
    getBP(bp);
    int child1 () {
        setBP(bp);
        int b = 10;

        int child2 () {
            setBP(bp);
            int c = 10;

            int child3() {
                setBP(bp);
                int d = 10;
                
                int child4(){
                    setBP(bp);
                    int e = 10;
                    
                    int child5(){
                        setBP(bp);
                        return a + b + c+d +e;
                    }
                    return child5();
                }
                return child4();
            }
            return child3();
        }
        return child2();
    }
    printf( "%d\n",  child1());

    return 0;
}


