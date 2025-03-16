#ifndef DOUBLE_H
#define DOUBLE_H

#include "typeInfo.h"

void sum_double(const void* a, const void* b, const void* result);
void multiply_double(const void* a, const void* b, const void* result);
void multiply_by_scalar_double(const void* a, const double scalar, const void* result);
void print_double(const void* element);
void printFile_double(const void* element, FILE* file);
void return_neutral_of_sum_double(const void* value);
bool is_zero_double(const void* value);
void divide_double(const void* numerator, const void* denominator, const void* result);
void negate_double(const void* value, const void* result);
void scan_double(const void* element);
void scanFile_double(const void* element, FILE* file);

typedef struct {
    double value;
} Double;

extern typeInfo doubleType;

typeInfo* getDoubleType();

#endif
