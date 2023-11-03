#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>
double f(double x)
{
    return 2*x+3;
}
int main(int argc, char *argv[])
{
     printf("Name: Kanak Khandelwal\n");
        printf("Roll no.: 2021BCS0102\n\n");
    int n = 16; //or 128 or 512 or 1024
    double a = 0.0;
    double b = 2.0;
    double h = (b - a) / n;
    double integral = 0.0;
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("%d",size);
    int local_n = n / size;
    double local_a = a + rank * local_n * h;
    double local_b = local_a + local_n * h;
    double local_integral = 0.0;
    clock_t start_time,
        end_time;
    if (size == 1)
    {
        // Serial execution
        start_time = clock();
        for (int i = 0; i < n; i++)
        {
            double x1 = a + i * h;
            double x2 = a + (i + 1) * h;
            integral += (f(x1) + f(x2)) * h / 2.0;
        }
        end_time = clock();
        double cpu_time_used = ((double)(end_time - start_time)) /
                               CLOCKS_PER_SEC;
        printf("Serial: Estimated value of the integral  = %lf\n", integral);
        printf("Serial: Execution Time = %lf seconds\n", cpu_time_used);
    }
    else
    {
        // Parallel execution
        start_time = clock();
        for (int i = 0; i < local_n; i++)
        {
            double x1 = local_a + i * h;
            double x2 = local_a + (i + 1) * h;
            local_integral += (f(x1) + f(x2)) * h / 2.0;
        }
        MPI_Reduce(&local_integral, &integral, 1, MPI_DOUBLE, MPI_SUM,
                   size - 1, MPI_COMM_WORLD);
        end_time = clock();
        if (rank == size - 1)
        {
            double cpu_time_used = ((double)(end_time - start_time)) /
                                   CLOCKS_PER_SEC;
            printf("Parallel: Estimated value of the integral = %lf\n", integral);
            printf("Parallel: Execution Time = %lf seconds\n",
                   cpu_time_used);
        }
    }
    MPI_Finalize();
    return 0;
}