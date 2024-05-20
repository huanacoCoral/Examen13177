#include <stdio.h>
#include <omp.h>

// Función para multiplicar dos números en base a sumas
int multiplicar(int a, int b) {
    int resultado = 0;
    #pragma omp parallel for reduction(+:resultado) //usado paralelimo
    for (int i = 0; i < b; i++) {
        resultado += a;
    }
    return resultado;
}

// Función para dividir dos números en base a restas
int division(int a, int b) {
    int cociente = 0;
    int temp = a;
    
    #pragma omp parallel
    {
        int local_cociente = 0;

        #pragma omp for
        for (int i = 0; i <= a; i++) {
            while (temp >= b) {
                temp -= b;
                local_cociente++;
            }
        }

        #pragma omp atomic
        cociente += local_cociente;
    }

    return cociente;
}

int main() {
    int num1 = 10;
    int num2 = 2;

    printf("Multiplicacion: %d\n", multiplicar(num1, num2));
    printf("Division: %d\n", division(num1, num2));

    return 0;
}

