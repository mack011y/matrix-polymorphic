#include <stdio.h>
#include "Int.h"
#include "typeInfo.h"

void sum_int(const void* a, const void* b, const void* result) {
    *(int*)result = *(int*)a + *(int*)b;
}

void multiply_int(const void* a, const void* b, const void* result) {
    *(int*)result = *(int*)a * *(int*)b;
}

void multiply_by_scalar_int(const void* a, const double scalar, const void* result) {
    *(int*)result = (int)(*(int*)a * scalar);
}

void print_int(const void* element) {
    printf("%d ", *(int*)element);
}

void printFile_int(const void* element, FILE* file) {
	fprintf(file, "%d ", *(int*)element);
}

void return_neutral_of_sum_int(const void* value) {
    Int* result = (Int*)value;
    result->value = 0;
    value = result;
}

bool is_zero_int(const void* value) {
    Int* int_value = (Int*)value;
    return int_value->value == 0;
}

void scan_int(const void* element) {
    scanf("%d", (int*)element);
}

void scanFile_int(const void* element, FILE* file) {
	fscanf(file, "%d", (int*)element);
}

void divide_int(const void* a, const void* b, const void* result) {
    *(int*)result = *(int*)a / *(int*)b;
}

void negate_int(const void* value, const void* result) {
    *(int*)result = -*(int*)value;
}

typeInfo intType = {
    .size = sizeof(int),
    .sum = sum_int,
    .multiply = multiply_int,
    .multiply_scalar = multiply_by_scalar_int,
    .print = print_int,
    .printFile = printFile_int,
    .return_neutral_of_sum = return_neutral_of_sum_int,
    .is_zero = is_zero_int,
    .scan = scan_int,
    .scanFile = scanFile_int,
    .divide = divide_int,
    .negate = negate_int,
    .type = INT_TYPE
};