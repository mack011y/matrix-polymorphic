#include "matrix.h"
#include "types/typeInfo.h"
#include "types/Double.h"
#include "error.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Matrix* create_matrix(int rows, int cols, const typeInfo* type) {
    if (rows < 1 || cols < 1) {
        set_error(ERROR_INVALID_SIZE);
        return NULL;
    }
    Matrix* mat = malloc(sizeof(Matrix));
    if (!mat) {
        set_error(ERROR_MEMORY_ERROR);
        return NULL;
    }
    mat->rows = rows;
    mat->cols = cols;
    mat->type = type;
    mat->data = malloc(rows * cols * mat->type->size);
    if (!mat->data) {
        free(mat);
        set_error(ERROR_MEMORY_ERROR);
        return NULL;
    }
    void* zero = malloc(mat->type->size);
    if (!zero) {
        free(mat->data);
        free(mat);
        set_error(ERROR_MEMORY_ERROR);
        return NULL;
    }
    mat->type->return_neutral_of_sum(zero);
    for (int i = 0; i < rows * cols; i++) {
        void* elem = (char*)mat->data + i * mat->type->size;
        memcpy(elem, zero, mat->type->size);
    }
    free(zero);
    reset_error();
    return mat;
}

void* get_element(const Matrix* mat, int row, int col) {
    if (!mat) {
        set_error(ERROR_NULL_POINTER);
        return NULL;
    }
    if (row < 0 || row >= mat->rows || col < 0 || col >= mat->cols) {
        set_error(ERROR_INDEX_OUT_OF_RANGE);
        return NULL;
    }
    void* elem = (char*)mat->data + (row * mat->cols + col) * mat->type->size;
    reset_error();
    return elem;
}

void set_element(const Matrix* mat, int row, int col, const void* value, const DataType value_type) {
    if (!mat || !value) {
        set_error(ERROR_NULL_POINTER);
        return;
    }
    if (mat->type->type != value_type) {
        set_error(ERROR_TYPE_MISMATCH);
        return;
    }
    if (row < 0 || row >= mat->rows || col < 0 || col >= mat->cols) {
        set_error(ERROR_INDEX_OUT_OF_RANGE);
        return;
    }
    void* target = (char*)mat->data + (row * mat->cols + col) * mat->type->size;
    memcpy(target, value, mat->type->size);
    reset_error();
}

Matrix* transpose_matrix(const Matrix* mat) {
    if (!mat) {
        set_error(ERROR_NULL_POINTER);
        return NULL;
    }
    Matrix* result = create_matrix(mat->cols, mat->rows, mat->type);
    if (!result) {
        return NULL;
    }
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            const void* element = get_element(mat, i, j);
            if (!element) {
                free_matrix(result);
                return NULL;
            }
            set_element(result, j, i, element, result->type->type);
            if (last_error != ERROR_OK) {
                free_matrix(result);
                return NULL;
            }
        }
    }
    reset_error();
    return result;
}

