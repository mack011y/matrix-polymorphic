#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows;
    int cols;
    double** data;
} Matrix;

Matrix* create_matrix(int rows, int cols) {
    Matrix* mat = malloc(sizeof(Matrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        mat->data[i] = (double*)malloc(cols * sizeof(double));
    }
    return mat;
}

void free_matrix(Matrix* mat) {
    for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

Matrix* add_matrices(Matrix* a, Matrix* b) {
    if (a->rows != b->rows || a->cols != b->cols) return NULL;
    Matrix* result = create_matrix(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    return result;
}

Matrix* multiply_matrices(Matrix* a, Matrix* b) {
    if (a->cols != b->rows) return NULL;
    Matrix* result = create_matrix(a->rows, b->cols);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < a->cols; k++) {
                result->data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }
    return result;
}

void multiply_matrix_by_scalar(const Matrix* mat, const double scalar) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            mat->data[i][j] *= scalar;
        }
    }
}

void add_linear_combination(Matrix* mat, int rowIndex, double* alphas) {
    if (rowIndex < 0 || rowIndex >= mat->rows) return;
    for (int i = 0; i < mat->rows; i++) {
        if (i != rowIndex) {
            for (int j = 0; j < mat->cols; j++) {
                mat->data[rowIndex][j] += alphas[i] * mat->data[i][j];
            }
        }
    }
}

void print_matrix(Matrix* mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%lf ", mat->data[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Matrix* m1 = create_matrix(2, 2);
    Matrix* m2 = create_matrix(2, 2);

    m1->data[0][0] = 1.0; m1->data[0][1] = 2.0;
    m1->data[1][0] = 3.0; m1->data[1][1] = 4.0;

    m2->data[0][0] = 5.0; m2->data[0][1] = 6.0;
    m2->data[1][0] = 7.0; m2->data[1][1] = 8.0;

    Matrix* sum = add_matrices(m1, m2);
    if (sum) {
        printf("Sum:\n");
        print_matrix(sum);
        free_matrix(sum);
    }

    Matrix* product = multiply_matrices(m1, m2);
    if (product) {
        printf("Product:\n");
        print_matrix(product);
        free_matrix(product);
    }

    multiply_matrix_by_scalar(m1, 2.0);
    printf("Matrix m1 after scalar multiplication:\n");
    print_matrix(m1);

    double alphas[] = {1.0, -0.5};
    add_linear_combination(m1, 0, alphas);
    printf("Matrix m1 after adding linear combination:\n");
    print_matrix(m1);

    free_matrix(m1);
    free_matrix(m2);
    return 0;
}