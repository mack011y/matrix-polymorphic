#include <stdio.h>
#include "Double.h"
#include "typeInfo.h"

void sum_double(const void* a, const void* b, const void* result) {
    *(double*)result = *(double*)a + *(double*)b;
}

void multiply_double(const void* a, const void* b, const void* result) {
    *(double*)result = *(double*)a * *(double*)b;
}

void multiply_by_scalar_double(const void* a, const double scalar, const void* result) {
    *(double*)result = *(double*)a * scalar;
}

void print_double(const void* element) {
    printf("%lf ", *(double*)element);
}

void printFile_double(const void* element, FILE* file) {
	fprintf(file, "%lf ", *(double*)element);
}

void return_neutral_of_sum_double(const void* value) {
    Double* d = (Double*)value;
    d->value = 0;
    value = d;
}

bool is_zero_double(const void* value) {
    Double* d = (Double*)value;
    return d->value == 0;
}

void divide_double(const void* numerator, const void* denominator, const void* result) {
    *((double*)result) = *((double*)numerator) / *((double*)denominator);
}

void negate_double(const void* value, const void* result) {
    *((double*)result) = -(*((double*)value));
}

void scan_double(const void* element) {
    scanf("%lf", (double*)element);
}

void scanFile_double(const void* element, FILE* file) {
	fscanf(file, "%lf", (double*)element);
}

typeInfo doubleType = {
    .size = sizeof(double),
    .sum = sum_double,
    .multiply = multiply_double,
    .multiply_scalar = multiply_by_scalar_double,
    .print = print_double,
    .printFile = printFile_double,
    .return_neutral_of_sum = return_neutral_of_sum_double,
    .is_zero = is_zero_double,
    .divide = divide_double,
    .negate = negate_double,
    .scan = scan_double,
    .scanFile = scanFile_double,
    .type = DOUBLE_TYPE
};

typeInfo* getDoubleType() {
  return &doubleType;
}