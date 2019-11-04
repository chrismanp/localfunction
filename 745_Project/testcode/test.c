#include "stdio.h"

struct Mystruct {
    int a ;
    int b ;
    int c ;
    int d ;
} ;

struct Mystruct mystruct;

int main(int argc, char ** argv)
{
    mystruct.d = 7;
    
    
    int foo()
    {
        int b = 10;
        mystruct.d = b;
        return mystruct.d;
    }

    printf( "foo : %d\n", foo());    
    return 0;
}


