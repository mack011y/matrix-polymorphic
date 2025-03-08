#ifndef INT_H
#define INT_H

#include "typeInfo.h"

void sum_int(const void* a, const void* b, const void* result);
void multiply_int(const void* a, const void* b, const void* result);
void multiply_by_scalar_int(const void* a, const double scalar, const void* result);
void print_int(const void* element);
void printFile_int(const void* element, FILE* file);
void return_neutral_of_sum_int(const void* value);
bool is_zero_int(const void* value);
void divide_int(const void* numerator, const void* denominator, const void* result);
void negate_int(const void* value, const void* result);
void scan_int(const void* element);
void scanFile_int(const void* element, FILE* file);

typedef struct {
    int value;
} Int;

extern typeInfo intType;

#endif
