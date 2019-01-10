//
//  main.cpp
//  ProgParalela
//
//  Created by Nacho Martinez on 10/01/2019.
//  Copyright © 2019 Nacho Martinez. All rights reserved.
//
#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 2
#define N 30
long  fib_p(int n)
{
    long x, y;
    int id = omp_get_thread_num();
    //printf("fib = %d\n", id);
    if (n < 2) return n;
    
#pragma omp task shared(x)  // task es de openMP v 3.0
    x = fib_p(n - 1);
#pragma omp task shared (y)
    y = fib_p(n - 2);
#pragma omp taskwait
    return x + y;
    
}

long  fib(int n)
{
    long x, y;
    if (n < 2) return n;
    
    x = fib(n - 1);
    y = fib(n - 2);
    return x + y;
    
}
int main() {
    double time1, time2;
    
    omp_set_num_threads(NUM_THREADS);
    time1 = omp_get_wtime();
    printf("serial fib = %ld\n", fib(N));
    time2 = omp_get_wtime();
    printf("serial: %lf\n", time2 - time1);
    
    time1 = omp_get_wtime();
    //#pragma omp parallel
    {
        //#pragma omp single
        {
            printf("parallel fib = %ld\n", fib_p(N));
        }
    }
    time2 = omp_get_wtime();
    printf("paralel: %lf\n", time2 - time1);
}
