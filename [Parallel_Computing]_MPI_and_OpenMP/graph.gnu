set terminal png size 800,600 
set output 'MPI_vs_MPI-OMP.png'

# Key means label...
#set key inside bottom right
set xlabel 'Matrix size'
set ylabel 'Time (sec)'
set title 'Matrix multiplication speed on Wolfgang Cluster'
plot  "mpi_out.txt" using 1:2 title 'MPI' with linespoint, "mpi_out.txt" using 1:3 title 'MPI/OMP' with linespoint
