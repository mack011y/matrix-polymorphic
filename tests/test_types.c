#include <stdio.h>
#include <assert.h>
#include "../src/types/Int.h"
#include "../src/types/Double.h"
#include "../src/types/Complex.h"
#include "test_types.h"

int test_int() {
    int countOfProblem = 0;
    Int a = {5}, b = {3}, result = {0};
    sum_int(&a, &b, &result);
    if (result.value == 8) {
        printf("[OK]     sum_int()\n");
    } else {
        printf("[WA]     sum_int()\n");
        countOfProblem++;
    }
    multiply_int(&a, &b, &result);
    if (result.value == 15) {
        printf("[OK]     multiply_int()\n");
    } else {
        printf("[WA]     multiply_int()\n");
        countOfProblem++;
    }
    return_neutral_of_sum_int(&result);
    if (result.value == 0) {
        printf("[OK]     netrual_int()\n");
    } else {
        printf("[WA]     netrual_int()\n");
        countOfProblem++;
    }
    negate_int(&a, &result);
    if (result.value == -5) {
        printf("[OK]     negate_int()\n");
    } else {
        printf("[WA]     negate_int()\n");
        countOfProblem++;
    }
    divide_int(&a, &b, &result);
    if (result.value == 1) {
        printf("[OK]     divide_int()\n");
    } else {
        printf("[WA]     divide_int()\n");
        countOfProblem++;
    }
    return countOfProblem;
}

int test_double() {
    Double a = {5.5}, b = {2.5}, result = {0};
    int countOfProblem = 0;
    sum_double(&a, &b, &result);
    if (result.value == 8.0) {
        printf("[OK]     sum_double()\n");
    } else {
        printf("[WA]     sum_double()\n");
        printf("Result: %f\n", result.value);
        countOfProblem++;
    }
    multiply_double(&a, &b, &result);
    if (result.value == 13.75) {
        printf("[OK]     multiply_double()\n");
    } else {
        printf("[WA]     multiply_double()\n");
        countOfProblem++;
    }
    return_neutral_of_sum_double(&result);
    if (result.value == 0.0) {
        printf("[OK]     netrual_double()\n");
    } else {
        printf("[WA]     netrual_double()\n");
        countOfProblem++;
    }
    negate_double(&a, &result);
    if (result.value == -5.5) {
        printf("[OK]     negate_double()\n");
    } else {
        printf("[WA]     negate_double()\n");
        countOfProblem++;
    }
    divide_double(&a, &b, &result);
    if (result.value == 2.2) {
        printf("[OK]     divide_double()\n");
    } else {
        printf("[WA]     divide_double()\n");
        countOfProblem++;
    }
    return countOfProblem;
}

int test_complex() {
    int countOfProblem = 0;
    Complex a = {4.0, 3.0}, b = {1.0, -1.0}, result = {0.0, 0.0};

    sum_complex(&a, &b, &result);
    if (result.real == 5.0 && result.imaginary == 2.0) {
        printf("[OK]     sum_complex()\n");
    } else {
        printf("[WA]     sum_complex()\n");
        countOfProblem++;
    }

    multiply_complex(&a, &b, &result);
    if (result.real == 7.0 && result.imaginary == -1.0) {
        printf("[OK]     multiply_complex()\n");
    } else {
        printf("[WA]     multiply_complex()\n");
        countOfProblem++;
    }

    return_neutral_of_sum_complex(&result);
    if (result.real == 0.0 && result.imaginary == 0.0) {
        printf("[OK]     neutral_complex()\n");
    } else {
        printf("[WA]     neutral_complex()\n");
        countOfProblem++;
    }

    negate_complex(&a, &result);
    if (result.real == -4.0 && result.imaginary == -3.0) {
        printf("[OK]     negate_complex()\n");
    } else {
        printf("[WA]     negate_complex()\n");
        countOfProblem++;
    }

    divide_complex(&a, &b, &result);
    if (result.real == 0.5 && result.imaginary == 3.5) {
        printf("[OK]     divide_complex()\n");
    } else {
        printf("[WA]     divide_complex()\n");
        countOfProblem++;
    }

    return countOfProblem;
}

int test_types() {
    int answer = 0;
    answer += test_int();
    answer +=test_double();
    answer += test_complex();
    return answer;
}