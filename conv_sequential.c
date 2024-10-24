#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    // ---- input and malloc A, F ----
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);

    for(int i = 0; i < NA; i++){
        scanf("%d", &A[i]);
    }
    for(int i = 0; i < NF; i++){
        scanf("%d", &F[NF - i - 1]);
    }
    // ---- end input and malloc----
    printf("\n");
    // Create result array
    int Nres = NA - NF + 1;
    int *res = malloc(sizeof(int) * Nres);

    // ---- Sequential Convolution ----
    clock_t start = clock();
    for (int i = 0; i < Nres; i++) {
        res[i] = 0;
        for (int j = 0; j < NF; j++) {
            res[i] += A[i + j] * F[j];
        }
    }
    clock_t end = clock();

    // Print result
    printf("\nResult :\n");
    for (int i = 0; i < Nres; i++) {
        printf("%d\n", res[i]);
    }

    double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Convolution took %f seconds\n", time_taken);
    // ---- end sequential convolution ----

    // ---- free memory ----
    free(F);
    free(A);
    free(res);
    // ---- end free ----
    return 0;
}