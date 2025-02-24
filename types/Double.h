#ifndef DOUBLE_H
#define DOUBLE_H

#include "typeInfo.h"

void sum_double(void* a, void* b, void* result);
void multiply_double(void* a, void* b, void* result);
void multiply_double_by_scalar(void* a, double scalar, void* result);
void print_double(void* element);

typedef struct {
    double value;
} Double;

extern typeInfo doubleType;

#endif
