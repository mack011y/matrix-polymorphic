#ifndef COMPLEX_H
#define COMPLEX_H

#include "typeInfo.h"

void sum_complex(void* a, void* b, void* result);
void multiply_complex(void* a, void* b, void* result);
void multiply_complex_by_scalar(void* a, double scalar, void* result);
void print_complex(void* element);

typedef struct {
    double real;
    double imaginary;
} Complex;

extern typeInfo complexType;

#endif