void lu_decomposition(const Matrix* mat, Matrix* L, Matrix* U) {
    if (!mat || !L || !U) {
        set_error(ERROR_NULL_POINTER);
        return;
    }
    if (L->rows != mat->rows || L->cols != mat->cols || U->rows != mat->rows || U->cols != mat->cols) {
        set_error(ERROR_INVALID_SIZE);
        return;
    }
    if (mat->type->type != DOUBLE_TYPE) {
        set_error(ERROR_TYPE_MISMATCH);
        printf("lu_decomposition: only double type allowed\n");
        return;
    }
    int n = mat->rows;
    void* zero = malloc(mat->type->size);
    if (!zero) {
        set_error(ERROR_MEMORY_ERROR);
        return;
    }
    mat->type->return_neutral_of_sum(zero);
    void* one = malloc(mat->type->size);
    if (!one) {
        free(zero);
        set_error(ERROR_MEMORY_ERROR);
        return;
    }
    double one_val = 1.0;
    memcpy(one, &one_val, sizeof(double));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            set_element(L, i, j, zero, L->type->type);
            set_element(U, i, j, zero, U->type->type);
        }
    }
    for (int i = 0; i < n; i++) {
        set_element(L, i, i, one, L->type->type);
    }
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            void* sum = malloc(mat->type->size);
            if (!sum) {
                free(zero);
                free(one);
                set_error(ERROR_MEMORY_ERROR);
                return;
            }
            mat->type->return_neutral_of_sum(sum);
            for (int k = 0; k < i; k++) {
                void* l_elem = get_element(L, i, k);
                void* u_elem = get_element(U, k, j);
                if (!l_elem || !u_elem) {
                    free(sum);
                    free(zero);
                    free(one);
                    return;
                }
                void* temp = malloc(mat->type->size);
                if (!temp) {
                    free(sum);
                    free(zero);
                    free(one);
                    set_error(ERROR_MEMORY_ERROR);
                    return;
                }
                mat->type->multiply(l_elem, u_elem, temp);
                mat->type->sum(sum, temp, sum);
                free(temp);
            }
            void* a_elem = get_element(mat, i, j);
            void* u_elem = get_element(U, i, j);
            if (!a_elem || !u_elem) {
                free(sum);
                free(zero);
                free(one);
                return;
            }
            void* neg_sum = malloc(mat->type->size);
            if (!neg_sum) {
                free(sum);
                free(zero);
                free(one);
                set_error(ERROR_MEMORY_ERROR);
                return;
            }
            mat->type->negate(sum, neg_sum);
            mat->type->sum(a_elem, neg_sum, u_elem);
            free(neg_sum);
            free(sum);
        }
        for (int j = i + 1; j < n; j++) {
            void* sum = malloc(mat->type->size);
            if (!sum) {
                free(zero);
                free(one);
                set_error(ERROR_MEMORY_ERROR);
                return;
            }
            mat->type->return_neutral_of_sum(sum);
            for (int k = 0; k < i; k++) {
                void* l_elem = get_element(L, j, k);
                void* u_elem = get_element(U, k, i);
                if (!l_elem || !u_elem) {
                    free(sum);
                    free(zero);
                    free(one);
                    return;
                }
                void* temp = malloc(mat->type->size);
                if (!temp) {
                    free(sum);
                    free(zero);
                    free(one);
                    set_error(ERROR_MEMORY_ERROR);
                    return;
                }
                mat->type->multiply(l_elem, u_elem, temp);
                mat->type->sum(sum, temp, sum);
                free(temp);
            }
            void* a_elem = get_element(mat, j, i);
            void* u_diag = get_element(U, i, i);
            void* l_elem = get_element(L, j, i);
            if (!a_elem || !u_diag || !l_elem) {
                free(sum);
                free(zero);
                free(one);
                return;
            }
            double u_diag_val;
            memcpy(&u_diag_val, u_diag, sizeof(double));
            if (U->type->is_zero(get_element(U, i, i))) {
                free(sum);
                free(zero);
                free(one);
                set_error(ERROR_DIVISION_BY_ZERO);
                return;
            }
            void* neg_sum = malloc(mat->type->size);
            if (!neg_sum) {
                free(sum);
                free(zero);
                free(one);
                set_error(ERROR_MEMORY_ERROR);
                return;
            }
            mat->type->negate(sum, neg_sum);
            void* temp = malloc(mat->type->size);
            if (!temp) {
                free(neg_sum);
                free(sum);
                free(zero);
                free(one);
                set_error(ERROR_MEMORY_ERROR);
                return;
            }
            mat->type->sum(a_elem, neg_sum, temp);
            L->type->divide(temp, u_diag, l_elem);
            free(temp);
            free(neg_sum);
            free(sum);
        }
    }
    free(zero);
    free(one);
    reset_error();
}

