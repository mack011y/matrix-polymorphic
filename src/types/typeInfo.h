#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "../typesEnum.h"

typedef struct {
    size_t size;
    void (*print)(const void*);
    void (*printFile)(const void*, FILE*);
    void (*sum)(const void*, const void*, const void*);
    void (*multiply)(const void*, const void*, const void*);
    void (*multiply_scalar)(const void*, const double, const void*);
    void (*return_neutral_of_sum)(const void*);
    bool (*is_zero)(const void*);
    void (*divide)(const void*, const void*, const void*);
    void (*negate)(const void*, const void*);
    void (*scan)(const void*);
    void (*scanFile)(const void*, FILE*);
    DataType type;
} typeInfo;

#endif
