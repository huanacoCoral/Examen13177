#include <stdio.h>

int sumar(int *x, int *y) {
    return *x + *y;
}

int restar(int *x, int *y) {
    return *x - *y;
}

int multiplicar(int *x, int *y) {
    int resultado = 0;
    for (int i = 0; i < *y; i++) {
        resultado += *x;
    }
    return resultado;
}

float dividir(int *x, int *y) {
    if (*y == 0) {
        printf("Error: División por cero\n");
        return 0;
    }
    float resultado = 0;
    float temp = *x;
    while (temp >= *y) {
        temp -= *y;
        resultado++;
    }
    return resultado;
}

int main() {
    int numero1, numero2;
    numero1 = 8;
    numero2 = 3;
    printf("Suma: %d\n", sumar(&numero1, &numero2));
    printf("Resta: %d\n", restar(&numero1, &numero2));
    printf("Multiplicación: %d\n", multiplicar(&numero1, &numero2));
    printf("División: %.2f\n", dividir(&numero1, &numero2));

    return 0;
}
