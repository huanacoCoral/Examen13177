#include <iostream>

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
        std::cout << "Error: División por cero" << std::endl;
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
    int numero1 = 8;
    int numero2 = 3;
    std::cout << "Suma: " << sumar(&numero1, &numero2) << std::endl;
    std::cout << "Resta: " << restar(&numero1, &numero2) << std::endl;
    std::cout << "Multiplicación: " << multiplicar(&numero1, &numero2) << std::endl;
    std::cout << "División: " << dividir(&numero1, &numero2) << std::endl;

    return 0;
}

