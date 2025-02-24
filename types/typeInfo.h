#ifndef TYPEINFO_H
#define TYPEINFO_H

#include <stdlib.h>
#include "../typesEnum.h"

typedef struct {
    size_t size;
    void (*print)(void*);
    void (*sum)(void*, void*, void*);
    void (*multiply)(void*, void*, void*);
    void (*multiply_scalar)(void*, double, void*);
    DataType type;
} typeInfo;

#endif
