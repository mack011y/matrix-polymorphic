#include "error.h"
#include <stdio.h>

ErrorCode last_error = ERROR_OK;

static const char* error_messages[] = {
    "Нет ошибки",                      // ERROR_OK
    "Нулевой указатель",               // ERROR_NULL_POINTER
    "Неверный размер",                 // ERROR_INVALID_SIZE
    "Несоответствие типов",            // ERROR_TYPE_MISMATCH
    "Индекс вне диапазона",            // ERROR_INDEX_OUT_OF_RANGE
    "Ошибка выделения памяти",         // ERROR_MEMORY_ERROR
    "Матрица не квадратная",           // ERROR_NOT_SQUARE
    "Вырожденная матрица",             // ERROR_SINGULAR
    "Несовместимые размеры",           // ERROR_INCOMPATIBLE_SIZES
    "Ошибка открытия файла",           // ERROR_FILE_OPEN
    "Ошибка чтения файла",             // ERROR_FILE_READ
    "Ошибка записи в файл",            // ERROR_FILE_WRITE
    "Неверный формат данных",          // ERROR_INVALID_FORMAT
    "Общая ошибка операции",           // ERROR_OPERATION_FAILED
    "Деление на ноль"                  // ERROR_DIVISION_BY_ZERO
};

const char* error_string(ErrorCode error) {
    if (error < 0 || error > ERROR_DIVISION_BY_ZERO) {
        return "Неизвестная ошибка";
    }
    return error_messages[error];
}

void set_error(ErrorCode error) {
    last_error = error;
    printf("Ошибка: %s\n", error_string(error));
}

void reset_error() {
    last_error = ERROR_OK;
} 