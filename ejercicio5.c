#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4 // Tamaño de la matriz y del vector

void imprimir_matriz(int matriz[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void imprimir_vector(int vector[N]) {
    for (int i = 0; i < N; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int rank, size;
    int matriz[N][N], vector[N], resultado[N];
    int filas_por_proceso, inicio_fila, fin_fila;
    int buffer_local[N], resultado_local[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Inicializar matriz y vector en el proceso raíz
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matriz[i][j] = i * N + j + 1; // Valores de ejemplo
            }
            vector[i] = i + 1; // Valores de ejemplo
        }

        printf("Matriz:\n");
        imprimir_matriz(matriz);

        printf("Vector:\n");
        imprimir_vector(vector);
    }

    // Distribuir el vector a todos los procesos
    MPI_Bcast(vector, N, MPI_INT, 0, MPI_COMM_WORLD);

    // Calcular la cantidad de filas que cada proceso manejará
    filas_por_proceso = N / size;
    inicio_fila = rank * filas_por_proceso;
    fin_fila = (rank + 1) * filas_por_proceso;

    // Distribuir las filas de la matriz a los procesos
    MPI_Scatter(matriz, filas_por_proceso * N, MPI_INT, buffer_local, filas_por_proceso * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Multiplicación local de la matriz y el vector
    for (int i = 0; i < filas_por_proceso; i++) {
        resultado_local[i] = 0;
        for (int j = 0; j < N; j++) {
            resultado_local[i] += buffer_local[i * N + j] * vector[j];
        }
    }

    // Recolectar los resultados en el proceso raíz
    MPI_Gather(resultado_local, filas_por_proceso, MPI_INT, resultado, filas_por_proceso, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Resultado:\n");
        imprimir_vector(resultado);
    }

    MPI_Finalize();
    return 0;
  }

