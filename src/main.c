#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "types/Complex.h"
#include "types/Double.h"
#include "types/Int.h"
#include "typesEnum.h"
#include "types/typeInfo.h"
#include "error.h"

void clear_console() {
    system("clear");
}

void print_input_instructions(const DataType type) {
    printf("\n=== Input Instructions ===\n");
    switch (type) {
        case DOUBLE_TYPE:
            printf("Enter numbers in decimal format, e.g., 1.23 4.56 7.89\n");
            break;
        case INT_TYPE:
            printf("Enter integers, e.g., 1 2 3 4\n");
            break;
        case COMPLEX_TYPE:
            printf("Enter complex numbers in the format: real imaginary\n");
            printf("Example: 3.5 -2.1 (means 3.5 + (-2.1)i)\n");
            break;
        default:
            printf("Unknown type, no specific instructions available.\n");
    }
    printf("==========================\n\n");
}

Matrix* create_and_fill_matrix(const typeInfo* type) {
    int rows, cols;
    printf("Введите количество строк: ");
    scanf("%d", &rows);
    printf("Введите количество столбцов: ");
    scanf("%d", &cols);
    Matrix* mat = create_matrix(rows, cols, type);
    if (!mat) {
        printf("Ошибка: %s\n", error_string(last_error));
        return NULL;
    }
    printf("Введите элементы матрицы (по %d чисел в строке):\n", cols);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    for (int i = 0; i < rows; i++) {
        printf("Строка %d: ", i);
        for (int j = 0; j < cols; j++) {
            void* elem = malloc(type->size);
            if (!elem) {
                free_matrix(mat);
                set_error(ERROR_MEMORY_ERROR);
                printf("Ошибка: %s\n", error_string(last_error));
                return NULL;
            }
            type->scan(elem);
            set_element(mat, i, j, elem, type->type);
            if (last_error != ERROR_OK) {
                printf("Ошибка: %s\n", error_string(last_error));
                free(elem);
                free_matrix(mat);
                return NULL;
            }
            free(elem);
        }
    }
    return mat;
}

const typeInfo* choose_type() {
    int choice;
    printf("Выберите тип данных:\n");
    printf("1. Double\n");
    printf("2. Int\n");
    printf("3. Complex\n");
    printf("Ваш выбор: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            return getDoubleType();
        case 2:
            return getIntType();
        case 3:
            return getComplexType();
        default:
            printf("Неверный выбор. Используется тип Double по умолчанию.\n");
            return getDoubleType();
    }
}

void option_1() {
    const typeInfo* type = choose_type();
    printf("Первая матрица:\n");
    Matrix* mat1 = create_and_fill_matrix(type);
    if (!mat1) return;
    printf("Вторая матрица:\n");
    Matrix* mat2 = create_and_fill_matrix(type);
    if (!mat2) {
        free_matrix(mat1);
        return;
    }
    Matrix* result = add_matrices(mat1, mat2);
    if (!result) {
        printf("Ошибка: %s\n", error_string(last_error));
        free_matrix(mat1);
        free_matrix(mat2);
        return;
    }
    printf("Результат сложения:\n");
    print_matrix(result);
    free_matrix(mat1);
    free_matrix(mat2);
    free_matrix(result);
}

void option_2() {
    const typeInfo* type = choose_type();
    printf("Первая матрица:\n");
    Matrix* mat1 = create_and_fill_matrix(type);
    if (!mat1) return;
    printf("Вторая матрица:\n");
    Matrix* mat2 = create_and_fill_matrix(type);
    if (!mat2) {
        free_matrix(mat1);
        return;
    }
    Matrix* result = multiply_matrices(mat1, mat2);
    if (!result) {
        printf("Ошибка: %s\n", error_string(last_error));
        free_matrix(mat1);
        free_matrix(mat2);
        return;
    }
    printf("Результат умножения:\n");
    print_matrix(result);
    free_matrix(mat1);
    free_matrix(mat2);
    free_matrix(result);
}