void* det(const Matrix* mat) {
    if (!mat) {
        set_error(ERROR_NULL_POINTER);
        return NULL;
    }
    if (mat->type != getDoubleType()) {
        set_error(ERROR_TYPE_MISMATCH);
        return NULL;
    }
    void* answer = malloc(mat->type->size);
    double one_val = 1.0;
    memcpy(answer, &one_val, sizeof(double));
    Matrix* L = create_matrix(mat->rows, mat->cols, mat->type);
    Matrix* U = create_matrix(mat->rows, mat->cols, mat->type);
    int n = mat->rows;
    for (int i = 0; i < n; i++) {
        mat->type->multiply(answer, get_element(U, i, i), answer);
    }
    free_matrix(L);
    free_matrix(U);
    return answer;
}

void free_matrix(Matrix* mat) {
    if (mat == NULL) return;
    free(mat->data);
    free(mat);
    reset_error();
}

Matrix* add_matrices(const Matrix* a, const Matrix* b) {
    if (!a || !b) {
        set_error(ERROR_NULL_POINTER);
        return NULL;
    }
    if (a->rows != b->rows || a->cols != b->cols) {
        set_error(ERROR_INCOMPATIBLE_SIZES);
        return NULL;
    }
    if (a->type->type != b->type->type) {
        set_error(ERROR_TYPE_MISMATCH);
        return NULL;
    }
    Matrix* result = create_matrix(a->rows, a->cols, a->type);
    if (!result) {
        return NULL;
    }
    for (int i = 0; i < a->rows * a->cols; i++) {
        void* elem_a = (char*)a->data + i * a->type->size;
        void* elem_b = (char*)b->data + i * b->type->size;
        void* elem_result = (char*)result->data + i * result->type->size;
        a->type->sum(elem_a, elem_b, elem_result);
    }
    reset_error();
    return result;
}

Matrix* multiply_matrices(const Matrix* a, const Matrix* b) {
    if (!a || !b) {
        set_error(ERROR_NULL_POINTER);
        return NULL;
    }
    if (a->cols != b->rows) {
        set_error(ERROR_INCOMPATIBLE_SIZES);
        return NULL;
    }
    if (a->type->type != b->type->type) {
        set_error(ERROR_TYPE_MISMATCH);
        return NULL;
    }
    Matrix* result = create_matrix(a->rows, b->cols, a->type);
    if (!result) {
        return NULL;
    }
    
    void* temp = malloc(a->type->size);
    if (!temp) {
        free_matrix(result);
        set_error(ERROR_MEMORY_ERROR);
        return NULL;
    }
    
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            for (int k = 0; k < a->cols; k++) {
                void* elem_a = get_element(a, i, k);
                void* elem_b = get_element(b, k, j);
                void* elem_result = get_element(result, i, j);
                if (!elem_a || !elem_b || !elem_result) {
                    free(temp);
                    free_matrix(result);
                    return NULL;
                }
                a->type->multiply(elem_a, elem_b, temp);
                a->type->sum(elem_result, temp, elem_result);
            }
        }
    }
    free(temp);
    reset_error();
    return result;
}

void multiply_matrix_by_scalar(const Matrix* mat, void* scalar) {
    if (!mat || !scalar) {
        set_error(ERROR_NULL_POINTER);
        return;
    }
    double scalar_value;
    memcpy(&scalar_value, scalar, sizeof(double));
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            void* elem = get_element(mat, i, j);
            if (!elem) {
                return;
            }
            mat->type->multiply_scalar(elem, scalar_value, elem);
        }
    }
    reset_error();
}

void add_linear_combination(const Matrix* mat, const int rowIndex, const double* alphas) {
    if (!mat || !alphas) {
        set_error(ERROR_NULL_POINTER);
        return;
    }
    if (rowIndex < 0 || rowIndex >= mat->rows) {
        set_error(ERROR_INDEX_OUT_OF_RANGE);
        return;
    }
    void* temp = malloc(mat->type->size);
    if (!temp) {
        set_error(ERROR_MEMORY_ERROR);
        return;
    }
    for (int i = 0; i < mat->rows; i++) {
        if (i == rowIndex) continue;
        for (int j = 0; j < mat->cols; j++) {
            void* elem_target = get_element(mat, rowIndex, j);
            void* elem_source = get_element(mat, i, j);
            if (!elem_target || !elem_source) {
                free(temp);
                return;
            }
            mat->type->multiply_scalar(elem_source, alphas[i], temp);
            mat->type->sum(elem_target, temp, elem_target);
        }
    }
    free(temp);
    reset_error();
}

