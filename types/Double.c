#include <stdio.h>
#include "Double.h"
#include "typeInfo.h"

void sum_double(void* a, void* b, void* result) {
    *(double*)result = *(double*)a + *(double*)b;
}

void multiply_double(void* a, void* b, void* result) {
    *(double*)result = *(double*)a * *(double*)b;
}

void multiply_double_by_scalar(void* a, double scalar, void* result) {
    *(double*)result = *(double*)a * scalar;
}

void print_double(void* element) {
    printf("%lf ", *(double*)element);
}

typeInfo doubleType = {
    .size = sizeof(double),
    .sum = sum_double,
    .multiply = multiply_double,
    .multiply_scalar = multiply_double_by_scalar,
    .print = print_double,
    .type = DOUBLE_TYPE
};