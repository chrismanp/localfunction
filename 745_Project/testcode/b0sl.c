#include <stdio.h>

// Static Link

struct Link1 {
    int *a;
};

struct Link2 {
    struct Link1 * link1;
    int *b;
};

struct Link3{
    struct Link2 * link2;
    int *c;
};

struct Link4{
    struct Link3 * link3;
    int *d;
};

struct Link5{
    struct Link4 * link4;
    int *e;
};

int main(){
    int a = 10;
    struct Link1 link1;
    link1.a = &a;
    int child1 (struct Link1 * link1) {
        int b = 10;
        struct Link2 link2;
        link2.link1 = link1;
        link2.b = &b;

        int child2 (struct Link2 * link2) {
            int c = 10;
            struct Link3 link3;
            link3.link2 =link2;
            link3.c = &c;

            int child3(struct Link3 * link3) {
                int d = 10;
                struct Link4 link4;
                link4.link3 = link3;
                link4.d = &d;
                
                int child4(struct Link4 * link4){
                    int e = 10;
                    struct Link5 link5;
                    link5.link4 = link4;
                    link5.e  = &e;
                    
                    int child5(struct Link5 * link5){
                        return *(link5->link4->link3->link2->link1->a) + *(link5->link4->link3->link2->b) + *(link5->link4->link3->c) + *(link5->link4->d) + *(link5->e);  
                    }
                    return child5(&link5);
                }
                return child4(&link4);
            }
            return child3(&link3);
        }
        return child2(&link2);
    }
    printf( "%d\n",  child1(&link1));

    return 0;
}


