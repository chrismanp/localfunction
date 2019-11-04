#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "avar.h"

#define getBP(bp) asm volatile("#getbp\n\tmovq %%rbp,%[Var]" : [Var] "=r" (bp))
#define setBP(bp) asm volatile("#setbp\n\tmovq %[Var],%%rbp" :: [Var] "r" (bp))

#define L1D_N (2048)

struct timespec timer_start() {
    struct timespec start_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
    return start_time;
}

// call this function to end a timer, returning nanoseconds elapsed as a long

long timer_end(struct timespec start_time) {
    struct timespec end_time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
    long diffInNanos = (end_time.tv_sec - start_time.tv_sec) * (long)1e9 + (end_time.tv_nsec - start_time.tv_nsec);
    return diffInNanos;
}

int main(){

#if 1
    genA
#endif
    
#if 0
    //void * bp;
    long a[L1D_N];
    //getBP(bp);
    long b[L1D_N]; 
    long c[L1D_N]; 
    long d[L1D_N];
    long e[L1D_N];

    for(int i = 0; i<L1D_N; i++){
        a[i] = 0;
        b[i] = 0;
        c[i] = 0;
        d[i] = 0;
        e[i] = 0;

    }

#endif

    struct timeval t1, t2;
    double elapsedTime;    
 
    int child1 () {
        //setBP(mbp);
#if 0
        for(int i = 0; i<L1D_N; i++){
            a[i]++;
            b[i]++;
            c[i]++;
            d[i]++;
            e[i]++;

        }
#endif

        
        
        
#if 1        
        assignA
#endif
        return 1;
    }
    int res = 0;
    
    //gettimeofday(&t1, NULL);
    struct timespec startTime = timer_start();
    res = child1();
    long nanoTime = timer_end(startTime);
    // gettimeofday(&t2, NULL);

    // compute and print the elapsed time in millisec
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000000.0;      // sec to us
    elapsedTime += (t2.tv_usec - t1.tv_usec);      

    printf( "%ld\n",nanoTime);  
    return 0;
}


