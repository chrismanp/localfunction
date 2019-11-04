//#include <iostream>
#include "stdio.h"


class MyClass {
private :
    int _a;
    int _b;

public:
    MyClass(int a, int b):_a(a),_b(b){}

    void print()
    {
        //std::cout << "MyClass " <<  _a << " and " << _b << std::endl;
        printf( "MyClass %d and %d\n", _a, _b);
    }    
};

int main (int argc, char ** argv){

    void (MyClass::*pmf)() = &MyClass::print;

    MyClass myclass(10, 20);
    
    (myclass.*pmf)();
    
        //pmf();

}
