#include "stdio.h"

int foo(int * d)
{
    int a = 0;
    int b = 10;
    
    return *d;
}




int main(int argc, char ** argv)
{
    int d = 4;    

    printf( "foo : %d\n", foo(&d));    
    return 0;
}

