# Matrix Operations Console Application
# Консольное приложение для работы с матрицами

## Description | Описание

This console application provides a powerful tool for working with matrices, supporting various operations including LU decomposition and solving systems of linear equations.

Это консольное приложение представляет собой мощный инструмент для работы с матрицами, поддерживающий различные операции, включая LU-разложение и решение систем линейных уравнений.

## Features | Возможности

- Matrix creation and input
- Matrix addition and multiplication
- Scalar multiplication
- Matrix transposition
- LU decomposition
- Solving systems of linear equations
- Determinant calculation
- Linear combinations of rows

---

- Создание и ввод матриц
- Сложение и умножение матриц
- Умножение на скаляр
- Транспонирование матриц
- LU-разложение
- Решение систем линейных уравнений
- Вычисление определителя
- Линейные комбинации строк

## Building the Application | Сборка приложения

```bash
make
```

## Usage | Использование

Run the compiled application:
Запуск скомпилированного приложения:

```bash
./matrix
```

### Available Operations | Доступные операции

1. Matrix Addition | Сложение матриц
   - Enter dimensions and elements of two matrices
   - Введите размерности и элементы двух матриц

2. Matrix Multiplication | Умножение матриц
   - Enter dimensions and elements of two matrices
   - Number of columns in first matrix must equal number of rows in second matrix
   - Введите размерности и элементы двух матриц
   - Количество столбцов первой матрицы должно равняться количеству строк второй

3. Scalar Multiplication | Умножение на скаляр
   - Enter matrix dimensions and elements
   - Enter scalar value
   - Введите размерности и элементы матрицы
   - Введите скалярное значение

4. Matrix Transposition | Транспонирование матрицы
   - Enter matrix dimensions and elements
   - Введите размерности и элементы матрицы

5. Linear Combination | Линейная комбинация
   - Enter matrix dimensions and elements
   - Enter target row and coefficients
   - Введите размерности и элементы матрицы
   - Введите целевую строку и коэффициенты

6. LU Decomposition | LU-разложение
   - Enter square matrix dimensions and elements
   - Returns matrices L and U
   - Введите размерности квадратной матрицы и её элементы
   - Возвращает матрицы L и U

7. Solve System of Linear Equations | Решение системы линейных уравнений
   - Enter coefficient matrix A and vector b
   - Returns solution vector x
   - Введите матрицу коэффициентов A и вектор b
   - Возвращает вектор решения x

8. Calculate Determinant | Вычисление определителя
   - Enter square matrix dimensions and elements
   - Returns determinant value
   - Введите размерности квадратной матрицы и её элементы
   - Возвращает значение определителя

### Input Format | Формат ввода

For matrices:
Для матриц:
```
Rows Columns
element_11 element_12 ... element_1n
element_21 element_22 ... element_2n
...
element_m1 element_m2 ... element_mn
```

For vectors:
Для векторов:
```
Size
element_1
element_2
...
element_n
```

### Example | Пример

Solving system of linear equations:
Решение системы линейных уравнений:

```
Enter matrix A (3x3):
3 3
1 2 -1
2 1 -2
3 -1 1

Enter vector b (3x1):
3
1
-3
2

Solution x:
1.000
2.000
3.000
```

## Error Handling | Обработка ошибок

The application includes comprehensive error handling for:
Приложение включает в себя обработку следующих ошибок:

- Invalid dimensions | Неверные размерности
- Memory allocation failures | Ошибки выделения памяти
- Division by zero | Деление на ноль
- Incompatible matrix sizes | Несовместимые размеры матриц
- Invalid input format | Неверный формат ввода

## Technical Details | Технические детали

- Written in C
- Uses dynamic memory allocation
- Supports double precision floating-point numbers
- Написано на языке C
- Использует динамическое выделение памяти
- Поддерживает числа с плавающей точкой двойной точности

## Memory Management | Управление памятью

All dynamically allocated memory is properly freed after use to prevent memory leaks.
Вся динамически выделенная память корректно освобождается после использования для предотвращения утечек памяти. 