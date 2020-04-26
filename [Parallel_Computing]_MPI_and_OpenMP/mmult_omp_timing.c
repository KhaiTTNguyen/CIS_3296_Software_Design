/**
 * This file compares the time to multiply matrices
 * both unoptimized and with OMP. 
 */

#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <stdlib.h>

#include "mat.h"

int main(int argc, char* argv[]) {
    /*struct timespec start; 
    struct timespec end;
    struct timespec res;
    double *a, *b, *c1, *c2;
    int n;
    double times[2];
    if (argc > 1) {
        n = atoi(argv[1]);
        a = gen_matrix(n, n);
        b = gen_matrix(n, n);
        c1 = malloc(sizeof(double) * n * n);
        c2 = malloc(sizeof(double) * n * n);
        clock_gettime(CLOCK_REALTIME, &start);
        mmult(c1, a, n, n, b, n, n);
        clock_gettime(CLOCK_REALTIME, &end);
        times[0] = deltaTime(&start, &end);
        printf("%d %f", n, times[0]);
        clock_gettime(CLOCK_REALTIME, &start);
        mmult_omp(c2, a, n, n, b, n, n);
        clock_gettime(CLOCK_REALTIME, &end);
        times[1] = deltaTime(&start, &end);
        printf(" %f", times[1]);
        printf("\n");
        compare_matrices(c1, c2, n, n);
    } else {
        fprintf(stderr, "Usage %s <n>\n", argv[0]);
    }*/

    struct timespec start;
    struct timespec end;
    struct timespec res;
    double *a, *b, *c1, *c2;
    double times[2];
    int n1, m1, n2, m2;
    if (argc > 1) {
        FILE *f1 = fopen(argv[1], "r");
        FILE *f2 = fopen(argv[2], "r");
        a = read_matrix_from_file(argv[1]);
        b = read_matrix_from_file(argv[2]);
        fscanf(f1, "%d %d", &n1, &m1);
        fscanf(f2, "%d %d", &n2, &m2);
        c1 = malloc(sizeof(double) * n1 * m1);
        c2 = malloc(sizeof(double) * n2 * m2);

        clock_gettime(CLOCK_REALTIME, &start);
        mmult(c1, a, n1, m1, b, n2, m2);
        clock_gettime(CLOCK_REALTIME, &end);
        times[0] = deltaTime(&start, &end);
        printf("%d %f", n1, times[0]);
        
        /* Open file & append time for OMP */
        clock_gettime(CLOCK_REALTIME, &start);
        mmult_omp(c2, a, n1, m1, b, n2, m2);
        clock_gettime(CLOCK_REALTIME, &end);
        times[1] = deltaTime(&start, &end);
        printf(" %f", times[1]);

        printf("\n");
        compare_matrices(c1, c2, n1, m2);
    } else {
        fprintf(stderr, "Usage %s <n>\n", argv[0]);
    }
} 

