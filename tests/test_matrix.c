#include <stdio.h>
#include <stdlib.h>
#include "../src/matrix.h"
#include "../src/types/Int.h"
#include "test_matrix.h"


int test_create_matrix() {
    Matrix* mat = create_matrix(3, 3, INT_TYPE);
    if (mat == NULL) {
        printf("[WA]     create_matrix()\n");
        return 1;
    }
    if (mat->rows != 3 || mat->cols != 3) {
        printf("[WA]     create_matrix()\n");
        return 1;
    }
    printf("[OK]     create_matrix()\n");
    free_matrix(mat);
    return 0;
}

int test_set_element() {
    Matrix* mat = create_matrix(3, 3, INT_TYPE);
    int value = 10;
    set_element(mat, 1, 1, &value, mat->type->type);
    int* retrieved_value = (int*)get_element(mat, 1, 1);
    int isItProblem = 0;
    if (*retrieved_value == 10) {
        printf("[OK]     set_element()\n");
    } else {
        printf("[WA]     set_element()\n");
        isItProblem = 1;
    }
    free_matrix(mat);
    return isItProblem;
}

int test_get_element() {
    Matrix* mat = create_matrix(3, 3, INT_TYPE);
    int value = 20;
    set_element(mat, 0, 0, &value, mat->type->type);
    int* retrieved_value = (int*)get_element(mat, 0, 0);
    int isItProblem = 0;
    if (*retrieved_value == 20) {
        printf("[OK]     get_element()\n");
    } else {
        printf("[WA]     get_element()\n");
        isItProblem = 1;
    }
    free_matrix(mat);
    return isItProblem;
}

int test_add_matrices() {
    Matrix* mat1 = create_matrix(2, 2, INT_TYPE);
    Matrix* mat2 = create_matrix(2, 2, INT_TYPE);
    int value1 = 5, value2 = 3;
    set_element(mat1, 0, 0, &value1, mat1->type->type);
    set_element(mat2, 0, 0, &value2, mat2->type->type);
    Matrix* result = add_matrices(mat1, mat2);
    int* result_value = (int*)get_element(result, 0, 0);
    int isItProblem = 0;
    if (*result_value == 8) {
        printf("[OK]     add_matrices()\n");
    } else {
        printf("[WA]     add_matrices()\n");
        isItProblem = 1;
    }
    free_matrix(mat1);
    free_matrix(mat2);
    free_matrix(result);
    return isItProblem;
}

int test_multiply_matrices() {
    Matrix* mat1 = create_matrix(2, 2, INT_TYPE);
    Matrix* mat2 = create_matrix(2, 2, INT_TYPE);
    int value1 = 2, value2 = 3;
    set_element(mat1, 0, 0, &value1, mat1->type->type);
    set_element(mat2, 0, 0, &value2, mat2->type->type);
    Matrix* result = multiply_matrices(mat1, mat2);
    int* result_value = (int*)get_element(result, 0, 0);
    int isItProblem = 0;
    if (*result_value == 6) {
        printf("[OK]     multiply_matrices()\n");
    } else {
        printf("[WA]     multiply_matrices()\n");
        isItProblem = 1;
    }
    free_matrix(mat1);
    free_matrix(mat2);
    free_matrix(result);
    return isItProblem;
}

int test_transpose_matrix() {
    Matrix* mat = create_matrix(2, 2, INT_TYPE);
    int value = 1;
    set_element(mat, 0, 1, &value, mat->type->type);
    Matrix* transposed = transpose_matrix(mat);
    int* transposed_value = (int*)get_element(transposed, 1, 0);
    int isItProblem = 0;
    if (*transposed_value == 1) {
        printf("[OK]     transpose_matrix()\n");
    } else {
        printf("[WA]     transpose_matrix()\n");
        isItProblem = 1;
    }
    free_matrix(transposed);
    free_matrix(mat);
    return isItProblem;
}

int test_linear_combination() {
    Matrix* mat = create_matrix(3, 3, INT_TYPE);
    int values[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int* value = malloc(sizeof(int));
            *value = values[i][j];
            set_element(mat, i, j, value, mat->type->type);
        }
    }
    double alphas[3] = {1, -1, 2};
    add_linear_combination(mat, 1, alphas);
    double expected_result[3][3] = {{1, 2, 3}, {4, 5, 6}, {9, 10, 11}};
    int isItProblem = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int* value = get_element(mat, i, j);
            isItProblem = *value == expected_result[i][j];
        }
    }
    if (!isItProblem) {
      printf("[OK]     linear combination()\n");
    } else {
      printf("[WA]     linear combination()\n");
    }
    free_matrix(mat);
    return isItProblem;
}

int test_matrix() {
    int countOfProblem = 0;
    countOfProblem += test_create_matrix();
    countOfProblem += test_set_element();
    countOfProblem += test_get_element();
    countOfProblem += test_add_matrices();
    countOfProblem += test_multiply_matrices();
    countOfProblem += test_transpose_matrix();
    countOfProblem += test_linear_combination();
    return countOfProblem;
}