void print_matrix(const Matrix* mat) {
    if (!mat) {
        set_error(ERROR_NULL_POINTER);
        printf("Ошибка: NULL указатель на матрицу\n");
        return;
    }
    if (!mat->data) {
        set_error(ERROR_NULL_POINTER);
        printf("Ошибка: NULL указатель на данные матрицы\n");
        return;
    }
    if (!mat->type) {
        set_error(ERROR_NULL_POINTER);
        printf("Ошибка: NULL указатель на тип матрицы\n");
        return;
    }
    if (!mat->type->print) {
        set_error(ERROR_NULL_POINTER);
        printf("Ошибка: NULL указатель на функцию печати\n");
        return;
    }
    void* elem_buffer = malloc(mat->type->size);
    if (!elem_buffer) {
        set_error(ERROR_MEMORY_ERROR);
        printf("Ошибка: не удалось выделить память для буфера элемента\n");
        return;
    }
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            void* elem = get_element(mat, i, j);
            if (!elem) {
                printf("Ошибка: не удалось получить элемент [%d][%d]\n", i, j);
                free(elem_buffer);
                return;
            }
            memcpy(elem_buffer, elem, mat->type->size);
            mat->type->print(elem_buffer);
            printf(" ");
        }
        printf("\n");
    }

    free(elem_buffer);
    reset_error();
}

Matrix* solve_first(const Matrix* L, const Matrix* b) {
    if (!L || !b) {
        set_error(ERROR_NULL_POINTER);
        return NULL;
    }
    if (L->rows != L->cols || L->rows != b->rows || b->cols != 1) {
        set_error(ERROR_INCOMPATIBLE_SIZES);
        return NULL;
    }
    if (L->type->type != DOUBLE_TYPE || b->type->type != DOUBLE_TYPE) {
        set_error(ERROR_TYPE_MISMATCH);
        return NULL;
    }
    int n = L->rows;
    Matrix* y = create_matrix(n, 1, L->type);
    if (!y) return NULL;
    for (int i = 0; i < n; i++) {
        void* sum = malloc(L->type->size);
        if (!sum) {
            free_matrix(y);
            set_error(ERROR_MEMORY_ERROR);
            return NULL;
        }
        L->type->return_neutral_of_sum(sum);
        for (int j = 0; j < i; j++) {
            void* l_elem = get_element(L, i, j);
            void* y_elem = get_element(y, j, 0);
            if (!l_elem || !y_elem) {
                free(sum);
                free_matrix(y);
                return NULL;
            }
            void* prod = malloc(L->type->size);
            if (!prod) {
                free(sum);
                free_matrix(y);
                set_error(ERROR_MEMORY_ERROR);
                return NULL;
            }
            L->type->multiply(l_elem, y_elem, prod);
            L->type->sum(sum, prod, sum);
            free(prod);
        }
        void* b_elem = get_element(b, i, 0);
        void* l_diag = get_element(L, i, i);
        void* y_elem = get_element(y, i, 0);
        if (!b_elem || !l_diag || !y_elem) {
            free(sum);
            free_matrix(y);
            return NULL;
        }
        if (L->type->is_zero(l_diag)) {
            free(sum);
            free_matrix(y);
            set_error(ERROR_DIVISION_BY_ZERO);
            return NULL;
        }
        void* neg_sum = malloc(L->type->size);
        if (!neg_sum) {
            free(sum);
            free_matrix(y);
            set_error(ERROR_MEMORY_ERROR);
            return NULL;
        }
        L->type->negate(sum, neg_sum);
        L->type->sum(b_elem, neg_sum, y_elem);
        L->type->divide(y_elem, l_diag, y_elem);
        free(neg_sum);
        free(sum);
    }
    reset_error();
    return y;
}

