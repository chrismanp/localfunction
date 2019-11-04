#include <stdio.h>
#include <string.h>
#include <malloc.h>

// Static Link

struct Link {
    int *a;
};


int fillstack(int (*f)(),  struct Link * inlink){
    long a = 1;
    long b = 2;
    long c = 3;
    long d = 4;
    long e = 5;
    long g = 6;

    printf ("Results : %d\n", f(50, inlink));

    return 0;

}

int (*genAddN(int n, struct Link ** locallink)) (){
    int m = n;
    struct Link * link = malloc (sizeof(struct Link));
    link->a = malloc(sizeof(int));
    *link->a = n;
    *locallink = link;

    int addN(int k, struct Link * inlink){
        return *(inlink->a) + k;
    }
        
    return addN;
}


int main(){
    struct Link * mylink;
  
           
    int (*add100)() = genAddN(100, &mylink);

    fillstack(add100, mylink);
    
    free(mylink->a);
    free(mylink);
    return 0;
}


