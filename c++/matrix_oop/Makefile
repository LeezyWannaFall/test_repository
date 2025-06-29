CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -O2
AR = ar
ARFLAGS = rcs

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

LIB_NAME = libs21matrix.a

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: $(LIB_NAME)

$(LIB_NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(LIB_NAME)

.PHONY: all clean