# матрицы на C

## Описание
Этот проект представляет собой библиотеку для работы с матрицами на языке C. Он включает базовые операции, такие как создание матриц, сложение, умножение, умножение на скаляр и линейные комбинации строк.

## Возможности
- **Динамическое выделение памяти** для матриц  
- **Поддержка различных типов данных** через `void*`  
- **Основные операции:**  
  - **Создание** и **удаление** матриц  
  - **Сложение** матриц  
  - **Умножение** матриц  
  - **Умножение на скаляр**  
  - **Линейная комбинация строк**  
- **Безопасное управление памятью** для предотвращения утечек  

## Установка
Склонируйте репозиторий и скомпилируйте файлы с помощью компилятора C (например, GCC):

```sh
git clone https://github.com/mack011y/matrix-library.git
cd matrix-library
gcc -o matrix_program main.c matrix.c -Wall -Wextra -std=c11
```

## Использование
### Создание матрицы
```c
Matrix* mat = create_matrix(3, 3, sizeof(double)); 
```

### Заполнение и вывод матрицы
```c
// Заполнение  
*(double*)mat->data[0][0] = 2.5;  
*(double*)mat->data[1][1] = 3.0;  

// Вывод (требуется функция для типа double)  
print_matrix(mat, print_double); 
```

### Сложение матриц
```c
Matrix* sum = add_matrices(mat1, mat2, sum_double);
```

### Умножение матриц
```c
Matrix* product = multiply_matrices(mat1, mat2, multiply_double, sum_double);  
```

### Умножение на скаляр
```c
multiply_matrix_by_scalar(mat, 2.5, multiply_double_by_scalar);  
```

### Линейная комбинация строк
```c
double coefficients[] = {0.5, -1.0, 0.0}; // Коэффициенты для строк  
add_linear_combination(mat, 0, coefficients, sum_double, multiply_double_by_scalar);  
```

### Освобождение памяти
```c
free_matrix(mat);
```

### Пример функций для типа double
```c
void print_double(void* element) {  
    printf("%.2f ", *(double*)element);  
}  

void sum_double(void* a, void* b, void* result) {  
    *(double*)result = *(double*)a + *(double*)b;  
}  

void multiply_double(void* a, void* b, void* result) {  
    *(double*)result = *(double*)a * *(double*)b;  
}  

void multiply_double_by_scalar(void* a, double scalar, void* result) {  
    *(double*)result = *(double*)a * scalar;  
}  
```
