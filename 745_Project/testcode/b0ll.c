#include <stdio.h>

// Lamda lifting

int main(){
    int a = 10;

    int child1 (int *a) {
        int b = 10;

        int child2 (int *a, int *b) {
            int c = 10;

            int child3(int *a, int *b, int *c) {
                int d = 10;
                
                int child4(int *a, int *b, int * c, int *d){
                    int e = 10;
                    
                    int child5(int *a, int *b, int *c, int *d, int *e){
                        return *a + *b + *c + *d + *e;  
                    }
                    return child5(a, b, c, d, &e);
                }
                return child4(a, b, c, &d);
            }
            return child3(a, b, &c);
        }
        return child2(a, &b);
    }
    printf( "%d\n",  child1(&a));

    return 0;
}
