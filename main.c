#include <stdio.h>
#include "matrix.h"
#include "types/typeInfo.h"
#include "types/Double.h"
#include "typesEnum.h"

int main() {
    Matrix* mat1 = create_matrix(3, 3, DOUBLE_TYPE);

    Double val1 = {1.0};
    set_element(mat1, 0, 0, &val1);
    val1.value = 2.0;
    set_element(mat1, 0, 1, &val1);
    val1.value = 3.0;
    set_element(mat1, 0, 2, &val1);
    val1.value = 4.0;
    set_element(mat1, 1, 0, &val1);
    val1.value = 5.0;
    set_element(mat1, 1, 1, &val1);
    val1.value = 6.0;
    set_element(mat1, 1, 2, &val1);
    val1.value = 7.0;
    set_element(mat1, 2, 0, &val1);

    val1.value = 8.0;
    set_element(mat1, 2, 1, &val1);
    val1.value = 9.0;
    set_element(mat1, 2, 2, &val1);

    printf("Matrix 1:\n");
    print_matrix(mat1);

    Matrix* mat2 = create_matrix(3, 3, DOUBLE_TYPE);
    val1.value = 9.0;
    set_element(mat2, 0, 0, &val1);
    val1.value = 8.0;
    set_element(mat2, 0, 1, &val1);
    val1.value = 7.0;
    set_element(mat2, 0, 2, &val1);
    val1.value = 6.0;
    set_element(mat2, 1, 0, &val1);
    val1.value = 5.0;
    set_element(mat2, 1, 1, &val1);
    val1.value = 4.0;
    set_element(mat2, 1, 2, &val1);
    val1.value = 3.0;
    set_element(mat2, 2, 0, &val1);
    val1.value = 2.0;
    set_element(mat2, 2, 1, &val1);
    val1.value = 1.0;
    set_element(mat2, 2, 2, &val1);

    printf("Matrix 2:\n");
    print_matrix(mat2);

    Matrix* result_add = add_matrices(mat1, mat2);
    printf("Matrix after addition:\n");
    print_matrix(result_add);

    Matrix* result_multiply = multiply_matrices(mat1, mat2);
    printf("Matrix after multiplication:\n");
    print_matrix(result_multiply);

    free_matrix(mat1);
    free_matrix(mat2);
    free_matrix(result_add);
    free_matrix(result_multiply);

    return 0;
}