#include <stdio.h>

void runtest(){
    int a = 4;

    auto myfunc = [&]() {
        a = a + 1;
    };
    myfunc();
    printf("a:%d\n",a);
}

 
int main() {
    
    runtest();
    return 0;

}

