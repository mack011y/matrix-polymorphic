#ifndef MATRIX_H
#define MATRIX_H

#include "types/typeInfo.h"

typedef struct {
    int rows;
    int cols;
    void* data;
    const typeInfo* type;
} Matrix;

Matrix* create_matrix(int rows, int cols, const DataType type);
void free_matrix(Matrix* mat);
void* get_element(const Matrix* mat, int row, int col);
void set_element(const Matrix* mat, int row, int col, const void* value);
void print_matrix(const Matrix* mat);
Matrix* add_matrices(const Matrix* a, const Matrix* b);
Matrix* multiply_matrices(const Matrix* a, const Matrix* b);
void multiply_matrix_by_scalar(const Matrix* mat, double scalar);
void add_linear_combination(const Matrix* mat, const int rowIndex, const double* alphas);

#endif