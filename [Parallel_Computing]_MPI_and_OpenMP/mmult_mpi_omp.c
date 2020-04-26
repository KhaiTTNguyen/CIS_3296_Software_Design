/** 
 * Incomplete program to multiply a matrix times a matrix using both
 * MPI to distribute the computation among nodes and OMP
 * to distribute the computation among threads.
 */

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#define min(x, y) ((x)<(y)?(x):(y))

#include "mat.h"

int main(int argc, char* argv[])
{
    int nrows, ncols;
    double *aa;	/* the A matrix */
    double *bb;	/* the B matrix */
    double *cc1;	/* A x B computed using the omp-mpi code you write */
    double *cc2;	/* A x B computed using the conventional algorithm */
    int myid;
    double starttime, endtime;
    MPI_Status status;

    /* insert other global variables here */
    int master = 0;
    int numsent = 0;
    int sender = 0;
    int row = 0; // MPI tag
    int numprocs = 10;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    if (argc > 1) {
        nrows = atoi(argv[1]);
        ncols = nrows;
        double* buffer = (double*)malloc(sizeof(double) * ncols);
        double* response = (double*)malloc(sizeof(double) * nrows);
        aa = gen_matrix(nrows, ncols);
        bb = gen_matrix(nrows, ncols);
        cc1 = malloc(sizeof(double) * nrows * nrows); 

        if (myid == master) {
            // Master Code goes here
            starttime = MPI_Wtime();
            /* -------------------Insert your master code-------------- */
            MPI_Bcast(bb, nrows * ncols, MPI_DOUBLE, master, MPI_COMM_WORLD);
            // SENDING ROWS - minimum between numprocs - 1 or all nrows
            for(int i = 0; i < min(numprocs - 1, nrows);i++) {
                // fill up the buffer for this given row
                for(int j=0;j<ncols; j++) {
                    buffer[j] = aa[i*ncols + j];
                }
                // send the buffer starting at ID 1 (can't send from master to master), and increment numsent to keep track of the # of rows sent 
                MPI_Send(buffer, ncols, MPI_DOUBLE, i+1, ++numsent, MPI_COMM_WORLD);
            }

            // RECEVING ROWS
            for(int i = 0; i < nrows; i++){
                
                // receive a buffer from the child
                MPI_Recv(response, nrows, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

                // determine who sent this buffer (MPI is non-deterministic, any of the child procs could have sent this)
                sender = status.MPI_SOURCE;

                // get the index of the row that was sent
                row = status.MPI_TAG;

                // fill up the row of cc1 this response corresponds to
                for(int l=0; l < ncols; l++){
                    cc1[row*nrows + l] = response[l];
                }

                // if we didnt send all the rows (i.e there were more rows than procs)
                if(numsent < nrows){
                    // fill up a buffer using the next row of aa
                    for(int l =0; l < nrows; l++){
                        buffer[l] = aa[numsent*nrows + l];
                    }
                    // send it to a child
                    MPI_Send(buffer, ncols, MPI_DOUBLE, sender, ++numsent, MPI_COMM_WORLD);
                } else { 
                    // we are done, signal that we are complete by sending a 0 tag
                    MPI_Send(MPI_BOTTOM, 0 , MPI_DOUBLE , sender, 0, MPI_COMM_WORLD);
                }
            }    

            endtime = MPI_Wtime();
            printf("MPI & OMP integrated takes %f\n",(endtime - starttime));
            // cc2  = malloc(sizeof(double) * nrows * nrows);
            // mmult(cc2, aa, nrows, ncols, bb, ncols, nrows);
            // compare_matrices(cc2, cc1, nrows, nrows);

        } else {
            /* ------------------------Slave Code ------------------------- */
            MPI_Bcast(bb, nrows * ncols, MPI_DOUBLE, master, MPI_COMM_WORLD);
            // exit if there were more processes than rows...
            if(myid <= nrows) { 
                // run indefinitely
                while(1){
                    // receive a row from the master 
                    MPI_Recv(buffer, ncols, MPI_DOUBLE, master, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                    // if the tag sent is 0, break
                    if(status.MPI_TAG == 0){
                        break;
                    }
                    // get the id of the row we sent (remember we sent it to proc + 1, so the row is tag - 1
                    row = status.MPI_TAG - 1;
                    
                    int i,j,k,l;
                    double sum;
                    // VECTOR x MATRIX and place it in response
	                #pragma omp parallel default(none) private(i,j,k,l,sum) shared(nrows,ncols,buffer,bb,response)
                    #pragma omp for
                    // for (i=0; i<nrows; i++){
                    //     sum = 0.0;
                    //     for (j=0; j<ncols; j++) {
                    //        sum += bb[row*ncols+i] * buffer[j];
                    //     }
                    //     response[i] = sum;   
                    // } /*-- End of parallel for --*/
                    // for (int k = 0; k < ncols; k++)  {  
                    //     response[k] = 0.0;  
                    // } 
                    for (i = 0; i < 1; i++) {  
                        for (j = 0; j < ncols; j++)  {  
                            response[i*ncols + j] = 0;  
                        }for (k = 0; k < nrows; k++)  {  
                            for (l = 0; l < ncols; l++) {     
                                response[i*ncols + l] += buffer[i*ncols + k] * bb[k*ncols + l];
                            }
                        }
                    }

                    // send this response back to master with the approriate row tag
                    MPI_Send(response, nrows, MPI_DOUBLE, master, row, MPI_COMM_WORLD);
                }
            }
        }
    } else {
        fprintf(stderr, "Usage matrix_times_vector <size>\n");
    }
    MPI_Finalize();
    return 0;
}
