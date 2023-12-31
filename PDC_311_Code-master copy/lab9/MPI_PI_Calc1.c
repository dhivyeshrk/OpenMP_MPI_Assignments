#include <stdio.h>
#include <mpi.h>

#define N 1E7
#define d 1E-7
#define d2 1E-14

int main (int argc, char* argv[])
{
    int rank, size, error, i;
    printf("Dhivyesh R K 2021BCS0084\n");
    printf("Ref : https://github.com/kiwenlau/MPI_PI/blob/master\n");
    double pi=0.0, result=0.0, sum=0.0, begin=0.0, end=0.0, x2;
    
    error=MPI_Init (&argc, &argv);
    
    //Get process ID
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    
    //Get processes Number
    MPI_Comm_size (MPI_COMM_WORLD, &size);

    //Synchronize all processes and get the begin time
    MPI_Barrier(MPI_COMM_WORLD);
    begin = MPI_Wtime();
    
    //Each process will caculate a part of the sum
    for (i=rank; i<N; i+=size)
    {
        x2=d2*i*i;
        result+=1.0/(1.0+x2);
    }
    
    //Sum up all results
    MPI_Reduce(&result, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    //Synchronize all processes and get the end time
    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();
    
    //Caculate and print PI
    if (rank==0)
    {
        pi=4*d*sum;
        printf("np=%2d;    Time=%fs;    PI=%lf\n", size, end-begin, pi);
    }
    
    error=MPI_Finalize();
    
    return 0;
}
