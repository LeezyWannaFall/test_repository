CC = gcc
CFLAGS = -std=c11 -g
LDFLAGS = -lncurses -lcheck -lm -lsubunit
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

EXE_NAME = tetris
LIB_NAME = libtetris.a

BRICK_GAME_DIR = brick_game/tetris
GUI_DIR = gui/cli
TEST_DIR = tests
BUILD_DIR = build

# Файлы
LIB_SRC = $(BRICK_GAME_DIR)/s21_tetris.c
GUI_SRC = $(GUI_DIR)/gui.c
TEST_SRC = $(TEST_DIR)/test.c
HEADERS = $(BRICK_GAME_DIR)/s21_tetris.h

# Объекты
LIB_OBJ = $(BUILD_DIR)/s21_tetris.o
GUI_OBJ = $(BUILD_DIR)/gui.o
TEST_OBJ = $(BUILD_DIR)/test.o

# Создаём build папку
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Правила компиляции
$(BUILD_DIR)/s21_tetris.o: $(LIB_SRC) $(HEADERS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/gui.o: $(GUI_SRC) $(HEADERS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/test.o: $(TEST_SRC) $(HEADERS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Сборка библиотеки
$(LIB_NAME): $(LIB_OBJ)
	ar rcs $@ $^

# Исполняемый файл
$(EXE_NAME): $(GUI_OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $(GUI_OBJ) -L. -ltetris $(LDFLAGS)
	echo 0 > highscore.txt

# Основная цель
all: $(LIB_NAME) $(EXE_NAME)

install: 
	clean $(EXE_NAME)

uninstall: clean

# Сборка и запуск тестов
test: $(TEST_OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) -o test_exe $(TEST_OBJ) -L. -ltetris $(LDFLAGS)
	./test_exe
	echo 0 > highscore.txt

# Gcov отчет
gcov_report: clean
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_SRC) $(LIB_SRC) $(LDFLAGS) -o gcov_exe
	./gcov_exe
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	genhtml -o gcov_report gcov_report.info

clean:
	rm -rf $(BUILD_DIR) $(LIB_NAME) $(EXE_NAME) test_exe gcov_exe *.gcno *.gcda *.gcov gcov_report.info gcov_report

.PHONY: all clean test gcov_report

