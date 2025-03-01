CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Исходные файлы и объектные файлы
SRC = main.c matrix.c types/Double.c types/Int.c types/Complex.c
OBJ = $(SRC:.c=.o)

# Финальный исполняемый файл
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)