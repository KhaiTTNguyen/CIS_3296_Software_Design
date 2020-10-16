#include "mat.h"

#define MAT_SIZE 100

int test_unoptimized(double *a, int arows, int acols,
                     double *b, int brows, int bcols,
                     double *c_actual) {
    double *c_calc = malloc(MAT_SIZE * MAT_SIZE * sizeof(double));

    mmult(c_calc, a, MAT_SIZE, MAT_SIZE, b, MAT_SIZE, MAT_SIZE);

    int are_same = compare_matrices(c_actual, c_calc, MAT_SIZE, MAT_SIZE);

    free(c_calc);

    return are_same;
}

int main(int argc, char *argv[]) {

    FILE *out;
    out = fopen("output.txt", "a+");
    clock_t time_start, time_end;
    double time_res;
    struct timespec start;
    struct timespec end;
    struct timespec res;

    int arr[] = { 100, 300, 500, 1000, 1500, 2000, 2500, 3000}; 

    double * a1 = gen_matrix(100, 100);
    double * b1 = gen_matrix(100, 100);
    double * c1 = malloc(100 * 100 * sizeof(double));
    time_start =  clock(); mmult(c1, a1, 100, 100, b1, 100, 100); time_end = clock();
    time_res = ((double)time_end - (double)time_start) / (double)(CLOCKS_PER_SEC);
    fprintf(out,"%d %.5f", 100, time_res);

    time_start =  clock(); mmult_simd(c1, a1, 100, 100, b1, 100, 100); time_end = clock();
    time_res = ((double)time_end - (double)time_start) / (double)(CLOCKS_PER_SEC);
    fprintf(out," %.5f", time_res);

    clock_gettime(CLOCK_REALTIME, &start); mmult_omp(c1, a1, 100, 100, b1, 100, 100); clock_gettime(CLOCK_REALTIME, &end);
    time_res = (double)deltaTime(&start, &end);
    fprintf(out," %.5f\n", time_res);
    free(a1); free(b1); free(c1);


    // for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++){
    //     a1 = gen_matrix(arr[i], arr[i]);
    //     b1 = gen_matrix(arr[i], arr[i]);
    //     c1 = malloc(arr[i] * arr[i] * sizeof(double));
    //     time_start =  clock(); mmult(c1, a1, arr[i], arr[i], b1, arr[i], arr[i]); time_end = clock();
    //     time_res = ((double)time_end - (double)time_start) / (double)(CLOCKS_PER_SEC);
    //     fprintf(out,"%d %.5f", arr[i], time_res);

    //     time_start =  clock(); mmult_simd(c1, a1, arr[i], arr[i], b1, arr[i], arr[i]); time_end = clock();
    //     time_res = ((double)time_end - (double)time_start) / (double)(CLOCKS_PER_SEC);
    //     fprintf(out," %.5f", time_res);

    //     clock_gettime(CLOCK_REALTIME, &start); mmult_omp(c1, a1, arr[i], arr[i], b1, arr[i], arr[i]); clock_gettime(CLOCK_REALTIME, &end);
    //     time_res = (double)deltaTime(&start, &end);
    //     fprintf(out," %.5f\n", time_res);

    //     memset(a1, 0, arr[i] * arr[i] * sizeof(double)); 
    //     memset(b1, 0, arr[i] * arr[i] * sizeof(double)); 
    //     memset(c1, 0, arr[i] * arr[i] * sizeof(double)); 
    // }
    
    // free(a1); free(b1); free(c1);

    /*----------------------------------------------------------*/
    double *a2 = gen_matrix(200, 200);
    double *b2 = gen_matrix(200, 200);
    double *c2 = malloc(200 * 200 * sizeof(double));
    time_start =  clock(); mmult(c2, a2, 200, 200, b2, 200, 200); time_end = clock();
    time_res = ((double)time_end - (double)time_start) / (double)(CLOCKS_PER_SEC);
    fprintf(out,"%d %.5f", 200, time_res);

    time_start =  clock(); mmult_simd(c2, a2, 200, 200, b2, 200, 200); time_end = clock();
    time_res = ((double)time_end - (double)time_start) / (double)(CLOCKS_PER_SEC);
    fprintf(out," %.5f", time_res);

    clock_gettime(CLOCK_REALTIME, &start); mmult_omp(c2, a2, 200, 200, b2, 200, 200); clock_gettime(CLOCK_REALTIME, &end);
    time_res = (double)deltaTime(&start, &end);
    fprintf(out," %.5f\n", time_res);
    free(a2); free(b2); free(c2);

    // double *a3 = gen_matrix(300, 300);
    // double *b3 = gen_matrix(300, 300);
    // double *c3 = malloc(300 * 300 * sizeof(double));
    // mmult(c3, a3, 300, 300, b3, 300, 300);
    // free(a3); free(b3); free(c3);

    // double *a4 = gen_matrix(400, 400);
    // double *b4 = gen_matrix(400, 400);
    // double *c4 = malloc(400 * 400 * sizeof(double));
    // mmult(c4, a4, 400, 400, b4, 400, 400);
    // free(a4); free(b4); free(c4);

    double *a5 = gen_matrix(500, 500);
    double *b5 = gen_matrix(500, 500);
    double *c5 = malloc(500 * 500 * sizeof(double));
    time_start =  clock(); mmult(c5, a5, 500, 500, b5, 500, 500); time_end = clock();
    time_res = ((double)time_end - (double)time_start) / (double)(CLOCKS_PER_SEC);
    fprintf(out,"%d %.5f", 500, time_res);

    time_start =  clock(); mmult_simd(c5, a5, 500, 500, b5, 500, 500); time_end = clock();
    time_res = ((double)time_end - (double)time_start) / (double)(CLOCKS_PER_SEC);
    fprintf(out," %.5f", time_res);

    clock_gettime(CLOCK_REALTIME, &start); mmult_omp(c5, a5, 500, 500, b5, 500, 500); clock_gettime(CLOCK_REALTIME, &end);
    time_res = (double)deltaTime(&start, &end);
    fprintf(out," %.5f\n", time_res);
    free(a5); free(b5); free(c5);

    // double *a6 = gen_matrix(600, 600);
    // double *b6 = gen_matrix(600, 600);
    // double *c6 = malloc(600 * 600 * sizeof(double));
    // mmult(c6, a6, 600, 600, b6, 600, 600);
    // free(a6); free(b6); free(c6);

    double *a7 = gen_matrix(700, 700);
    double *b7 = gen_matrix(700, 700);
    double *c7 = malloc(700 * 700 * sizeof(double));
    time_start =  clock(); mmult(c7, a7, 700, 700, b7, 700, 700); time_end = clock();
    time_res = ((double)time_end - (double)time_start) / (double)(CLOCKS_PER_SEC);
    fprintf(out,"%d %.5f", 700, time_res);

    time_start =  clock(); mmult_simd(c7, a7, 700, 700, b7, 700, 700); time_end = clock();
    time_res = ((double)time_end - (double)time_start) / (double)(CLOCKS_PER_SEC);
    fprintf(out," %.5f", time_res);

    clock_gettime(CLOCK_REALTIME, &start); mmult_omp(c7, a7, 700, 700, b7, 700, 700); clock_gettime(CLOCK_REALTIME, &end);
    time_res = (double)deltaTime(&start, &end);
    fprintf(out," %.5f\n", time_res);
    free(a7); free(b7); free(c7);

    printf("Got down to 700");
    // double *a8 = gen_matrix(800, 800);
    // double *b8 = gen_matrix(800, 800);
    // double *c8 = malloc(800 * 800 * sizeof(double));
    // mmult(c8, a8, 800, 800, b8, 800, 800);
    // free(a8); free(b8); free(c8);

    // double *a9 = gen_matrix(900, 900);
    // double *b9 = gen_matrix(900, 900);
    // double *c9 = malloc(900 * 900 * sizeof(double));
    // mmult(c9, a9, 900, 900, b9, 900, 900);
    // free(a9); free(b9); free(c9);
    
    double *a1000 = gen_matrix(1000, 1000);
    double *b1000 = gen_matrix(1000, 1000);
    double *c1000 = malloc(1000 * 1000 * sizeof(double));
    time_start =  clock(); mmult(c1000, a1000, 1000, 1000, b1000, 1000, 1000); time_end = clock();
    time_res = ((double)time_end - (double)time_start) / (double)(CLOCKS_PER_SEC);
    fprintf(out,"%d %.5f", 1000, time_res);

    time_start =  clock(); mmult_simd(c1000, a1000, 1000, 1000, b1000, 1000, 1000); time_end = clock();
    time_res = ((double)time_end - (double)time_start) / (double)(CLOCKS_PER_SEC);
    fprintf(out," %.5f", time_res);

    clock_gettime(CLOCK_REALTIME, &start); mmult_omp(c1000, a1000, 1000, 1000, b1000, 1000, 1000); clock_gettime(CLOCK_REALTIME, &end);
    time_res = (double)deltaTime(&start, &end);
    fprintf(out," %.5f\n", time_res);
    free(a1000); free(b1000); free(c1000);

    // double *a1500 = gen_matrix(1500, 1500);
    // double *b1500 = gen_matrix(1500, 1500);
    // double *c1500 = malloc(1500 * 1500 * sizeof(double));
    // mmult(c1500, a1500, 1500, 1500, b1500, 1500, 1500);
    // free(a1500); free(b1500); free(c1500);

    // double *a2000 = gen_matrix(2000, 2000);
    // double *b2000 = gen_matrix(2000, 2000);
    // double *c2000 = malloc(2000 * 2000 * sizeof(double));
    // mmult(c2000, a2000, 2000, 2000, b2000, 2000, 2000);
    // free(a2000); free(b2000); free(c2000);  

    // double *a2500 = gen_matrix(2500, 2500);
    // double *b2500 = gen_matrix(2500, 2500);
    // double *c2500 = malloc(2500 * 2500 * sizeof(double));
    // mmult(c2500, a2500, 2500, 2500, b2500, 2500, 2500);
    // free(a2500); free(b2500); free(c2500);

    double *a3000 = gen_matrix(3000, 3000);
    double *b3000 = gen_matrix(3000, 3000);
    double *c3000 = malloc(3000 * 3000 * sizeof(double));
    time_start =  clock(); mmult(c3000, a3000, 3000, 3000, b3000, 3000, 3000); time_end = clock();
    time_res = ((double)time_end - (double)time_start) / (double)(CLOCKS_PER_SEC);
    fprintf(out,"%d %.5f", 3000, time_res);

    time_start =  clock(); mmult_simd(c3000, a3000, 3000, 3000, b3000, 3000, 3000); time_end = clock();
    time_res = ((double)time_end - (double)time_start) / (double)(CLOCKS_PER_SEC);
    fprintf(out," %.5f", time_res);

    clock_gettime(CLOCK_REALTIME, &start); mmult_omp(c3000, a3000, 3000, 3000, b3000, 3000, 3000); clock_gettime(CLOCK_REALTIME, &end);
    time_res = (double)deltaTime(&start, &end);
    fprintf(out," %.5f\n", time_res);
    free(a3000); free(b3000); free(c3000);

	
    /*double *a5000 = gen_matrix(5000, 5000);
    double *b5000 = gen_matrix(5000, 5000);
    double *c5000 = malloc(5000 * 5000 * sizeof(double));
    mmult(c5000, a5000, 5000, 5000, b5000, 5000, 5000);
    free(a5000); free(b5000); free(c5000);

    double *a2000 = gen_matrix(2000, 500);
    double *b2000 = gen_matrix(500, 2000);
    double *c2000 = malloc(2000 * 2000 * sizeof(double));
    mmult(c2000, a2000, 2000, 500, b2000, 500, 2000);
    free(a2000); free(b2000); free(c2000);

    double *a4000 = gen_matrix(4000, 500);
    double *b4000 = gen_matrix(500, 4000);
    double *c4000 = malloc(4000 * 4000 * sizeof(double));
    mmult(c4000, a4000, 4000, 500, b4000, 500, 4000);
    free(a4000); free(b4000); free(c4000);

    double *a6000 = gen_matrix(6000, 500);
    double *b6000 = gen_matrix(500, 500);
    double *c6000 = malloc(6000 * 6000 * sizeof(double));
    mmult(c6000, a6000, 6000, 500, b6000, 500, 6000);
    free(a6000); free(b6000); free(c6000);

    double *a8000 = gen_matrix(8000, 500);
    double *b8000 = gen_matrix(500, 8000);
    double *c8000 = malloc(8000 * 8000 * sizeof(double));
    mmult(c8000, a8000, 8000, 500, b8000, 500, 8000);
    free(a8000); free(b8000); free(c8000);

    double *a10000 = gen_matrix(10000, 10000);     
    double *b10000 = gen_matrix(10000, 10000);
    double *c10000 = malloc(10000 * 10000 * sizeof(double));
    mmult(c10000, a10000, 10000, 10000, b10000, 10000, 10000);
    free(a10000); free(b10000); free(c10000);
    */
   fclose(out); 
}
