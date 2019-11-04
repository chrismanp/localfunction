#include <stdio.h>



struct Link {
    int *a;
};


int printfunc(int (*f)(), struct Link * link ){
    printf("Result %d\n", f(link));
    return 0;
}

int main(){
    struct Link link;
    int a = 10;
    link.a = &a;

    int child1 (struct Link * link) {
        int b = 5;
        return *(link->a) + b;
    }


    printfunc(child1, &link);
    return 0;
}


