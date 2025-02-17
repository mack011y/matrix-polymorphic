#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows;
    int cols;
    size_t sizeOfElement;
    void*** data;
} Matrix;

typedef void (*MultiplyFunction)(void* a, void* b, void* result);
typedef void (*MultiplyOnScalarFunction)(void* a, double scalar, void* result);
typedef void (*PrintFunction)(void* element);

Matrix* create_matrix(const int rows, const int cols, const size_t sizeOfElement) {
    Matrix* mat = malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->sizeOfElement = sizeOfElement;
    mat->data = (void***)malloc(rows * sizeof(void**));
    for (int i = 0; i < rows; i++) {
        mat->data[i] = (void**)malloc(cols * sizeof(void*));
        for (int j = 0; j < cols; j++) {
            mat->data[i][j] = malloc(sizeOfElement);
        }
    }
    return mat;
}

void free_matrix(Matrix* mat) {
    if (mat == NULL) return;
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            free(mat->data[i][j]);
        }
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

Matrix* add_matrices(const Matrix* a, const Matrix* b, const MultiplyFunction sunFunc) {
    if (a->rows != b->rows || a->cols != b->cols) return NULL;
    Matrix* result = create_matrix(a->rows, a->cols, a->sizeOfElement);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            sunFunc(a->data[i][j], b->data[i][j], result->data[i][j]);
        }
    }
    return result;
}

Matrix* multiply_matrices(const Matrix* a, const Matrix* b, const MultiplyFunction mulFunc, const MultiplyFunction sumFunc) {
    if (a->cols != b->rows) return NULL;
    Matrix* result = create_matrix(a->rows, b->cols, a->sizeOfElement);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            for (int k = 0; k < a->cols; k++) {
                void* tmp = malloc(a->sizeOfElement);
                mulFunc(a->data[i][k], b->data[k][j], tmp);
                sumFunc(result->data[i][j], tmp, result->data[i][j]);
            }
        }
    }
    return result;
}

void multiply_matrix_by_scalar(const Matrix* mat, const double scalar, const MultiplyOnScalarFunction mulFunc) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            mulFunc(mat->data[i][j], scalar, mat->data[i][j]);
        }
    }
}

void add_linear_combination(const Matrix* mat, const int rowIndex, const double* alphas, const MultiplyFunction sumFunc, const MultiplyOnScalarFunction mulScalarFunc) {
    if (rowIndex < 0 || rowIndex >= mat->rows) return; // out of range
    for (int i = 0; i < mat->rows; i++) {
        if (i == rowIndex) continue;
        for (int j = 0; j < mat->cols; j++) {
            void* tmp = malloc(mat->sizeOfElement);
            mulScalarFunc(mat->data[i][j], alphas[i], tmp);
            sumFunc(mat->data[rowIndex][j], tmp, mat->data[rowIndex][j]);
            free(tmp);
        }
    }
}

void print_matrix(const Matrix* mat, const PrintFunction printFunc) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printFunc(mat->data[i][j]);
        }
        printf("\n");
    }
}

void print_double(void* element) {
    printf("%lf ", *(double*)element);
}

void sum_double(void* a, void* b, void* result) {
    *(double*)result = *(double*)a + *(double*)b;
}

void multiply_double(void* a, void* b, void* result) {
    *(double*)result = *(double*)a * *(double*)b;
}

void multiply_double_by_scalar(void* a, const double scalar, void* result) {
    *(double*)result = *(double*)a * scalar;
}

int main() {
    return 0;
}