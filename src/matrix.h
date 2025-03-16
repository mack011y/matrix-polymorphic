#ifndef MATRIX_H
#define MATRIX_H

#include "types/typeInfo.h"

typedef struct {
    int rows;
    int cols;
    void* data;
    const typeInfo* type;
} Matrix;

Matrix* create_matrix(int rows, int cols, const typeInfo* type);
void free_matrix(Matrix* mat);
void* get_element(const Matrix* mat, int row, int col);
void set_element(const Matrix* mat, int row, int col, const void* value, const DataType type);
void print_matrix(const Matrix* mat);
Matrix* add_matrices(const Matrix* a, const Matrix* b);
Matrix* multiply_matrices(const Matrix* a, const Matrix* b);
void multiply_matrix_by_scalar(const Matrix* mat, void* scalar);
void add_linear_combination(const Matrix* mat, const int rowIndex, const double* alphas);
Matrix* transpose_matrix(const Matrix* mat);
void lu_decomposition(const Matrix* mat, Matrix* L, Matrix* U);
Matrix* solve_first(const Matrix* L, const Matrix* b);  // Решает Ly = b
Matrix* solve_second(const Matrix* U, const Matrix* y); // Решает Ux = y
Matrix* solve_equation(const Matrix* A, const Matrix* b); // Решает Ax = b через LU разложение
void* det(const Matrix* mat);

#endif