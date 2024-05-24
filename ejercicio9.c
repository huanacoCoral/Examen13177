#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

// Función para generar y mostrar la serie
void generandoCadena(int start_cadena, int end_cadena, int paso_cadena, int proceso_id) {
    for (int i = start_cadena; i <= end_cadena; i += paso_cadena) {
        printf("Proceso %d: %d\n", proceso_id, i);
    }
}

int main(int argc, char *argv[]) {
    int proceso_id, num_procesos;
    const int elementos_por_proceso = 8; // Número de elementos en cada porción de la serie

    // Inicialización de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &proceso_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procesos);

    // Cálculo del número total de elementos en la serie
    const int total_elementos_serie = elementos_por_proceso * num_procesos * 2;

    // Determinación del inicio y fin de la serie para cada procesador
    const int start_cadena = proceso_id * elementos_por_proceso * 2 + 2;
    int end_cadena = start_cadena + (elementos_por_proceso * 2 - 2);

    // Ajuste del valor de fin si excede el total de elementos
    if (end_cadena > total_elementos_serie) {
        end_cadena = total_elementos_serie;
    }

    // Información de depuración
    printf("Proceso %d: inicio = %d, fin = %d\n", proceso_id, start_cadena, end_cadena);

    // Generación y visualización de la serie
    generandoCadena(start_cadena, end_cadena, 2, proceso_id);

    // Finalización de MPI
    MPI_Finalize();

    return 0;
}

