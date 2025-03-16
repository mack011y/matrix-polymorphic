#include <stdio.h>
#include "Complex.h"
#include "typeInfo.h"

void sum_complex(const void* a, const void* b, const void* result) {
    Complex* ca = (Complex*)a;
    Complex* cb = (Complex*)b;
    Complex* res = (Complex*)result;
    res->real = ca->real + cb->real;
    res->imaginary = ca->imaginary + cb->imaginary;
}

void multiply_complex(const void* a, const void* b, const void* result) {
    Complex* ca = (Complex*)a;
    Complex* cb = (Complex*)b;
    Complex* res = (Complex*)result;
    res->real = ca->real * cb->real - ca->imaginary * cb->imaginary;
    res->imaginary = ca->real * cb->imaginary + ca->imaginary * cb->real;
}

void multiply_by_scalar_complex(const void* a, const double scalar, const void* result) {
    Complex* ca = (Complex*)a;
    Complex* res = (Complex*)result;
    res->real = ca->real * scalar;
    res->imaginary = ca->imaginary * scalar;
}

void scan_complex(const void* value) {
    scanf("%lf, %lf", &((Complex*)value)->real,  &((Complex*)value)->imaginary);
}

void scanFile_complex(const void* value, FILE* file) {
    fscanf(file, "%lf %lf", &((Complex*)value)->real,  &((Complex*)value)->imaginary);
}

void print_complex(const void* element) {
    Complex* c = (Complex*)element;
    printf("(%lf + %lfi) ", c->real, c->imaginary);
}


void printFile_complex(const void* element, FILE* file) {
    Complex* c = (Complex*)element;
    printf("(%lf + %lfi) ", c->real, c->imaginary);
}

void return_neutral_of_sum_complex(const void* value) {
    Complex* c = (Complex*)value;
    c->real = 0.0;
    c->imaginary = 0.0;
    value = c;
}

bool is_zero_complex(const void* value) {
    Complex* c = (Complex*)value;
    return (c->real == 0.0 && c->imaginary == 0.0);
}

void divide_complex(const void* numerator, const void* denominator, const void* result) {
    Complex* num = (Complex*)numerator;
    Complex* denom = (Complex*)denominator;
    Complex* res = (Complex*)result;

    double denom_mag = denom->real * denom->real + denom->imaginary * denom->imaginary;
    if (denom_mag == 0) {
        printf("Division by zero error\n");
        return;
    }

    res->real = (num->real * denom->real + num->imaginary * denom->imaginary) / denom_mag;
    res->imaginary = (num->imaginary * denom->real - num->real * denom->imaginary) / denom_mag;
}

void negate_complex(const void* value, const void* result){
    Complex* v = (Complex*)value;
    Complex* r = (Complex*)result;
    r->real = -v->real;
    r->imaginary = -v->imaginary;
}



typeInfo complexType = {
    .size = sizeof(Complex),
    .sum = sum_complex,
    .multiply = multiply_complex,
    .multiply_scalar = multiply_by_scalar_complex,
    .print = print_complex,
    .return_neutral_of_sum = return_neutral_of_sum_complex,
    .is_zero = is_zero_complex,
    .divide = divide_complex,
    .negate = negate_complex,
    .type = COMPLEX_TYPE
};

typeInfo* getComplexType() {
    return &complexType;
}