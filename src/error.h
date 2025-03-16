#ifndef ERROR_H
#define ERROR_H

typedef enum {
    ERROR_OK = 0,                   // Нет ошибки
    ERROR_NULL_POINTER = 1,         // Нулевой указатель
    ERROR_INVALID_SIZE = 2,         // Неверный размер
    ERROR_TYPE_MISMATCH = 3,        // Несоответствие типов
    ERROR_INDEX_OUT_OF_RANGE = 4,   // Индекс вне диапазона
    ERROR_MEMORY_ERROR = 5,         // Ошибка выделения памяти
    ERROR_NOT_SQUARE = 6,           // Матрица не квадратная
    ERROR_SINGULAR = 7,             // Вырожденная матрица (для обратной и LU)
    ERROR_INCOMPATIBLE_SIZES = 8,   // Несовместимые размеры
    ERROR_FILE_OPEN = 9,            // Ошибка открытия файла
    ERROR_FILE_READ = 10,           // Ошибка чтения файла
    ERROR_FILE_WRITE = 11,          // Ошибка записи в файл
    ERROR_INVALID_FORMAT = 12,      // Неверный формат данных
    ERROR_OPERATION_FAILED = 13,    // Общая ошибка операции
    ERROR_DIVISION_BY_ZERO = 14     // Деление на ноль
} ErrorCode;

extern ErrorCode last_error;

const char* error_string(ErrorCode error);

void set_error(ErrorCode error);

void reset_error();

#endif /* ERROR_H */ 