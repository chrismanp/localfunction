//#include <stdio.h>

//struct x {int x, int y};
// struct_lfp x { int x };

typedef int (* const fp_ci )();
//typedef int (* _Atomic fp_ai )();
typedef int (* _Local  fp_li )(int, int);
typedef int (* _Atomic fp_ai )(int, int);


void print(int x, int y, fp_ai func )
{
    int res = func(x,y);
    //printf("result : %d\n", res);
}
int main()
{
    int x=100, y=200;

    int add (int i, int j)
    {
        return (i + j);
    }

    int sub (int i, int j)
    {
        return (i - j);
    }

    fp_ai func_add = _Atomic(add);
    print(x,y,func_add);
    fp_ai func_sub = _Atomic(sub);
    print(x,y,func_sub);
    return 0;
}