Matrix* solve_second(const Matrix* U, const Matrix* y) {
    if (!U || !y) {
        set_error(ERROR_NULL_POINTER);
        return NULL;
    }
    if (U->rows != U->cols || U->rows != y->rows || y->cols != 1) {
        set_error(ERROR_INCOMPATIBLE_SIZES);
        return NULL;
    }
    if (U->type->type != DOUBLE_TYPE || y->type->type != DOUBLE_TYPE) {
        set_error(ERROR_TYPE_MISMATCH);
        return NULL;
    }
    int n = U->rows;
    Matrix* x = create_matrix(n, 1, U->type);
    if (!x) return NULL;
    for (int i = n - 1; i >= 0; i--) {
        void* sum = malloc(U->type->size);
        if (!sum) {
            free_matrix(x);
            set_error(ERROR_MEMORY_ERROR);
            return NULL;
        }
        U->type->return_neutral_of_sum(sum);
        for (int j = i + 1; j < n; j++) {
            void* u_elem = get_element(U, i, j);
            void* x_elem = get_element(x, j, 0);
            if (!u_elem || !x_elem) {
                free(sum);
                free_matrix(x);
                return NULL;
            }
            void* prod = malloc(U->type->size);
            if (!prod) {
                free(sum);
                free_matrix(x);
                set_error(ERROR_MEMORY_ERROR);
                return NULL;
            }
            U->type->multiply(u_elem, x_elem, prod);
            U->type->sum(sum, prod, sum);
            free(prod);
        }
        void* y_elem = get_element(y, i, 0);
        void* u_diag = get_element(U, i, i);
        void* x_elem = get_element(x, i, 0);
        if (!y_elem || !u_diag || !x_elem) {
            free(sum);
            free_matrix(x);
            return NULL;
        }
        if (U->type->is_zero(u_diag)) {
            free(sum);
            free_matrix(x);
            set_error(ERROR_DIVISION_BY_ZERO);
            return NULL;
        }
        void* neg_sum = malloc(U->type->size);
        if (!neg_sum) {
            free(sum);
            free_matrix(x);
            set_error(ERROR_MEMORY_ERROR);
            return NULL;
        }
        U->type->negate(sum, neg_sum);
        U->type->sum(y_elem, neg_sum, x_elem);
        U->type->divide(x_elem, u_diag, x_elem);
        free(neg_sum);
        free(sum);
    }
    reset_error();
    return x;
}

Matrix* solve_equation(const Matrix* A, const Matrix* b) {
    if (!A || !b) {
        set_error(ERROR_NULL_POINTER);
        return NULL;
    }
    if (A->rows != A->cols || A->rows != b->rows || b->cols != 1) {
        set_error(ERROR_INCOMPATIBLE_SIZES);
        return NULL;
    }
    if (A->type->type != DOUBLE_TYPE || b->type->type != DOUBLE_TYPE) {
        set_error(ERROR_TYPE_MISMATCH);
        return NULL;
    }
    Matrix* L = create_matrix(A->rows, A->cols, A->type);
    Matrix* U = create_matrix(A->rows, A->cols, A->type);
    if (!L || !U) {
        if (L) free_matrix(L);
        if (U) free_matrix(U);
        return NULL;
    }
    lu_decomposition(A, L, U);
    if (last_error != ERROR_OK) {
        free_matrix(L);
        free_matrix(U);
        return NULL;
    }
    Matrix* y = solve_first(L, b);
    if (!y) {
        free_matrix(L);
        free_matrix(U);
        return NULL;
    }
    Matrix* x = solve_second(U, y);
    free_matrix(L);
    free_matrix(U);
    free_matrix(y);
    return x;
}