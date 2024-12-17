CC = gcc
CFLAGS = -Wall --pedantic
SRC = src/*.c
TARGET = bin/gauss
TEST_DIR = test_data

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: all
	$(TARGET) dane/A dane/b

# Przykładowe przypadki testowe
test: all test1 test2 test3

# Test 1: Poprawne dane wejściowe
test1:
	@echo "===== Test 1: Poprawne dane wejściowe ====="
	$(TARGET) $(TEST_DIR)/A1 $(TEST_DIR)/b1 > $(TEST_DIR)/out1
	@diff $(TEST_DIR)/out1 $(TEST_DIR)/expected1 && echo "Test 1: SUCCESS" || echo "Test 1: FAILED"

# Test 2: Dane niespójne (brak rozwiązania)
test2:
	@echo "===== Test 2: Dane niespójne ====="
	$(TARGET) $(TEST_DIR)/A2 $(TEST_DIR)/b2 > $(TEST_DIR)/out2
	@diff $(TEST_DIR)/out2 $(TEST_DIR)/expected2 && echo "Test 2: SUCCESS" || echo "Test 2: FAILED"

# Test 3: Brak plików wejściowych
test3:
	@echo "===== Test 3: Brak plików wejściowych ====="
	$(TARGET) non_existing_A non_existing_b > $(TEST_DIR)/out3 2>&1 || true
	@grep "Nie mogę otworzyć pliku o nazwie" $(TEST_DIR)/out3 && echo "Test 3: SUCCESS" || echo "Test 3: FAILED"

clean:
	rm -f $(TARGET) $(TEST_DIR)/out*
