#include <stdio.h>

void runtest(int a , int b){
    b = b + 1;

    auto myfunc = [&]() {
        a = a+1;
        b = b-1;
        printf("a : %d\n", a);
    };
    myfunc();
    printf("a outside : %d\n", a);
}

 
int main(int argc, char ** argv) {
    
    int a = argc + 1;
    runtest(argc, a);
    return 0;

}

