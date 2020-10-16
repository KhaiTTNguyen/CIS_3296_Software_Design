/** 
 * Program to multiply a matrix times a vector using both
 * MPI to distribute the computation among nodes and OMP
 * to distribute the computation among threads.
*/

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mat.h"
#define min(x, y) ((x)<(y)?(x):(y))

int main(int argc, char* argv[])
{
    int nrows, ncols;
    double *aa, *b, *c;
    double *buffer, ans;
    double *times;
    double total_times;
    int run_index;
    int nruns;
    int myid, master, numprocs;
    double starttime, endtime;
    MPI_Status status;
    int i, j, numsent, sender;
    int anstype, row;
    
    srand(time(0));
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    if (argc > 1) {
        nrows = atoi(argv[1]);
        ncols = nrows;
        aa = (double*)malloc(sizeof(double) * nrows * ncols);
        b = (double*)malloc(sizeof(double) * ncols);
        c = (double*)malloc(sizeof(double) * nrows);
        buffer = (double*)malloc(sizeof(double) * ncols);
        master = 0;
        if (myid == master) {
            // Master Code goes here
            aa = gen_matrix(nrows, ncols);
            starttime = MPI_Wtime();
            numsent = 0;
            /* ---- broadcast out b for "ncols" time to slave processes -----*/
            MPI_Bcast(b, ncols, MPI_DOUBLE, master, MPI_COMM_WORLD);
            for (i = 0; i < min(numprocs-1, nrows); i++) {
	            for (j = 0; j < ncols; j++) {
                    buffer[j] = aa[i * ncols + j];
                }  
                MPI_Send(buffer, ncols, MPI_DOUBLE, i+1, i+1, MPI_COMM_WORLD); // sending collums of "aa" out (till hit numprocs or nros depending on which one is smaller - condition of for-loop)
                numsent++;
            }
            /*------receiving back results------*/ 
            for (i = 0; i < nrows; i++) {
                MPI_Recv(&ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, 
                    MPI_COMM_WORLD, &status); // receive ans to build matrix "c", from any slave process
                sender = status.MPI_SOURCE;
                anstype = status.MPI_TAG;     // take tag or index of c
                c[anstype-1] = ans;           // remember like in SIMD, data is stored in 1D array on hardware
                // got that &ans back, now send more rows of [aa] to that "sender" worker process 
                if (numsent < nrows) {
                    // prep a row to send - buffer
                    for (j = 0; j < ncols; j++) {
                        buffer[j] = aa[numsent*ncols + j];
                    }
                    MPI_Send(buffer, ncols, MPI_DOUBLE, sender, numsent+1, 
                        MPI_COMM_WORLD); // send the buffer, if you read the MPI docs, {"buffer" is address of send buffer, ncols is number of elements to be sent} 
                    numsent++;
                } else {
                    // notify slave process that master is done, MPI_BOTTOM indicate the bottom of the address space
                    MPI_Send(MPI_BOTTOM, 0, MPI_DOUBLE, sender, 0, MPI_COMM_WORLD);
                }
            } 
            endtime = MPI_Wtime();
            printf("%f\n",(endtime - starttime));
        } else {
            // Slave Code goes here
            /**
             * Although the root process and receiver processes do different jobs, 
             * they all call the same MPI_Bcast function. 
             * When the root process (in our example, it was process zero) calls MPI_Bcast, 
             * the "b" vector will be sent to all worker processes. 
             * When all of the receiver processes call MPI_Bcast, "b" variable will be filled in with the data from the master process.
             * 
             * Explaination source:
             * https://mpitutorial.com/tutorials/mpi-broadcast-and-collective-communication/
             */
            MPI_Bcast(b, ncols, MPI_DOUBLE, master, MPI_COMM_WORLD);
            if (myid <= nrows) {
	            while(1) {
	                MPI_Recv(buffer, ncols, MPI_DOUBLE, master, MPI_ANY_TAG, 
		                MPI_COMM_WORLD, &status);
	                if (status.MPI_TAG == 0){
	                    break;
                    }
	                row = status.MPI_TAG;
	                ans = 0.0;
#pragma omp parallel
#pragma omp shared(ans) for reduction(+:ans)
	                for (j = 0; j < ncols; j++) {
	                    ans += buffer[j] * b[j];
	                }
	                MPI_Send(&ans, 1, MPI_DOUBLE, master, row, MPI_COMM_WORLD);
	            }
            }
        }
    } else {
        fprintf(stderr, "Usage matrix_times_vector <size>\n");
    }
    MPI_Finalize();
    return 0;
}