void option_3() {
    const typeInfo* type = choose_type();
    printf("Матрица:\n");
    Matrix* mat = create_and_fill_matrix(type);
    if (!mat) return;
    printf("Введите скаляр: ");
    double scalar_value;
    scanf("%lf", &scalar_value);
    void* scalar_ptr = malloc(sizeof(double));
    if (!scalar_ptr) {
        printf("Ошибка: %s\n", error_string(ERROR_MEMORY_ERROR));
        free_matrix(mat);
        return;
    }
    memcpy(scalar_ptr, &scalar_value, sizeof(double));
    multiply_matrix_by_scalar(mat, scalar_ptr);
    if (last_error != ERROR_OK) {
        printf("Ошибка: %s\n", error_string(last_error));
        free(scalar_ptr);
        free_matrix(mat);
        return;
    }
    printf("Результат умножения на скаляр:\n");
    print_matrix(mat);
    free(scalar_ptr);
    free_matrix(mat);
}

void option_4() {
    const typeInfo* type = choose_type();
    printf("Матрица:\n");
    Matrix* mat = create_and_fill_matrix(type);
    if (!mat) return;
    Matrix* result = transpose_matrix(mat);
    if (!result) {
        printf("Ошибка: %s\n", error_string(last_error));
        free_matrix(mat);
        return;
    }
    printf("Результат транспонирования:\n");
    print_matrix(result);
    free_matrix(mat);
    free_matrix(result);
}

void option_5() {
    const typeInfo* type = choose_type();
    printf("Матрица:\n");
    Matrix* mat = create_and_fill_matrix(type);
    if (!mat) return;
    int target_row;
    printf("Введите индекс целевой строки (от 0 до %d): ", mat->rows - 1);
    scanf("%d", &target_row);
    if (target_row < 0 || target_row >= mat->rows) {
        printf("Ошибка: %s\n", error_string(ERROR_INDEX_OUT_OF_RANGE));
        free_matrix(mat);
        return;
    }
    double* alphas = malloc(mat->rows * sizeof(double));
    if (!alphas) {
        printf("Ошибка: %s\n", error_string(ERROR_MEMORY_ERROR));
        free_matrix(mat);
        return;
    }
    printf("Введите коэффициенты для каждой строки:\n");
    for (int i = 0; i < mat->rows; i++) {
        if (i == target_row) {
            alphas[i] = 0.0;
            continue;
        }
        printf("Коэффициент для строки %d: ", i);
        scanf("%lf", &alphas[i]);
    }
    add_linear_combination(mat, target_row, alphas);
    if (last_error != ERROR_OK) {
        printf("Ошибка: %s\n", error_string(last_error));
        free(alphas);
        free_matrix(mat);
        return;
    }
    printf("Результат линейной комбинации:\n");
    print_matrix(mat);
    free(alphas);
    free_matrix(mat);
}

void option_6() {
    const typeInfo* type = choose_type();
    printf("Матрица для LU разложения:\n");
    Matrix* mat = create_and_fill_matrix(type);
    if (!mat) return;
    Matrix* L = create_matrix(mat->rows, mat->cols, mat->type);
    Matrix* U = create_matrix(mat->rows, mat->cols, mat->type);
    lu_decomposition(mat, L, U);
    if (last_error != ERROR_OK) {
        printf("Ошибка: %s\n", error_string(last_error));
        free_matrix(mat);
        free_matrix(L);
        free_matrix(U);
        return;
    }
    printf("LU Decomposition:\n");
    printf("Matrix L:\n");
    print_matrix(L);
    printf("Matrix U:\n");
    print_matrix(U);
    free_matrix(mat);
    free_matrix(L);
    free_matrix(U);
}

void option_7() {
    const typeInfo* type = choose_type();
    if (type->type != DOUBLE_TYPE) {
        printf("Определитель поддерживается только для типа Double.\n");
        return;
    }
    printf("Матрица для нахождения определителя:\n");
    Matrix* mat = create_and_fill_matrix(type);
    if (!mat) return;
    if (mat->rows != mat->cols) {
        printf("Ошибка: Определитель можно вычислить только для квадратной матрицы.\n");
        free_matrix(mat);
        return;
    }
    double determinant = *(double*)det(mat);
    if (last_error != ERROR_OK) {
        printf("Ошибка при вычислении определителя: %s\n", error_string(last_error));
        free_matrix(mat);
        return;
    }
    printf("Определитель матрицы: %f\n", determinant);
    free_matrix(mat);
}

