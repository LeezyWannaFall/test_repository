CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -O2

SRC = core/s21_matrix_oop.cpp
OBJ_DIR = obj
OBJ = $(OBJ_DIR)/s21_matrix_oop.o
LIB_NAME = s21_matrix_oop.a
HEADER = s21_matrix_oop.h

all: $(LIB_NAME) check_style test

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ): $(SRC) $(HEADER) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIB_NAME): $(OBJ)
	ar rcs $@ $^

test: 
	$(CXX) $(CXXFLAGS) tests/s21_matrix_oop_tests.cpp core/s21_matrix_oop.cpp -lgtest -lpthread -o test_matrix
	./test_matrix

check_style:
	clang-format -n core/* tests/* s21_matrix_oop.h

fix_style:
	clang-format -i core/* tests/* s21_matrix_oop.h

clean:
	rm -rf $(OBJ_DIR) $(LIB_NAME) test_matrix

.PHONY: all clean check_style fix_style test