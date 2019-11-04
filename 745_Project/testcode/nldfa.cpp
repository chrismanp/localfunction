#include <stdio.h>

#define ai __attribute__((always_inline))


void myfunc(int a, int b){
    a = a+1;
    b = b -1;
    printf("a : %d\n", a);
 
}

void runtest(int a, int b){
    //int a = 4;
    //int b = 5;
    b = b+1;
    myfunc(a, b);
    printf("a outside : %d\n", a);
}

 
int main(int argc, char**argv) {
    
    int a = argc+1;
    runtest(argc, a);
    return 0;

}

