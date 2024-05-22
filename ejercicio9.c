#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void generate_series(int start, int count, int* series) {
    for (int i = 0; i < count; i++) {
        series[i] = start + 2 * i;
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 18;  // Número total de términos deseados
    int terms_per_process = N / size;
    int extra = N % size;

    int start, count;
    if (rank < extra) {
        start = rank * (terms_per_process + 1) * 2 + 2;
        count = terms_per_process + 1;
    } else {
        start = rank * terms_per_process * 2 + extra * 2 + 2;
        count = terms_per_process;
    }

    int* partial_series = (int*)malloc(count * sizeof(int));
    generate_series(start, count, partial_series);

    int* recvcounts = NULL;
    int* displs = NULL;
    if (rank == 0) {
        recvcounts = (int*)malloc(size * sizeof(int));
        displs = (int*)malloc(size * sizeof(int));

        for (int i = 0; i < size; i++) {
            if (i < extra) {
                recvcounts[i] = (terms_per_process + 1);
            } else {
                recvcounts[i] = terms_per_process;
            }
        }

        displs[0] = 0;
        for (int i = 1; i < size; i++) {
            displs[i] = displs[i - 1] + recvcounts[i - 1];
        }
    }

    int* complete_series = NULL;
    if (rank == 0) {
        complete_series = (int*)malloc(N * sizeof(int));
    }

    MPI_Gatherv(partial_series, count, MPI_INT, complete_series, recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Serie completa: ");
        for (int i = 0; i < N; i++) {
            printf("%d ", complete_series[i]);
        }
        printf("\n");

        free(complete_series);
        free(recvcounts);
        free(displs);
    }

    free(partial_series);

    MPI_Finalize();
    return 0;
}

