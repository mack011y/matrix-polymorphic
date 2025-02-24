#include <stdio.h>
#include "Complex.h"
#include "typeInfo.h"

void sum_complex(void* a, void* b, void* result) {
    Complex* ca = (Complex*)a;
    Complex* cb = (Complex*)b;
    Complex* res = (Complex*)result;
    res->real = ca->real + cb->real;
    res->imaginary = ca->imaginary + cb->imaginary;
}

void multiply_complex(void* a, void* b, void* result) {
    Complex* ca = (Complex*)a;
    Complex* cb = (Complex*)b;
    Complex* res = (Complex*)result;
    res->real = ca->real * cb->real - ca->imaginary * cb->imaginary;
    res->imaginary = ca->real * cb->imaginary + ca->imaginary * cb->real;
}

void multiply_complex_by_scalar(void* a, double scalar, void* result) {
    Complex* ca = (Complex*)a;
    Complex* res = (Complex*)result;
    res->real = ca->real * scalar;
    res->imaginary = ca->imaginary * scalar;
}

void print_complex(void* element) {
    Complex* c = (Complex*)element;
    printf("(%lf + %lfi) ", c->real, c->imaginary);
}

typeInfo complexType = {
    .size = sizeof(Complex),
    .sum = sum_complex,
    .multiply = multiply_complex,
    .multiply_scalar = multiply_complex_by_scalar,
    .print = print_complex,
    .type = COMPLEX_TYPE
};