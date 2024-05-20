#include <stdio.h>
#include <omp.h>

#define N 4 // Dimensiones de la matriz y el vector

// Función para imprimir una matriz
void printMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Función para multiplicar una matriz por un vector utilizando OpenMP
void multiplyMatrixVector(int matrix[N][N], int vector[N], int result[N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        int sum = 0;
        for (int j = 0; j < N; j++) {
            sum += matrix[i][j] * vector[j];
        }
        result[i] = sum;
    }
}

int main() {
    int matrix[N][N] = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 16}};
    int vector[N] = {1, 2, 3, 4};
    int result[N];

    printf("Matriz:");
    printMatrix(matrix);

    printf("\nVector:");
    for (int i = 0; i < N; i++) {
        printf("%d\n", vector[i]);
    }

    multiplyMatrixVector(matrix, vector, result);

    printf("\nResultado:");
    for (int i = 0; i < N; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}
