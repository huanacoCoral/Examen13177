#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int MASTER = 0;
    int N = 10; // Número de términos de Fibonacci a calcular

    if (rank == MASTER) {
        // Procesador MASTER
        int* fib_series = (int*)malloc(N * sizeof(int));
        int term;
        
        for (int i = 0; i < N; i++) {
            int worker = (i % (size - 1)) + 1; // Distribuye trabajos entre los SLAVES
            MPI_Send(&i, 1, MPI_INT, worker, 0, MPI_COMM_WORLD);
            MPI_Recv(&term, 1, MPI_INT, worker, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            fib_series[i] = term;
        }

        printf("Serie de Fibonacci: ");
        for (int i = 0; i < N; i++) {
            printf("%d ", fib_series[i]);
        }
        printf("\n");

        free(fib_series);

        // Indicar a los esclavos que finalicen
        term = -1;
        for (int i = 1; i < size; i++) {
            MPI_Send(&term, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

    } else {
        // Procesadores SLAVE
        int n;
        while (1) {
            MPI_Recv(&n, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (n == -1) {
                break; // Terminar el proceso si recibe la señal de finalización
            }
            int result = fibonacci(n);
            MPI_Send(&result, 1, MPI_INT, MASTER, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
