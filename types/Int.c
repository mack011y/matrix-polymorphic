#include <stdio.h>
#include "Int.h"
#include "typeInfo.h"

void sum_int(void* a, void* b, void* result) {
    *(int*)result = *(int*)a + *(int*)b;
}

void multiply_int(void* a, void* b, void* result) {
    *(int*)result = *(int*)a * *(int*)b;
}

void multiply_int_by_scalar(void* a, double scalar, void* result) {
    *(int*)result = (int)(*(int*)a * scalar);
}

void print_int(void* element) {
    printf("%d ", *(int*)element);
}

typeInfo intType = {
    .size = sizeof(int),
    .sum = sum_int,
    .multiply = multiply_int,
    .multiply_scalar = multiply_int_by_scalar,
    .print = print_int,
    .type = INT_TYPE
};