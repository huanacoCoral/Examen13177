#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void generar_serie(int *vector, int N) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        vector[i] = (i + 1) * 2;
    }
}

int main() {
    int N;
    printf("Ingrese el número de términos para la serie: ");
    scanf("%d", &N);

    int *vector = (int *)malloc(N * sizeof(int));
    if (vector == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    // Establecer el número de hilos a usar
    omp_set_num_threads(omp_get_max_threads());

    // Generar la serie en paralelo
    generar_serie(vector, N);

    // Imprimir la serie generada
    printf("Serie generada:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");

    free(vector);
    return 0;
}
