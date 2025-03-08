CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = src/main.c src/matrix.c src/types/Double.c src/types/Int.c src/types/Complex.c
OBJ = $(SRC:.c=.o)

TEST_SRC = tests/checkAllTests.c tests/test_matrix.c tests/test_types.c src/matrix.c src/types/Double.c src/types/Int.c src/types/Complex.c
TEST_OBJ = $(TEST_SRC:.c=.o)

TARGET = matrix_program
TEST_TARGET = test

test: $(TEST_OBJ)
	$(CC) $(TEST_OBJ) -o $(TEST_TARGET)
	./$(TEST_TARGET)
	$(MAKE) all
	./$(TARGET)

all: $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) $(TEST_TARGET) $(TEST_OBJ)