#include "matrix.h"
#include "types/typeInfo.h"
#include "types/Double.h"
#include "types/Int.h"
#include "types/Complex.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Matrix* create_matrix(int rows, int cols, const DataType type) {
    if (rows < 1 || cols < 1) {
        printf("Invalid matrix size, returned NULL\n");
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
        case INT_TYPE:
            mat->type = &intType;
        break;
        case COMPLEX_TYPE:
            mat->type = &complexType;
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
        return NULL;
    }
    if (row < 0 || row >= mat->rows || col < 0 || col >= mat->cols) {
        return NULL;
    }
    void* elem = (char*)mat->data + (row * mat->cols + col) * mat->type->size;
    return elem;
}

void set_element(const Matrix* mat, int row, int col, const void* value, DataType value_type) {
    if (!mat || !value) {
        printf("NULL in 'set_element'\n");
        return;
    }

    // Проверка типа
    if (mat->type->type != value_type) {
        printf("Type mismatch! Matrix expects %d, got %d\n", mat->type->type, value_type);
        return;
    }

    if (row < 0 || row >= mat->rows || col < 0 || col >= mat->cols) {
        printf("Index out of range\n");
        return;
    }

    void* target = (char*)mat->data + (row * mat->cols + col) * mat->type->size;
    memcpy(target, value, mat->type->size);
}

Matrix* transpose_matrix(const Matrix* mat) {
    if (!mat) {
        printf("NULL in 'transpose_matrix'\n");
        return NULL;
    }


    Matrix* result = create_matrix(mat->cols, mat->rows, mat->type->type);
    if (!result) {
        printf("Failed to create transposed matrix\n");
        return NULL;
    }


    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            const void* element = get_element(mat, i, j);
            set_element(result, j, i, element, result->type->type);
        }
    }
    return result;
}

/*Matrix* create_submatrix(const Matrix* mat, int excluded_row, int excluded_col) {
    if (mat->rows <= 1 || mat->cols <= 1) {
        printf("Error: Cannot create submatrix from 1x1 matrix.\n");
        return NULL;
    }

    // Создаём подматрицу с независимыми данными
    Matrix* subMat = create_matrix(mat->rows - 1, mat->cols - 1, mat->type->type);
    if (!subMat) return NULL;

    // Копируем данные, исключая указанные строку и столбец
    for (int i = 0, si = 0; i < mat->rows; i++) {
        if (i == excluded_row) continue;
        for (int j = 0, sj = 0; j < mat->cols; j++) {
            if (j == excluded_col) continue;
            void* src = get_element(mat, i, j);
            set_element(subMat, si, sj, src);
            sj++;
        }
        si++;
    }
    return subMat;
}

void* determinant_of_matrix(const Matrix* mat) {
    if (mat->rows != mat->cols) {
        printf("Error: determinant is only defined for square matrices.\n");
        return NULL;
    }

    if (mat->rows == 1) {
        void* result = malloc(mat->type->size);
        if (!result) {
            printf("Error: Memory allocation failed.\n");
            return NULL;
        }
        void* element = get_element(mat, 0, 0);
        if (!element) {
            free(result);
            return NULL;
        }
        memcpy(result, element, mat->type->size);
        return result;
    }

    void* det = malloc(mat->type->size);
    if (!det) {
        printf("Error: Memory allocation failed.\n");
        return NULL;
    }
    mat->type->return_neutral_of_sum(det); // Инициализация нулём
    printf("%d\n", mat->cols);
    for (int i = 0; i < mat->cols; i++) {
        Matrix* subMat = create_submatrix(mat, 0, i);
        if (!subMat) {
            printf("Error: Failed to create submatrix.\n");
            free(det);
            return NULL;
        }

        void* minorDet = determinant_of_matrix(subMat);
        if (!minorDet) {
            free_matrix(subMat);
            free(det);
            return NULL;
        }

        void* element = get_element(mat, 0, i);
        if (!element) {
            printf("Error: Failed to get element (0, %d).\n", i);
            free(minorDet);
            free_matrix(subMat);
            free(det);
            return NULL;
        }

        void* cofactor = malloc(mat->type->size);
        if (!cofactor) {
            printf("Error: Memory allocation failed.\n");
            free(minorDet);
            free_matrix(subMat);
            free(det);
            return NULL;
        }

        mat->type->multiply(element, minorDet, cofactor);
        if (i % 2 == 1) {
            mat->type->negate(cofactor, cofactor);
        }
        mat->type->sum(det, cofactor, det);
        free(minorDet);
        free(cofactor);
        free_matrix(subMat);
        printf("lol\n");
        mat->type->print(det);
        printf("\n");
    }
    return det;
}

Matrix* inverse_matrix(const Matrix* mat) {
    if (mat->rows != mat->cols) {
        printf("Error: Only square matrices can have an inverse.\n");
        return NULL;
    }

    void* det = determinant_of_matrix(mat);
    if (mat->type->is_zero(det)) { // Проверяем, равен ли детерминант нулю
        printf("Error: Singular matrix, cannot compute inverse.\n");
        return NULL;
    }

    Matrix* cofactors = create_matrix(mat->rows, mat->cols, mat->type->type);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            Matrix* subMat = create_submatrix(mat, i, j);
            void* minor_det = determinant_of_matrix(subMat);
            void* cofactor = malloc(mat->type->size);

            if ((i + j) % 2 == 0) {
                memcpy(cofactor, minor_det, mat->type->size);
            } else {
                mat->type->negate(minor_det, cofactor);
            }

            set_element(cofactors, i, j, cofactor);
            free(subMat);
        }
    }

    Matrix* adjugate = transpose_matrix(cofactors);
    free_matrix(cofactors);

    Matrix* inverse = create_matrix(mat->rows, mat->cols, mat->type->type);
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            void* inv_elem = malloc(mat->type->size);
            mat->type->divide(get_element(adjugate, i, j), det, inv_elem);
            set_element(inverse, i, j, inv_elem);
            free(inv_elem);
        }
    }

    free_matrix(adjugate);
    return inverse;
}*/

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