#include <stdio.h>
#include <malloc.h>

#define getBP(bp) asm volatile("#getbp\n\tmovq %%rbp,%[Var]" : [Var] "=r" (bp))
#define setBP(bp) asm volatile("#setbp\n\tmovq %[Var],%%rbp" :: [Var] "r" (bp))

//#define reg2var(var) asm volatile("#reg2var\n\tmov %%ecx,%[Var]" : [Var] "=r" (var)) 
//#define var2reg(var) asm volatile("#var2reg\n\tmov %[Var],%%ecx" :: [Var] "r" (var)) 

void * gbp;

#define ef __attribute__ ((escape_function))

#define ulihandler __attribute__ ((user_level_interrupt)) void


//#define nss __attribute__ ((no_split_stack)) 

struct mystruct {
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int a1;
    int b2;
    int c2;
    int d2;
    int e2;
    int f2;
};

struct mystruct structA;


//ulihandler test()  {
//    int a = 4;/
//}

void * dummybp;

int fillstack(int (*f)()){
    long a = 1;
    long b = 2;
    long c = 3;
    long d = 4;
    long e = 5;
    long g = 6;
    printf ("Results : %d\n", f(50));

    return 0;

}

ef int (*genAddN(int n)) (){
    setBP(&structA);
    int m = n;       
       
    ef int addN(int k){
        setBP(&structA);
        return m + k;
    }
        
    return addN;
}

int main(){
    void * newstack =  malloc ( 13 * sizeof(int));

    int (*add100)() = genAddN(100);

    fillstack(add100);

    return 0;
}





