#include <stdio.h>

void runtest(){
    int a = 4;
    int b = 5;

    auto myfunc = [&]() {
        auto myfunc2 = [&](){
            int t = 4;
            auto myfunc3 = [&] (){
                auto myfunc4 = [&] (){
                    a = a+1;
                    t = t-1;
                    printf("a : %d : t : %d\n", a, t);
                };
                myfunc4();
            };
            myfunc3();
        };
        myfunc2();
    };
    myfunc();
}

 
int main() {
    
    runtest();
    return 0;

}