void option_8() {
    const typeInfo* type = choose_type();
    if (type->type != DOUBLE_TYPE) {
        printf("Решение системы поддерживается только для типа Double.\n");
        return;
    }
    printf("Введите матрицу коэффициентов A:\n");
    Matrix* A = create_and_fill_matrix(type);
    if (!A) return;
    
    if (A->rows != A->cols) {
        printf("Ошибка: Матрица A должна быть квадратной.\n");
        free_matrix(A);
        return;
    }
    Matrix* L = create_matrix(A->rows, A->cols, A->type);
    Matrix* U = create_matrix(A->rows, A->cols, A->type);
    if (!L || !U) {
        printf("Ошибка: %s\n", error_string(last_error));
        if (L) free_matrix(L);
        if (U) free_matrix(U);
        free_matrix(A);
        return;
    }
    lu_decomposition(A, L, U);
    if (last_error != ERROR_OK) {
        printf("Ошибка при LU разложении: %s\n", error_string(last_error));
        free_matrix(A);
        free_matrix(L);
        free_matrix(U);
        return;
    }
    printf("LU разложение успешно выполнено.\n");
    printf("Матрица L:\n");
    print_matrix(L);
    printf("Матрица U:\n");
    print_matrix(U);
    char continue_input = 'y';
    int vector_count = 0;
    while (continue_input == 'y' || continue_input == 'Y') {
        printf("\nВведите вектор правой части b%d:\n", vector_count + 1);
        Matrix* b = create_matrix(A->rows, 1, type);
        if (!b) {
            free_matrix(A);
            free_matrix(L);
            free_matrix(U);
            return;
        }
        for (int i = 0; i < A->rows; i++) {
            printf("b[%d]: ", i);
            void* elem = malloc(type->size);
            if (!elem) {
                printf("Ошибка: %s\n", error_string(ERROR_MEMORY_ERROR));
                free_matrix(b);
                free_matrix(A);
                free_matrix(L);
                free_matrix(U);
                return;
            }
            type->scan(elem);
            set_element(b, i, 0, elem, type->type);
            free(elem);
        }
        Matrix* y = solve_first(L, b);
        if (!y) {
            printf("Ошибка при решении Ly = b: %s\n", error_string(last_error));
            free_matrix(b);
            continue;
        }
        Matrix* x = solve_second(U, y);
        if (!x) {
            printf("Ошибка при решении Ux = y: %s\n", error_string(last_error));
            free_matrix(y);
            free_matrix(b);
            continue;
        }
        printf("\nРешение для b%d:\n", vector_count + 1);
        print_matrix(x);
        free_matrix(y);
        free_matrix(x);
        free_matrix(b);
        vector_count++;
        printf("\nХотите ввести еще один вектор правой части? (y/n): ");
        while ((getchar()) != '\n');
        continue_input = getchar();
    }
    printf("\nВсего было решено %d систем уравнений.\n", vector_count);
    free_matrix(A);
    free_matrix(L);
    free_matrix(U);
}

void console_interface();

int main() {
    console_interface();
    return 0;
}

void console_interface() {
    int choice;
    do {
        clear_console();
        printf("\nВыберите операцию:\n");
        printf("1. Сложение матриц\n");
        printf("2. Умножение матриц\n");
        printf("3. Умножение матрицы на скаляр\n");
        printf("4. Транспонирование матрицы\n");
        printf("5. Линейная комбинация строк\n");
        printf("6. LU разложение\n");
        printf("7. Определитель матрицы\n");
        printf("8. Решение системы уравнений (с множественными правыми частями)\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        clear_console();
        switch (choice) {
            case 1:
                option_1();
                break;
            case 2:
                option_2();
                break;
            case 3:
                option_3();
                break;
            case 4:
                option_4();
                break;
            case 5:
                option_5();
                break;
            case 6:
                option_6();
                break;
            case 7:
                option_7();
                break;
            case 8:
                option_8();
                break;
            case 0:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
        if (choice != 0) {
            printf("\nНажмите Enter для продолжения...");
            getchar();
            getchar();
        }
    } while (choice != 0);
    clear_console();
}