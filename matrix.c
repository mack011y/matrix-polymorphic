#include "matrix.h"
#include "types/typeInfo.h"
#include "types/Double.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Matrix* create_matrix(int rows, int cols, const DataType type) {
    if (rows < 1 || cols < 1) {
        printf("Invalid matrix size\n");
        return NULL;
    }
    Matrix* mat = malloc(sizeof(Matrix));
    if (!mat) return NULL;
    mat->rows = rows;
    mat->cols = cols;
    switch (type) {
        case DOUBLE_TYPE:
            mat->type = &doubleType;
        break;
        default:
            printf("Unsupported type\n");
        free(mat);
        return NULL;
    }
    mat->data = malloc(rows * cols * mat->type->size);
    return mat;
}

void* get_element(const Matrix* mat, int row, int col) {
    if (!mat) {
        printf("c");
        fflush(stdout);
        return NULL;
    }
    if (row < 0 || row >= mat->rows || col < 0 || col >= mat->cols) {
        printf("Ошибка: индекс [%d][%d] вне диапазона!\n", row, col);
        return NULL;
    }

    void* elem = (char*)mat->data + (row * mat->cols + col) * mat->type->size;
    return elem;
}


void set_element(const Matrix* mat, const int row, const int col, const void* value) {
    if (!mat || !value) {
        printf("c");
        return;
    }
    if (row < 0 || row >= mat->rows || col < 0 || col >= mat->cols) {
        printf("Ошибка: индекс [%d][%d] вне диапазона!\n", row, col);
        return;
    }

    void* target = (char*)mat->data + (row * mat->cols + col) * mat->type->size;
    memcpy(target, value, mat->type->size);
}


void free_matrix(Matrix* mat) {
    if (mat == NULL) return;
    free(mat->data);
    free(mat);
}

Matrix* add_matrices(const Matrix* a, const Matrix* b) {
    if (a->rows != b->rows || a->cols != b->cols) return NULL;
    Matrix* result = create_matrix(a->rows, a->cols, a->type->type);
    for (int i = 0; i < a->rows * a->cols; i++) {
        void* elem_a = get_element(a, i / a->cols, i % a->cols);
        void* elem_b = get_element(b, i / b->cols, i % b->cols);
        void* elem_result = get_element(result, i / result->cols, i % result->cols);
        a->type->sum(elem_a, elem_b, elem_result);
    }
    return result;
}

Matrix* multiply_matrices(const Matrix* a, const Matrix* b) {
   if (a->cols != b->rows) return NULL;
    Matrix* result = create_matrix(a->rows, b->cols, a->type->type);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            for (int k = 0; k < a->cols; k++) {
                void* tmp = malloc(a->type->size);
                a->type->multiply(get_element(a, i, k), get_element(b, k, j), tmp);
                a->type->sum(get_element(result, i, j), tmp, get_element(result, i, j));
            }
        }
    }
    return result;
}

void multiply_matrix_by_scalar(const Matrix* mat, const double scalar) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            mat->type->multiply_scalar(get_element(mat, i, j), scalar, get_element(mat, i, j));
        }
    }
}

void add_linear_combination(const Matrix* mat, const int rowIndex, const double* alphas) {
    if (rowIndex < 0 || rowIndex >= mat->rows) return;
    for (int i = 0; i < mat->rows; i++) {
        if (i == rowIndex) continue;
        for (int j = 0; j < mat->cols; j++) {
            void* elem_target = get_element(mat, rowIndex, j);
            void* elem_source = get_element(mat, i, j);
            void* tmp = malloc(mat->type->size);
            mat->type->multiply_scalar(elem_source, alphas[i], tmp);
            mat->type->sum(elem_target, tmp, elem_target);
            free(tmp);
        }
    }
}

void print_matrix(const Matrix* mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            mat->type->print(get_element(mat, i, j));
        }
        printf("\n");
    }
}