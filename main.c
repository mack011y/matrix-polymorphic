#include <stdio.h>
#include "matrix.h"
#include "types/Complex.h"
#include "typesEnum.h"

int main() {
    // Создаём матрицу 2x2 с комплексными числами
    Matrix* mat1 = create_matrix(2, 2, COMPLEX_TYPE);
    Matrix* mat2 = create_matrix(2, 2, COMPLEX_TYPE);

    // Создаём комплексные числа и заполняем матрицы
    Complex c1 = {1.0, 2.0}; // 1 + 2i
    Complex c2 = {3.0, 4.0}; // 3 + 4i
    Complex c3 = {5.0, 6.0}; // 5 + 6i
    Complex c4 = {7.0, 8.0}; // 7 + 8i

    set_element(mat1, 0, 0, &c1);
    set_element(mat1, 0, 1, &c2);
    set_element(mat1, 1, 0, &c3);
    set_element(mat1, 1, 1, &c4);

    Complex c5 = {9.0, -1.0}; // 9 - i
    Complex c6 = {-2.0, 3.0}; // -2 + 3i
    Complex c7 = {4.0, -5.0}; // 4 - 5i
    Complex c8 = {-6.0, 7.0}; // -6 + 7i

    set_element(mat2, 0, 0, &c5);
    set_element(mat2, 0, 1, &c6);
    set_element(mat2, 1, 0, &c7);
    set_element(mat2, 1, 1, &c8);

    // Выводим матрицы
    printf("Matrix 1:\n");
    print_matrix(mat1);

    printf("Matrix 2:\n");
    print_matrix(mat2);

    // Проверяем сложение
    Matrix* sum = add_matrices(mat1, mat2);
    printf("Sum of matrices:\n");
    print_matrix(sum);

    // Проверяем умножение
    Matrix* product = multiply_matrices(mat1, mat2);
    printf("Product of matrices:\n");
    print_matrix(product);

    // Проверяем умножение на скаляр
    double scalar = 2.0;
    printf("Matrix 1 after multiplying by scalar %.1f:\n", scalar);
    multiply_matrix_by_scalar(mat1, scalar);
    print_matrix(mat1);

    // Освобождаем память
    free_matrix(mat1);
    free_matrix(mat2);
    free_matrix(sum);
    free_matrix(product);

    return 0;
}