#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int inside_circle = 0;
    int total_points = 1000000; // Adjust total_points as needed

    srand(time(NULL));
    printf("-----DHIVYESH R K---------2021BCS0084----\n");
    for (int i = 0; i < total_points; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        if ((x * x + y * y) <= 1) {
            inside_circle++;
        }
    }

    double pi_estimate = 4.0 * inside_circle / total_points;

    printf("Estimated value of pi (serial version): %f\n", pi_estimate);
    printf("Classical value of pi: %f\n", 3.14159265358979323846);

    return 0;
}

