CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -O2

AR = ar
ARFLAGS = rcs

SRC = core/s21_matrix_oop.cpp
OBJ_DIR = obj
LIB_NAME = s21_matrix_oop.a

OBJ = $(patsubst %.c, %.o, $(SRC))

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@
test: 
	g++ -std=c++20 -Wall -Wextra -O2 tests/main.cpp core/s21_matrix_oop.cpp -lgtest -lpthread -o test_matrix
	./test_matrix
clean:
	rm -rf $(OBJ_DIR) $(LIB_NAME) test_matrix

.PHONY: all clean