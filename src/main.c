#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "types/Complex.h"
#include "types/Double.h"
#include "types/Int.h"
#include "typesEnum.h"

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

Matrix* load_matrix_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }

    int rows, cols, type_choice;
    fscanf(file, "%d %d %d", &rows, &cols, &type_choice);
    DataType type = (DataType)type_choice;

    Matrix* mat = create_matrix(rows, cols, type);
    if (!mat) {
        printf("Error: Failed to create matrix.\n");
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            void* value = malloc(mat->type->size);
            mat->type->scan(value);
            set_element(mat, i, j, value);
            free(value);
        }
    }
    fclose(file);
    return mat;
}


Matrix* create_and_fill_matrix() {
    int rows, cols, type_choice;

    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Choose data type (0 - Double, 1 - Int, 2 - Complex): ");
    scanf("%d", &type_choice);

    if (type_choice < 0 || type_choice > 2) {
        printf("Invalid type selection.\n");
        return NULL;
    }

    DataType type = type_choice;
    print_input_instructions(type);

    Matrix* mat = create_matrix(rows, cols, type);
    if (!mat) {
        printf("Failed to create matrix.\n");
        return NULL;
    }

    printf("Enter matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            void* value = malloc(mat->type->size);
            mat->type->scan(value);
            set_element(mat, i, j, value);
            free(value);
        }
    }

    return mat;
}

void option_1(Matrix** mat1, Matrix** mat2, Matrix** result) {
    printf("Matrix A:\n");
    *mat1 = create_and_fill_matrix();
    printf("Matrix B:\n");
    *mat2 = create_and_fill_matrix();

    if (*mat1 && *mat2) {
        *result = add_matrices(*mat1, *mat2);
        printf("Sum result:\n");
        print_matrix(*result);
        free_matrix(*result);
    } else {
        printf("Failed to create matrices. Try again.\n");
    }
    free_matrix(*mat1);
    free_matrix(*mat2);
}

void option_2(Matrix** mat1, Matrix** mat2, Matrix** result) {
    printf("Matrix A:\n");
    *mat1 = create_and_fill_matrix();
    printf("Matrix B:\n");
    *mat2 = create_and_fill_matrix();

    if (*mat1 && *mat2) {
        *result = multiply_matrices(*mat1, *mat2);
        printf("Multiplication result:\n");
        print_matrix(*result);
        free_matrix(*result);
    } else {
        printf("Failed to create matrices. Try again.\n");
    }
}

void option_3(Matrix** mat) {
    printf("Matrix A:\n");
    *mat = create_and_fill_matrix();

    if (*mat) {
        printf("Enter scalar value: ");
        double scalar;
        scanf("%lf", &scalar);
        multiply_matrix_by_scalar(*mat, scalar);
        printf("Matrix after scalar multiplication:\n");
        print_matrix(*mat);
    }
}

void option_4(Matrix** mat) {
    *mat = create_and_fill_matrix();
    if (*mat) {
        printf("Transpose of matrixч:\n");
        Matrix* transposed = transpose_matrix(*mat);
        print_matrix(transposed);
        free_matrix(transposed);
    } else {
        printf("Failed to create matrix. Try again.\n");
    }
}

void option_5(Matrix** mat) {
    printf("Matrix A:\n");
    *mat = create_and_fill_matrix();

    if (*mat) {
        int rowIndex;
        printf("Enter the row index for the linear combination (0 to %d): ", (*mat)->rows - 1);
        scanf("%d", &rowIndex);

        if (rowIndex < 0 || rowIndex >= (*mat)->rows) {
            printf("Invalid row index. Try again.\n");
            free_matrix(*mat);
            return;
        }

        double* alphas = malloc((*mat)->rows * sizeof(double));
        printf("Enter the coefficients (alphas) for the linear combination:\n");
        for (int i = 0; i < (*mat)->rows; i++) {
            if (i == rowIndex) {
                alphas[i] = 1.0;
            } else {
                printf("Alpha[%d]: ", i);
                scanf("%lf", &alphas[i]);
            }
        }

        add_linear_combination(*mat, rowIndex, alphas);

        printf("Matrix after linear combination:\n");
        print_matrix(*mat);
        free(alphas);
    } else {
        printf("Failed to create matrix. Try again.\n");
    }
}

void console_interface() {
    while (1) {
        printf("\n===== Matrix Console Interface =====\n");
        printf("1. Add two matrices\n");
        printf("2. Multiply two matrices\n");
        printf("3. Multiply by scalar\n");
        printf("4. Transpose a matrix\n");
        printf("5. Add linear combination\n");
        printf("0. Exit\n");
        printf("====================================\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("Exiting...\n");
            break;
        }

        Matrix *mat1 = NULL, *mat2 = NULL, *result = NULL;
        switch (choice) {
            case 1:
                option_1(&mat1, &mat2, &result);
                break;
            case 2:
                option_2(&mat1, &mat2, &result);
                break;
            case 3:
                option_3(&mat1);
                break;
            case 4:
                option_4(&mat1);
                break;
            case 5:
                option_5(&mat1);
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

int main() {
    console_interface();
    return 0;
}