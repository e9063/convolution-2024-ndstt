#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Function declarations for sequential and parallel convolution
void sequential_convolution(int *A, int *F, int NA, int NF);
void parallel_convolution(int *A, int *F, int NA, int NF);

int main() {
    int NA, NF;
    
    // Reading input sizes
    scanf("%d %d", &NA, &NF);

    // Allocate memory for arrays
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);

    // Reading array A
    for(int i = 0; i < NA; i++) {
        scanf("%d", &A[i]);
    }

    // Reading filter F (reversed)
    for(int i = 0; i < NF; i++) {
        scanf("%d", &F[NF - i - 1]);
    }

    printf("NA = %d\nNF = %d\n",NA,NF);
    // ---- Sequential Convolution Benchmark ----
    clock_t start_seq = clock();
    sequential_convolution(A, F, NA, NF);
    clock_t end_seq = clock();
    double seq_time = ((double)(end_seq - start_seq)) / CLOCKS_PER_SEC;
    printf("Sequential Convolution took %f seconds\n", seq_time);

    // ---- Parallel Convolution Benchmark ----
    double start_par = omp_get_wtime();
    parallel_convolution(A, F, NA, NF);
    double end_par = omp_get_wtime();
    double par_time = end_par - start_par;
    printf("Parallel Convolution took %f seconds\n", par_time);

    // ---- Speedup Calculation ----
    double speedup = seq_time / par_time;
    printf("Speedup: %f\n", speedup);

    // Free memory
    free(A);
    free(F);

    return 0;
}

// Sequential convolution function
void sequential_convolution(int *A, int *F, int NA, int NF) {
    int Nres = NA - NF + 1;
    int *res = malloc(sizeof(int) * Nres);

    for (int i = 0; i < Nres; i++) {
        res[i] = 0;
        for (int j = 0; j < NF; j++) {
            res[i] += A[i + j] * F[j];
        }
    }

    free(res);
}

// Parallel convolution function
void parallel_convolution(int *A, int *F, int NA, int NF) {
    int Nres = NA - NF + 1;
    int *res = malloc(sizeof(int) * Nres);

    omp_set_num_threads(4);
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < Nres; i++) {
        res[i] = 0;
        for (int j = 0; j < NF; j++) {
            res[i] += A[i + j] * F[j];
        }
    }

    free(res);
}
