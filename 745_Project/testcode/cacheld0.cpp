#include <stdio.h>
#include <sys/time.h> 
#include <time.h>
#include "avar.h"

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
struct timespec startTime;
long nanoTime;


int main(){
    genA


    auto child1 = [&] () {
        assignA
        return 1;

    };

    int res = 0;
    
    startTime = timer_start();
    res = child1();
    nanoTime = timer_end(startTime);
    

    printf( "%ld\n",nanoTime);
    //printf( "%d:%lf\n",res,elapsedTime);    
 
    return 0;
}


