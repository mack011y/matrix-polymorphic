#ifndef COMPLEX_H
#define COMPLEX_H

#include "typeInfo.h"

void sum_complex(const void* a, const void* b, const void* result);
void multiply_complex(const void* a, const void* b, const void* result);
void multiply_by_scalar_complex(const void* a, const double scalar, const void* result);
void print_complex(const void* element);
void printFile_complex(const void* element, FILE* file);
void return_neutral_of_sum_complex(const void* value);
bool is_zero_complex(const void* value);
void divide_complex(const void* numerator, const void* denominator, const void* result);
void negate_complex(const void* value, const void* result);
void scan_complex(const void* value);
void scanFile_complex(const void* element, FILE* file);

typedef struct {
    double real;
    double imaginary;
} Complex;

extern typeInfo complexType;

#endif
