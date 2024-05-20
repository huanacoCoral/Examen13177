#include <stdio.h>
#include <mpi.h>
#include <math.h>

double calcular_pi(int inicio, int fin) {
    double suma = 0.0;
    for (int i = inicio; i <= fin; i++) {
        suma += 1.0 / (i * i);
    }
    return suma;
}

int main(int argc, char *argv[]) {
    int rank, size, n, inicio, fin;
    double pi_local, pi_global;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Ingrese el número de términos para la aproximación de Pi: ");
        scanf("%d", &n);
    }

    // Enviamos n desde el proceso 0 a todos los demás
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculamos la porción de la suma que corresponde a cada proceso
    int terminos_por_proceso = n / size;
    inicio = rank * terminos_por_proceso + 1;
    fin = (rank + 1) * terminos_por_proceso;

    // Calculamos la suma local en cada proceso
    pi_local = calcular_pi(inicio, fin);

    // Sumamos todas las sumas locales usando MPI_Reduce
    MPI_Reduce(&pi_local, &pi_global, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Calculamos el valor final de Pi
        pi_global = sqrt(6.0 * pi_global);

        // Imprimimos el resultado
        printf("La aproximación de Pi con %d términos es: %.15f\n", n, pi_global);
    }

    MPI_Finalize();
    return 0;
}
