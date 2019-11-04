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

struct timeval t1, t2;
double elapsedTime;    
long nanoTime;
struct timespec startTime;

int main(){

    startTime = timer_start();
    genA
 
    int child1 () {
        assignA
        return 1;
    }
    int res = 0;
    


    res = child1();
    nanoTime = timer_end(startTime);
    
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000000.0;      // sec to us
    elapsedTime += (t2.tv_usec - t1.tv_usec);      

    printf( "%ld\n",nanoTime);  
    return 0;
}


