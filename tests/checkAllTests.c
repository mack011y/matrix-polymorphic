#include "test_types.h"
#include "test_matrix.h"
#include <stdio.h>

int main() {
    printf("==================================\n");
    printf("RUNNING TESTS...\n");
    int countOfProblem = 0;
    countOfProblem += test_types();
    countOfProblem += test_matrix();
    printf("\n======COUNT OF PROBLEMS ~ %d======\n", countOfProblem);
}