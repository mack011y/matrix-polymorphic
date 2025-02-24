#ifndef INT_H
#define INT_H

#include "typeInfo.h"

void sum_int(void* a, void* b, void* result);
void multiply_int(void* a, void* b, void* result);
void multiply_int_by_scalar(void* a, double scalar, void* result);
void print_int(void* element);

typedef struct {
    int value;
} Int;

extern typeInfo intType;

#endif
