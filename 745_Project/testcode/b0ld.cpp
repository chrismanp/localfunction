#include <stdio.h>

//#define getBP(bp) asm volatile("#getbp\n\tmovq %%rbp,%[Var]" : [Var] "=r" (bp))
//#define setBP(bp) asm volatile("#setbp\n\tmovq %[Var],%%rbp" :: [Var] "r" (bp))

void * bp;

int main(){
    int a = 10;
    auto child1 =[&] () {
        int b = 10;
        
        auto child2=[&] () {
            int c = 10;
            
            auto child3=[&]() {
                int d = 10;
                
                auto child4 =[&](){
                    int e = 10;
                    
                    auto child5 =[&](){
                        return a + b + c + d + e;
                    };
                    return child5();
                };
                return child4();
            };
            return child3();
        };
        return child2();
    };
    printf( "%d\n",  child1());
    
    return 0;
}


