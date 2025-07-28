GXX = g++
CXXFLAGS =  -Wall -Wextra -std=c++20 -O2

all: test

test: 
	g++ -Wall -Wextra -std=c++20 -O2 s21_list_test.cpp -lgtest -lpthread -o test_list
	./test_list

clean:
	rm -f *.o test_list

check_style:
	clang-format -n s21_list.cpp s21_list.h s21_list_test.cpp

fix_style:
	clang-format -i s21_list.h s21_list_test.cpp

.PHONY: all clean check_style fix_style test